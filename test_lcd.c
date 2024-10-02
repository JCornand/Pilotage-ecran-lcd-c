#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // String function definitions 
#include <unistd.h>  // UNIX standard function definitions 
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions 
#include <termios.h> // POSIX terminal control definitions 

void clear_lcd(int fd)
{
	char cmde_clear[2]={254,88};
	write(fd,cmde_clear,sizeof(cmde_clear));

}

int main() 
{
	//unsigned char x=0;//récupération du caractère
	int fd_lcd;
	//param_liaison_serie=(19200,N,8,1) port:j0,j1,j2;i²c 0x5c

	fd_lcd = open("/dev/ttyS0",O_RDWR | O_NOCTTY | O_NDELAY); //| O_NDELAY);// /dev/ttyS0 port 1 de linus,ndelay ne mets pas ne pause le programme si problème avec DCD
	//rdwr pour lire et écrire,RDONLY pour lire uniquement
	struct termios termios_p;
	tcgetattr(fd_lcd, &termios_p);/* Lecture des paramètres courants de la liaison série */
	termios_p.c_cflag = B9600 | CS8 ;
	cfsetospeed(&termios_p, B9600);
	tcsetattr(fd_lcd, TCSANOW, &termios_p);//rentre les paramètres dedans
	/* Sauvegarde des nouveaux paramètres de la liaison série */
	if (fd_lcd == -1){
	  /*
	  * Could not open the port.
   	  */
	  perror("open_port: Unable to open /dev/ttyf1 - ");
	  exit(0);
	}
	else{
		printf("\nport ouvert\n");
	}
	clear_lcd(fd_lcd);
	write(fd_lcd,"xcm", 1);
	close(fd_lcd);//ferme le socket

	exit(0);
}