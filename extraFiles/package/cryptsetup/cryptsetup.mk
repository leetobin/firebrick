CRYPTSETUP_VERSION = 1.6.1
CRYPTSETUP_SOURCE = cryptsetup-1.6.1.tar.bz2
CRYPTSETUP_SITE = http://cryptsetup.googlecode.com/files
CRYPTSETUP_AUTORECONF = NO
CRYPTSETUP_INSTALL_STAGING = NO
CRYPTSETUP_INSTALL_TARGET = YES
CRYPTSETUP_CONF_OPT = --with-crypto_backend=gcrypt --with-libgcrypt-prefix=$(STAGING_DIR)/usr
CRYPTSETUP_DEPENDENCIES = lvm2 libgcrypt popt e2fsprogs
$(eval $(autotools-package))
