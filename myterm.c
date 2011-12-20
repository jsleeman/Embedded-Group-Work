/*------------------------------------------------------------
 * Simple terminal in C
 * 
 * Arjan J.C. van Gemund (+ few mods by Mark Dufour)
 *------------------------------------------------------------
 * http://www.st.ewi.tudelft.nl/~gemund/Courses/In4073/Resources/myterm.c
 *
 * Modified again by Pete Hemery - 20/12/2011
 * For use with the USB-PIO cable
 */
#define	FALSE		0
#define	TRUE		1

#include <stdio.h>
#include <termios.h>
#include <unistd.h>


/*------------------------------------------------------------
 * console I/O
 *------------------------------------------------------------
 */
struct termios 	savetty;

void	term_initio()
{
	struct termios tty;

        tcgetattr(0, &savetty);
        tcgetattr(0, &tty);
        tty.c_lflag &= ~(ECHO|ECHONL|ICANON|IEXTEN);
        tty.c_cc[VTIME] = 0;
        tty.c_cc[VMIN] = 0;
        tcsetattr(0, TCSADRAIN, &tty);
}

void	term_exitio()
{
	tcsetattr(0, TCSADRAIN, &savetty);
}

/*------------------------------------------------------------
 * serial I/O (8 bits, 1 stopbit, no parity, 38,400 baud)
 *------------------------------------------------------------
 */
#include <termios.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#define SERIAL_DEVICE 	"/dev/ttyACM0"


int fd_RS232;


int rs232_open(void)
{
  	char 		*name;
  	int 		result;  
  	struct termios	tty;
  
        fd_RS232 = open(SERIAL_DEVICE, O_RDWR | O_NOCTTY);
        assert(fd_RS232>=0);

  	result = isatty(fd_RS232);
  	assert(result == 1);

  	name = ttyname(fd_RS232);
  	assert(name != 0);

  	result = tcgetattr(fd_RS232, &tty);
  	assert(result == 0);

        tty.c_iflag = IGNBRK; /* ignore break condition */
        tty.c_oflag = 0;
        tty.c_lflag = 0;

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; /* 8 bits-per-character */
        tty.c_cflag |= CLOCAL | CREAD; /* Ignore model status + read input */

        cfsetospeed(&tty, B38400); /* set output baud rate */
        cfsetispeed(&tty, B38400); /* set input baud rate */

        tty.c_cc[VMIN]  = 0;
        tty.c_cc[VTIME] = 0;

        tty.c_iflag &= ~(IXON|IXOFF|IXANY);

        result = tcsetattr (fd_RS232, TCSANOW, &tty); /* non-canonical */

        tcflush(fd_RS232, TCIOFLUSH); /* flush I/O buffer */
}


int 	rs232_close(void)
{
  	int 	result;

  	result = close(fd_RS232);
  	assert (result==0);
}

/*----------------------------------------------------------------
 * USB-PIO specific functions
 *----------------------------------------------------------------
 */
#include <string.h>
#define A 0
#define B 1
#define C 2
#define SLEEP 1000

void setup_ports(){
  char out[4];
  write(fd_RS232,"@00D000\r",8);
  read(fd_RS232,out,4);
  usleep(SLEEP);
  write(fd_RS232,"@00D1FF\r",8);
  read(fd_RS232,out,4);
  usleep(SLEEP);
  write(fd_RS232,"@00D200\r",8);
  read(fd_RS232,out,4);
  usleep(SLEEP);
}


void write_to_port(int port, int bits){
  char out[4];
  char str[12];

  snprintf(str,8,"@00P%d%02x\r",port,bits);
  /*printf("%s\n",str);*/
  write(fd_RS232,str,8);
  read(fd_RS232,out,4);
  usleep(SLEEP);
  
}

/*----------------------------------------------------------------
 * main -- execute terminal
 *----------------------------------------------------------------
 */
int main(void)
{
  char	c;
  char out[4];
  int i;
  
  term_initio();
  rs232_open();
  
  setup_ports();

  for(i=0;i<1000;i++){
    write_to_port(A,0x01);
    write_to_port(C,0x80);
    write_to_port(C,0x00);

    write_to_port(A,0x02);
    write_to_port(C,0x70);
    write_to_port(C,0x00);

    write_to_port(A,0x04);
    write_to_port(C,0x80);
    write_to_port(C,0x00);

    write_to_port(A,0x08);
    write_to_port(C,0x01);
    write_to_port(C,0x00);
  }

  /*
  for(i=0;i<1000;i++){
    write(fd_RS232,"@00P001\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);
    write(fd_RS232,"@00P27F\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);

    write(fd_RS232,"@00P200\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);

    write(fd_RS232,"@00P002\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);
    write(fd_RS232,"@00P2FF\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);

    write(fd_RS232,"@00P200\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);

    write(fd_RS232,"@00P004\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);
    write(fd_RS232,"@00P27F\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);

    write(fd_RS232,"@00P200\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);

    write(fd_RS232,"@00P008\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);
    write(fd_RS232,"@00P2FF\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);

    write(fd_RS232,"@00P200\r",8);
    read(fd_RS232,out,4);
    usleep(SLEEP);
  }
  */
  /* discard any incoming text
   */
  /*
    while ((c = rs232_getchar_nb()) != -1)
    fputc(c,stderr);

    for (;;) {
    if ((c = term_getchar_nb()) != -1) {
    rs232_putchar(c);
    }
    if ((c = rs232_getchar_nb()) != -1) {
    term_putchar(c);
    }
    }
  */
  term_exitio();
  rs232_close();
  /*term_puts("\n<exit>\n");*/
  return 0;
}
