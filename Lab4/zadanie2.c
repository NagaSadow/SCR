#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>



int flag =0;


void sygnaly(int signal){
  
  printf("Sygnał: ");
  
  if(signal==14){
    printf("SIGALRM\n");
    printf("Zamykam program\n");
    exit(1);
  }

  if(signal==15){
    printf("SIGTERM\n");
    printf("Kontynuuje działanie\n");
  }

  if(signal==10){
    printf("SIGUSR1\n");
    printf("Zatrzymuje odbieranie sygnałów\n");
    flag=1;
  }
}




int main(){

  
  signal(SIGUSR2,SIG_IGN); //ignoruje SIGUSR2

  int k=0;
  int tmp=0;


  for(;;){

    k++;

    printf("Przejście pętli nr: %i\n",k);

    
    struct timespec tim;
    tim.tv_sec=0;
    tim.tv_nsec=100000000L;

    nanosleep(&tim,NULL);


    if(flag==0){
      signal(SIGALRM,sygnaly);
      signal(SIGTERM,sygnaly);
      signal(SIGUSR1,sygnaly);
    }

    if(flag==1){
      signal(SIGALRM,SIG_IGN);
      signal(SIGTERM,SIG_IGN);
      signal(SIGUSR1,SIG_IGN);

      if(tmp<k)
	tmp=k+500; //liczba interacji czekania

      if(k==tmp){
	printf("Znów łapie sygnały\n");
	flag=0;
      }
    }
  }
  return 0;
}
