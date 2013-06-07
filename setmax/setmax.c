/* setmax.c - aeb, 000326 - use on 2.4.0test9 or newer */
/* IBM part thanks to Matan Ziv-Av <matan@svgalib.org> */
/*
 * Results on Maxtor disks:
 * The jumper that clips capacity does not influence the value returned
 * by READ_NATIVE_MAX_ADDRESS, so it is possible to set the jumper
 * and let the kernel, or a utility (like this one) run at boot time
 * restore full capacity.
 * For example, run "setmax -d 0 /dev/hdX" for suitable X.
 * Kernel patches exist that do the same.
 *
 * Results on IBM disks:
 * The jumper that clips capacity is ruthless. You clipped capacity.
 * However, if your BIOS hangs on a large disk, do not use the jumper
 * but find another machine and use a utility (like this one) to
 * clip the non-volatile max address.
 * For example, run "setmax -m 66055248 /dev/hdX" for suitable X.
 * Now go back to your first machine and proceed as with Maxtor drives above.
 */
#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <linux/hdreg.h>

#ifndef HDIO_DRIVE_CMD_AEB
#define HDIO_DRIVE_CMD_AEB	0x031e
#endif

#define INITIALIZE_DRIVE_PARAMETERS 0x91
#define READ_NATIVE_MAX_ADDRESS 0xf8
#define CHECK_POWER_MODE	0xe5
#define SET_MAX			0xf9

#define LBA	0x40
#define VV	1		/* if set in sectorct then NOT volatile */

struct idecmdin {
	unsigned char cmd;
	unsigned char feature;
	unsigned char nsect;
	unsigned char sect, lcyl, hcyl;
	unsigned char select;
};

struct idecmdout {
	unsigned char status;
	unsigned char error;
	unsigned char nsect;
	unsigned char sect, lcyl, hcyl;
	unsigned char select;
};

unsigned int
tolba(unsigned char *args) {
	return ((args[6] & 0xf) << 24) + (args[5] << 16) + (args[4] << 8) + args[3];
}

void
fromlba(unsigned char *args, unsigned int lba) {
	args[3] = (lba & 0xff);
	lba >>= 8;
	args[4] = (lba & 0xff);
	lba >>= 8;
	args[5] = (lba & 0xff);
	lba >>= 8;
	args[6] = (args[6] & 0xf0) | (lba & 0xf);
}

int
get_identity(int fd) {
	unsigned char args[4+512] = {WIN_IDENTIFY,0,0,1,};
	struct hd_driveid *id = (struct hd_driveid *)&args[4];

	if (ioctl(fd, HDIO_DRIVE_CMD, &args)) {
		perror("HDIO_DRIVE_CMD");
		fprintf(stderr,
			"WIN_IDENTIFY failed - trying WIN_PIDENTIFY\n");
		args[0] = WIN_PIDENTIFY;
		if (ioctl(fd, HDIO_DRIVE_CMD, &args)) {
			perror("HDIO_DRIVE_CMD");
			fprintf(stderr,
			       "WIN_PIDENTIFY also failed - giving up\n");
			exit(1);
		}
	}

	printf("lba capacity: %d sectors (%lld bytes)\n",
	       id->lba_capacity,
	       (long long) id->lba_capacity * 512);
}

/*
 * result: in LBA mode precisely what is expected
 *         in CHS mode the correct H and S, and C mod 65536.
 */
unsigned int
get_native_max(int fd, int slave) {
	unsigned char args[7];
	int i, max;

	for (i=0; i<7; i++)
		args[i] = 0;
	args[0] = READ_NATIVE_MAX_ADDRESS;
	args[6] = (slave ? 0x10 : 0) | LBA;
	if (ioctl(fd, HDIO_DRIVE_CMD_AEB, &args)) {
		perror("HDIO_DRIVE_CMD_AEB failed READ_NATIVE_MAX_ADDRESS");
		for (i=0; i<7; i++)
			printf("%d = 0x%x\n", args[i], args[i]);
		exit(1);
	}
	return tolba(args);
}

/*
 * SET_MAX_ADDRESS requires immediately preceding READ_NATIVE_MAX_ADDRESS
 *
 * On old Maxtor disk: this fails for delta <= 254, succeeds for delta >= 255.
 * (So, in order to get the last 255*512=130560 bytes back one has to reboot.
 * Side effect: reset to CurCHS=16383/16/63, CurSects=16514064.)
 * On new Maxtor disk: this works.
 * On IBM disk without jumper: this works.
 */
void
set_max_address(int fd, int slave, int delta, int max, int volat) {
	unsigned char args[7];
	int i, nativemax, newmax;

	nativemax = get_native_max(fd, slave);
	printf("nativemax=%d (0x%x)\n", nativemax, nativemax);

	for (i=0; i<7; i++)
		args[i] = 0;
	args[0] = SET_MAX;
	args[1] = 0;
	args[2] = (volat ? 0 : 1);
	if (delta != -1)
		newmax = nativemax-delta;
	else
		newmax = max-1;
	fromlba(args, newmax);
	args[6] |= LBA;

	if (ioctl(fd, HDIO_DRIVE_CMD_AEB, &args)) {
		perror("HDIO_DRIVE_CMD_AEB failed SET_MAX");
		for (i=0; i<7; i++)
			printf("%d = 0x%x\n", args[i], args[i]);
		exit(1);
	}
}

static char short_opts[] = "d:m:";
static const struct option long_opts[] = {
	{ "delta",	required_argument,	NULL,	'd' },
	{ "max",	required_argument,	NULL,	'm' },
        { NULL, 0, NULL, 0 }
};

static char *usage_txt =
"Call: setmax [-d D] [-m M] DEVICE\n"
"\n"
"The call  \"setmax --max M DEVICE\"  will do a SET_MAX command\n"
"to set the non-volatile max number of accessible sectors to M.\n"
"\n"
"The call  \"setmax --delta D DEVICE\"  will do a SET_MAX command\n"
"to set the maximum accessible sector number D sectors\n"
"below end-of-disk.\n"
"\n"
"The call  \"setmax DEVICE\"  will do a READ_NATIVE_MAX_ADDRESS\n"
"command, and report the maximum accessible sector number.\n"
"\n"
"This is IDE-only. Probably DEVICE is /dev/hdx for some x.\n\n";

main(int argc, char **argv){
	int fd, c;
	int delta, max, volat;

	/* If you modify device, also update slave, if necessary. */
	/* The kernel already does this for us since 2.4.0test9. */
	/* master: hda, hdc, hde; slave: hdb, hdd, hdf */
	char *device = NULL;	/* e.g. "/dev/hda" */
	int slave = 0;

	delta = max = volat = -1;
	while ((c = getopt_long (argc, argv, short_opts, long_opts, NULL)) != -1) {
		switch(c) {
		case 'd':
			delta = atoi(optarg);
			volat = 1;
			break;
		case 'm':
			max = atoi(optarg);
			volat = 0;
			break;
		case '?':
		default:
			fprintf(stderr, "unknown option\n");
			fprintf(stderr, usage_txt);
			exit(1);
		}
	}

	if (optind < argc)
		device = argv[optind];
	if (!device) {
		fprintf(stderr, "no device specified - "
			"use e.g. \"setmax /dev/hdb\"\n");
		fprintf(stderr, usage_txt);
		exit(1);
	}
	printf("Using device %s\n", device);

	fd = open(device, O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	if (delta != -1 || max != -1) {
		if (delta != -1)
			printf("setting delta=%d\n", delta);
		else
			printf("setting max=%d\n", max);
		set_max_address(fd, slave, delta, max, volat);
	} else {
		int mad = get_native_max(fd, slave);
		long long bytes = (long long) (mad+1) * 512;
		int hMB = (bytes+50000000)/100000000;

		printf("native max address: %d\n", mad);
		printf("that is %lld bytes, %d.%d GB\n",
		       bytes, hMB/10, hMB%10);
	}
	get_identity(fd);

	return 0;
}
