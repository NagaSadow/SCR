#include <time.h>

int k=0;

int main(){

  for(;;){
    k++;

    struct timespec tim;
    tim.tv_sec=0;
    tim.tv_nsec=100000;

    nanosleep(&tim,NULL);
  }

  return 0;
}
