#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int main(void)
{
  	int h, min, s;
  	while(1){
	  	time_t now;
	  	// Renvoie l'heure actuelle
	  	time(&now);
	  	// Convertir au format heure locale
	  	struct tm *local = localtime(&now);
		  h = local->tm_hour;        
		  min = local->tm_min;       
		  s = local->tm_sec;
		  printf("%02d:%02d:%02d\n", h, min, s);//heure
		  //system("date");
		  sleep(1);
		  system("clear");//remplacer par write
	}
  return 0;
}
