#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // String function definitions 
#include <unistd.h>  // UNIX standard function definitions 
#include <fcntl.h>   // File control definitions
#include <errno.h>   // Error number definitions 
#include <termios.h> // POSIX terminal control definitions 

void decToHex (char valeur_entiere, char* buf) 
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
	char buf[9];
	char lettre=0;
	int valeur_entiere=0;
	while(lettre!='q'){	
		printf("\n*Affichage de l heure par seconde.\n");
		printf("*Conversion d une valeur entière(0<= x < 256) en décimal, hexadecimal et binaire.");
		printf("\nc - convertir une donnée.\nq - sortir du programme.\n");
		scanf("%c",&lettre);
		while(getchar()!='\n');
	
		switch (lettre){
			case 'c':
				printf("*Votre choix: c\n maintenant entrez une valeur à convertir.\n\n");
				scanf("%d",&valeur_entiere);
				while(getchar()!='\n');
				if((valeur_entiere <= 255)&&(valeur_entiere >= 0))
				{
					printf("\nconversion apparition\n");
					decToBin(valeur_entiere,buf);
					printf("\nvotre nombre en binaire vaut:base2=%s\n",buf);
					decToHex(valeur_entiere,buf);
					printf("\nvotre nombre en hexadécimal vaut:base16=%s\n",buf);
				}
				else printf("\nerreur nombre invalide\n");
				break;
			case 'q':
				printf("*Votre choix: q\n sortie du programme.\n");
				break;
		}
	}
	//int y;y=2%2; % donne le reste
	//printf("rés=%d",y);
	exit(0);
}

