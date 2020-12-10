#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){

  int fd_wsp, fd;
  int rozmiar_pliku_wsp, rozmiar_pliku;
  char nazwa_pliku_wsp[50];
  char nazwa_pliku[50];
  struct stat dane_pliku_wsp, dane_pliku;

  printf("Podaj nazwę pliku współdzielonego:\n");
  scanf("%s", nazwa_pliku_wsp);

  stat(nazwa_pliku_wsp, &dane_pliku_wsp);
  rozmiar_pliku_wsp = dane_pliku_wsp.st_size;

  fd_wsp = open(nazwa_pliku_wsp, O_RDWR);

  char* wsk_wsp = (char*)mmap(NULL, rozmiar_pliku_wsp, PROT_READ | PROT_WRITE, MAP_SHARED, fd_wsp, 0);

  printf("wsk_wsp: %s\n", wsk_wsp);


  while(1){

    printf("Podaj nazwę pliku:\n");
    scanf("%s", nazwa_pliku);

    fd = open(nazwa_pliku, O_RDONLY);

    stat(nazwa_pliku, &dane_pliku);
    rozmiar_pliku = dane_pliku.st_size;

    truncate(nazwa_pliku_wsp, rozmiar_pliku);
    char* wsk = (char*)mmap(NULL, rozmiar_pliku, PROT_READ | PROT_WRITE, MAP_SHARED, fd_wsp, 0);
    read(fd, wsk, rozmiar_pliku);

     printf("wsk: %s\n", wsk);

    
  }
}
