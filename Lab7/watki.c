#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


int main(){

  int ilosc_watkow = 3;
  pthread_t id_watkow[ilosc_watkow];


  void *funkcja_watku(void *id){

    int idw = (int) id;
    printf("Hello SCR. Written by thread %d \n", idw);
    pthread_exit(NULL);
  }

  for(int k = 0; k < ilosc_watkow; k++){

    int tmp = pthread_create(&id_watkow[k], NULL, funkcja_watku, (void*) id_watkow[k]);
  }

  pthread_exit(NULL);
}
