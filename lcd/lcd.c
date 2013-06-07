/*
 * lcd2usb.c - test application for the lcd2usb interface
 *             http://www.harbaum.org/till/lcd2usb
 *
 * Modified for use in FIREBrick by Pavel Gladyshev, DigitalFIRE
 *             http://digitalfire.ucd.ie/firebrick
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <usb.h>

/* vendor and product id */
#define LCD2USB_VID  0x0403
#define LCD2USB_PID  0xc630

/* target is a bit map for CMD/DATA */
#define LCD_CTRL_0         (1<<3)
#define LCD_CTRL_1         (1<<4)
#define LCD_BOTH           (LCD_CTRL_0 | LCD_CTRL_1)

#define LCD_ECHO           (0<<5)
#define LCD_CMD            (1<<5)
#define LCD_DATA           (2<<5)
#define LCD_SET            (3<<5)
#define LCD_GET            (4<<5)

/* target is value to set */
#define LCD_SET_CONTRAST   (LCD_SET | (0<<3))
#define LCD_SET_BRIGHTNESS (LCD_SET | (1<<3))
#define LCD_SET_RESERVED0  (LCD_SET | (2<<3))
#define LCD_SET_RESERVED1  (LCD_SET | (3<<3))

/* target is value to get */
#define LCD_GET_FWVER      (LCD_GET | (0<<3))
#define LCD_GET_KEYS       (LCD_GET | (1<<3))
#define LCD_GET_CTRL       (LCD_GET | (2<<3))
#define LCD_GET_RESERVED1  (LCD_GET | (3<<3))

/* Max length of input string */
#define MAX_LINE_LENGTH (1024)

#ifdef WIN
#include <windows.h>
#include <winbase.h>
#define MSLEEP(a) Sleep(a)
#else
#define MSLEEP(a) usleep(a*1000)
#endif


usb_dev_handle      *handle = NULL;

int lcd_send(int request, int value, int index) {
  if(usb_control_msg(handle, USB_TYPE_VENDOR, request, 
		      value, index, NULL, 0, 1000) < 0) {
    fprintf(stderr, "USB request failed!");
    return -1;
  }
  return 0;
}

/* to increase performance, a little buffer is being used to */
/* collect command bytes of the same type before transmitting them */
#define BUFFER_MAX_CMD 4        /* current protocol supports up to 4 bytes */
int buffer_current_type = -1;   /* nothing in buffer yet */
int buffer_current_fill = 0;    /* -"- */
unsigned char buffer[BUFFER_MAX_CMD];

/* command format:
 * 7 6 5 4 3 2 1 0
 * C C C T T R L L
 *
 * TT = target bit map
 * R = reserved for future use, set to 0
 * LL = number of bytes in transfer - 1
 */

/* flush command queue due to buffer overflow / content */
/* change or due to explicit request */
void lcd_flush(void) {
  int request, value, index;
  
  /* anything to flush? ignore request if not */
  if (buffer_current_type == -1)
    return;
  
  /* build request byte */
  request = buffer_current_type | (buffer_current_fill - 1);
  
  /* fill value and index with buffer contents. endianess should IMHO not */
  /* be a problem, since usb_control_msg() will handle this. */
  value = buffer[0] | (buffer[1] << 8);
  index = buffer[2] | (buffer[3] << 8);
  
  /* send current buffer contents */
  lcd_send(request, value, index);
  
  /* buffer is now free again */
  buffer_current_type = -1;
  buffer_current_fill = 0;
}

/* enqueue a command into the buffer */
void lcd_enqueue(int command_type, int value) {
  if ((buffer_current_type >= 0) && (buffer_current_type != command_type))
    lcd_flush();
  
  /* add new item to buffer */
  buffer_current_type = command_type;
  buffer[buffer_current_fill++] = value;
  
  /* flush buffer if it's full */
  if (buffer_current_fill == BUFFER_MAX_CMD)
    lcd_flush();
}

/* see HD44780 datasheet for a command description */
void lcd_command(const unsigned char ctrl, const unsigned char cmd) {
  lcd_enqueue(LCD_CMD | ctrl, cmd);
}

/* clear display */
void lcd_clear(void) {
  lcd_command(LCD_BOTH, 0x01);    /* clear display */
  lcd_command(LCD_BOTH, 0x03);    /* return home */
  lcd_flush();
}

/* home display */
void lcd_home(void) {
  lcd_command(LCD_BOTH, 0x03);    /* return home */
  lcd_flush();
}

/* Backspace */
void lcd_backspace(void) {
  lcd_command(LCD_BOTH, 0x10);    
  lcd_flush();
}

/* Set cursor on the first display to position X,Y (X is column, Y is row) */
void lcd_gotoxy(int x, int y) {
    switch (y)
    {
       case 0: lcd_command(LCD_BOTH, 0x80+0+x); break;
       case 1: lcd_command(LCD_BOTH, 0x80+0x40+x); break;
       case 2: lcd_command(LCD_BOTH, 0x80+0x14+x); break;
       case 3: lcd_command(LCD_BOTH, 0x80+0x54+x); break;
    }
    lcd_flush();
}


/* write a data string to the first display */
void lcd_write(const char *data) {
  int ctrl = LCD_CTRL_0;
  
  while(*data) 
    lcd_enqueue(LCD_DATA | ctrl, *data++);
  
  lcd_flush();
}

/* send a number of 16 bit words to the lcd2usb interface */
/* and verify that they are correctly returned by the echo */
/* command. This may be used to check the reliability of */
/* the usb interfacing */
#define ECHO_NUM 100
void lcd_echo(void) {

  int i, nBytes, errors=0;
  unsigned short val, ret;

  for(i=0;i<ECHO_NUM;i++) {
    val = rand() & 0xffff;
    
    nBytes = usb_control_msg(handle, 
	   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 
	   LCD_ECHO, val, 0, (char*)&ret, sizeof(ret), 1000);

    if(nBytes < 0) {
      fprintf(stderr, "USB request failed!");
      return;
    }

    if(val != ret)
      errors++;
  }

  if(errors) 
    fprintf(stderr, "ERROR: %d out of %d echo transfers failed!\n", 
	    errors, ECHO_NUM);
  else 
    printf("Echo test successful!\n");
}

/* get a value from the lcd2usb interface */
int lcd_get(unsigned char cmd) {
  unsigned char       buffer[2];
  int                 nBytes;

  /* send control request and accept return value */
  nBytes = usb_control_msg(handle, 
	   USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, 
	   cmd, 0, 0, (char *)buffer, sizeof(buffer), 1000);

  if(nBytes < 0) {
    fprintf(stderr, "USB request failed!");
    return -1;
  }

  return buffer[0] + 256*buffer[1];
}

/* get lcd2usb interface firmware version */
void lcd_get_version(void) {
  int ver = lcd_get(LCD_GET_FWVER);

  if(ver != -1) 
    printf("Firmware version %d.%d\n", ver&0xff, ver>>8);
}

/* get the bit mask of installed LCD controllers (0 = no */
/* lcd found, 1 = single controller display, 3 = dual */
/* controller display */
void lcd_get_controller(void) {
  int ctrl = lcd_get(LCD_GET_CTRL);

  if(ctrl != -1) {
    if(ctrl)
      printf("Installed controllers: %s%s\n", 
	     (ctrl&1)?"CTRL0":"",
	     (ctrl&2)?" CTRL1":"");
    else
      printf("No controllers installed!\n");
  }
}

/* get state of the two optional buttons */
void lcd_get_keys(void) {
  int keymask = lcd_get(LCD_GET_KEYS);

  if(keymask != -1) 
    printf("Keys: 0:%s 1:%s\n",
	   (keymask&1)?"on":"off",
	   (keymask&2)?"on":"off");
}

/* set a value in the LCD interface */
void lcd_set(unsigned char cmd, int value) {
  if(usb_control_msg(handle, 
	     USB_TYPE_VENDOR, cmd, value, 0, 
	     NULL, 0, 1000) < 0) {
    fprintf(stderr, "USB request failed!");
  }
}

/* set contrast to a value between 0 and 255. Result depends */
/* display type */
void lcd_set_contrast(int value) {
  lcd_set(LCD_SET_CONTRAST, value);
}

/* set backlight brightness to a value between 0 (off) anf 255 */
void lcd_set_brightness(int value) {
  lcd_set(LCD_SET_BRIGHTNESS, value);
}

void printUsage() 
{
   printf ("\nUsage: \n");
   printf ("   lcd             - without any parameters will act like TEE\n");
   printf ("   lcd c           - erase LCD screen\n");
   printf ("   lcd g 2 5       - set cursor to the row 2 column 5\n");
   printf ("   lcd p \"Hello\"   - print Hello message on LCD and exit\n");
   printf ("   lcd o 123       - set LCD cOntrast to 123 \n");
   printf ("   lcd b 123       - set LCD brightness to 123 \n\n");
}

void lcd_read_line(char *line, int x, int y, int width, int length)
{
   char *pos = line;
   char *win = line;
   
   char c;
   
   lcd_gotoxy(x,y);
   
   while ( (c=getchar()) > 0)
   {
      //printf ("%d",c);
      if (c == 13) break;
	  if (c == 127) 
      {
         if (pos > line)		 
		 { 
		   pos--; 
		   x--; 
		 }
		 lcd_gotoxy(x,y);
		 lcd_enqueue(LCD_DATA | LCD_CTRL_0, ' ');
         lcd_flush();
		 lcd_gotoxy(x,y);
	  }
	  else
	  {
		 lcd_enqueue(LCD_DATA | LCD_CTRL_0, c);
         lcd_flush(); 
		 *pos = c;
		 if ((pos-line)<(width-1)) 
		 {
		   pos++;
		   x++;
		 }
		 lcd_gotoxy(x,y);
	  }
   }
   *pos = 0;
}

int main(int argc, char *argv[]) {
  struct usb_bus      *bus;
  struct usb_device   *dev;

  if (argc == 2)
  {
     if ((argv[1][0]!='c') && 
         (argv[1][0]!='g') && 
         (argv[1][0]!='p') && 
         (argv[1][0]!='o') && 
         (argv[1][0]!='b'))
     {
        printUsage();
        exit(0);
     }
  }

  /* Find & initialise the LCD2USB device */
  usb_init();
    
  usb_find_busses();
  usb_find_devices();
  
  bus = usb_get_busses();
 // printf("bus %d\n",bus);
  for(bus = usb_get_busses(); bus; bus = bus->next) {
      for(dev = bus->devices; dev; dev = dev->next) {
     
          //printf("idVendor=%d, idProduct=%d\n", dev->descriptor.idVendor, dev->descriptor.idProduct);
      
          if((dev->descriptor.idVendor == LCD2USB_VID) && 
             (dev->descriptor.idProduct == LCD2USB_PID)) {
                
              //printf("Found LCD2USB device on bus %s device %s.\n", bus->dirname, dev->filename);
                
              /* open device */
              if(!(handle = usb_open(dev))) 
                  fprintf(stderr, "Error: Cannot open USB device: %s\n", 
                          usb_strerror());
                
              break;
          }
      }
  }
    
  if(!handle) {
	  
      fprintf(stderr, "Error (no handle): Could not find LCD2USB device\n");
      exit(-1);
  }    
    
    
  if (argc < 2)
  {
      char c;
      
      /* While there is some input data, send it to lcd */
      
      do
      {
          c=getchar();
          if (c<0) break;

          switch (c)
          {
             case 8:   //Backspace
                 lcd_backspace(); 
                 break;
                  
             case 10:  // line feed
                 break; // ignore for now 

             case 27:  // escape sequence to clear screen
                 putchar(c);
                 c=getchar(); if (c<0) break;
                 if (c != '[') break;
                 putchar(c);
                 c=getchar(); if (c<0) break;                 
                 if (c != '2') break;
                 putchar(c);
                 c=getchar(); if (c<0) break;
                 if (c != 'J') break;
                 lcd_clear();
                 break; 

             default: lcd_enqueue(LCD_DATA | LCD_CTRL_0, c); 
                      lcd_flush();
          }
          if (c<0) break;

          putchar(c);
      } while (1);
  }
  else
  {
      int x,y,curx;
	  char c;
	  char line[MAX_LINE_LENGTH];
	  int input_window_width;
      
      switch(argv[1][0])
      {
         case 'o':   // Set Contrast
              if (argc >= 3)
              {    
                x=atoi(argv[2]);
                lcd_set_contrast(x);
              }
              break;
              
         case 'b':   // Set brightness
              if (argc >= 3)
              {    
                  x=atoi(argv[2]);
                  lcd_set_brightness(x);
              }
              break;
              
         case 'c':   // erase
              lcd_clear();
              break;
              
         case 'g':   // Go To X,Y coordinates
              if (argc >= 4)
              {    
                  x=atoi(argv[2]);
                  y=atoi(argv[3]);
                  lcd_gotoxy(x,y);
              }
              break;
              
         case 'p':   // Print message and exit
              if (argc >= 3)
              {
                  lcd_write(argv[2]);
              }
              break;
			  
		 case 'i':   // read line echoing to LCD   lcd i x y width
              if (argc >= 5)
              {    
                  x=atoi(argv[2]);
                  y=atoi(argv[3]);
				  input_window_width = atoi(argv[4]);
                  lcd_read_line(line, x,y,input_window_width, MAX_LINE_LENGTH);
	    		  printf("%s",line);
			  }
              break;	  
			  
		 case 'j':   // read line echoing to LCD   lcd j x y width
              if (argc >= 3)
              {   
                  curx = x = atoi(argv[2]);
                  y = atoi(argv[3]);
				  lcd_gotoxy(x,y);
				  
				  /* While there is some input data, send it to lcd and echo to screen */
                  do
                  {
                     c=getchar();
                     if (c<0) break;

                     switch (c)
                     {
                        case 8:   //Backspace
                           if (curx>x) 
                           {
                              curx=curx-1;
                              lcd_gotoxy(curx,y);
                           }
                        break;
                  
			            case 10:  // line feed	  
                        case 13:  // carriage return
                           curx=x;
          				   lcd_gotoxy(0,y);
	        			   lcd_write("                    ");
                           lcd_gotoxy(x,y);
                        break;  
                  
                        default: 
                           if (curx<20)
					       {
			                  lcd_enqueue(LCD_DATA | LCD_CTRL_0, c); 
                              lcd_flush();
                              curx++;
					       }
                     }
                     if (c<0) break;
                     putchar(c);
					 
				  } while (1);
			  }
              break;
		 
         default:   // Print usage message and exit
              printUsage();
      }
  }

  usb_close(handle);
  return 0;
}
