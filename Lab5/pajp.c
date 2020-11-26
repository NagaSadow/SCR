#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define BUF 128

int main(){

  int potok_fd[2], licz, plik;
  pid_t pid;
  char bufor[BUF];
  char nazwa_pliku[50];

  pipe(potok_fd);
  pid = fork();


  if(pid < 0){
    printf("Błąd. Nie udało się utworzyć dziecka.\n");
    exit(-1);
  }


  if(pid == 0){
    close(potok_fd[1]);
    while((licz = read(potok_fd[0], bufor, 5)) > 0){
      write(1, "#", 1);
      write(1, bufor, 5);
      write(1, "#", 1);
    }
    write(1, "\n", 1);

    close(potok_fd[0]);
  }


  if(pid > 0){
    close(potok_fd[0]);
    
    printf("Podaj nazwę pliku:\n");
    scanf("%s", nazwa_pliku);
    
    plik = open(nazwa_pliku, O_RDONLY);
    
    while((licz = read(plik, bufor, BUF)) > 0)
      write(potok_fd[1], bufor, licz);

    close(potok_fd[1]);
  }
}
  
