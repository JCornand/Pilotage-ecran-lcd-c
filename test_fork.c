//smb://172.16.0.1/snir2/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // String function definitions 
#include <unistd.h>  // UNIX standard function definitions 
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions 
#include <termios.h> // POSIX terminal control definitions
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

void clear_lcd(int fd)
{
	char cmde_clear[2]={254,88};
	write(fd,cmde_clear,sizeof(cmde_clear));
}

void positionner_curseur (int fd,int colonne, int ligne)
{
	char cmde_position[4]={254,71, colonne, ligne};//row pour rangé
	write(fd,cmde_position,sizeof(cmde_position));//3.4.5 Set cursor position (254 71 [column] [row])
//This command sets the cursor position (text insertion point) to the [column] and [row] specified. Columns
//have values from 1 to 20 (0x01 to 0x14) and rows have values of 1 and 2 (0x01 and 0x02).
}

void heure(int fd_lcd)
{
	int h, min, s;
	time_t now;
	char boite[15]={'\0'};

	struct tm *local;
	//do{
		// Renvoie l'heure actuelle
		//conversion int->string
		
	    //clear_lcd(fd_lcd);
		time(&now);
		// Convertir au format heure locale
		local=localtime(&now);
		h = local->tm_hour;        
		min = local->tm_min;       
		s = local->tm_sec;
		sprintf(boite, "Heure %2d:%2d:%2d", h,min,s);
		positionner_curseur(fd_lcd, 0, 0);
		write(fd_lcd,boite,strlen(boite));
		//printf("%02d:%02d:%02d\n", h, min, s);//heure
		//system("date");
		sleep(1);
	
	//while(1);
}

void decToHex (unsigned char valeur_entiere, char* buf) 
{
	sprintf(buf,"%.2x",valeur_entiere);
}

void decToBin (unsigned char valeur_entiere, char *buf)//calcul de décimal à binairedecToBin(valeur_entiere,tab);
{
	char quotient=0;
	char reste=0;
	int diviseur=2;
	int i;
	buf[8]='\0';//on mets le back slash
	for(i=0;i<8;i++){//on écrase chaque case pour y écrire un zéro
		buf[i]='0';//le zéro en question
	}
	i=7;//remise de i à 7
	do{//on exécute les calculs pour aavoir le binaire
		quotient=valeur_entiere/2;
		reste=valeur_entiere%2;
		buf[i]=reste+48;
		valeur_entiere=quotient;
		i=i-1;
	}
	while (quotient >=diviseur);//+'0'
	buf[i]= quotient +48;
}



int main()
{
	//unsigned char x=0;//récupération du caractère
	int fd_lcd, pip[2], status;
	char var;
	//param_liaison_serie=(19200,N,8,1) port:j0,j1,j2;i²c 0x5c

	fd_lcd = open("/dev/ttyS0",O_RDWR | O_NOCTTY | O_NDELAY); //| O_NDELAY);// /dev/ttyS0 port 1 de linus,ndelay ne mets pas ne pause le programme si problème avec DCD
	//rdwr pour lire et écrire,RDONLY pour lire uniquement

	/* Sauvegarde des nouveaux paramètres de la liaison série */
	if (fd_lcd == -1){
	  /*
	  * Could not open the port.
   	  */
	  perror("open_port: Unable to open /dev/ttyf1 - ");
	  exit(0);
	}
	else{
		struct termios termios_p;
		tcgetattr(fd_lcd, &termios_p);/* Lecture des paramètres courants de la liaison série */
		//termios_p.c_cflag = B9600 | CS8 ;
		cfsetospeed(&termios_p, B9600);
		termios_p.c_cflag &= ~PARENB;
		termios_p.c_cflag &= ~CSTOPB;
		termios_p.c_cflag &= ~CSIZE;
		termios_p.c_cflag |= CS8;
		tcsetattr(fd_lcd, TCSANOW, &termios_p);//rentre les paramètres dedans
		//printf("\nport ouvert\n");
	}
	
	//début de la fourche

	pipe(pip);
	fcntl(pip[0], F_SETFL, O_NONBLOCK);
	pid_t pid;
	pid=fork();
	switch(pid){
		case -1 :
			perror("fork");
			close(fd_lcd);
			exit(EXIT_FAILURE);
			break;
		//cas de l'heure qui tourne
		case 0 : 
			printf("processus fils\n");
			do{
				close(pip[1]);
				read(pip[0], &var, 1);
				heure(fd_lcd);
				
			}
			while(var != 'q');
			break;
		default : 
			printf("je suis le père\n");
			char buf[9];//9 de base
			char decimal[12];
			char lettre=0;
			int valeur_entiere=0;
			while(lettre!='q'){	
				printf("\n*Affichage de l heure par seconde.\n");//1
				printf("*Conversion d une valeur entière(0<= x < 256) en décimal, hexadecimal et binaire.");
				printf("\nc - convertir une donnée.\nq - sortir du programme.\n");
				scanf("%c",&lettre);
				clear_lcd(fd_lcd);
				while(getchar()!='\n');
			
				switch (lettre){
					case 'c':
						printf("*Votre choix: c\n maintenant entrez une valeur à convertir.\n\n");
						scanf("%d",&valeur_entiere);
						
						while(getchar()!='\n');
						if((valeur_entiere <= 255)&&(valeur_entiere >= 0))
						{
							//écriture de entier sur le lcd
							
						    sprintf(decimal, "entier: %d", valeur_entiere);
						    positionner_curseur(fd_lcd, 0, 2);
							write(fd_lcd,decimal,strlen(decimal));
							//printf("\nconversion apparition\n");
							decToBin(valeur_entiere,buf);
							//écriture en binaire
							//char binaire[18];
					    	//sprintf(binaire, "binaire: %s", buf);
					    	positionner_curseur(fd_lcd, 0, 3);

					    	write(fd_lcd,"binaire: b",10);
							write(fd_lcd,buf,strlen(buf));
							//printf("\nvotre nombre en binaire vaut:base2=%s\n",buf);

							decToHex(valeur_entiere,buf);
							//écriture en hexa
							//char hexa[18];
					    	//sprintf(hexa, "hexa: 0x%.2x", buf);
					    	positionner_curseur(fd_lcd, 0, 4);
					    	write(fd_lcd,"hexa: 0x",8);
							write(fd_lcd,buf,strlen(buf));
							//printf("\nvotre nombre en hexadécimal vaut:base16=%s\n",buf);
						}
						else printf("\nerreur nombre invalide\n");
						break;
					case 'q':
						printf("*Votre choix: q\n sortie du programme.\n");
						//envoie du kill au fils
						close(pip[0]);
						write(pip[1],"q",1);
						printf("écriture dans le fils via le pipe\n");
						close(pip[1]);
						wait(&status);
						break;
				}
			}
			break;
	}
	printf("mort lente\n");
	exit(EXIT_SUCCESS);
}