#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define BUF 128


int main(int argc, char *argv[]){

  int potok_fd[2], licz, plik;
  pid_t pid;
  char bufor[BUF];

  pipe(potok_fd);
  pid = fork();


  if(pid < 0){
    printf("Błąd. Nie udało się utworzyć dziecka.\n");
    exit(-1);
  }


  if(pid == 0){
    close(0); // zamyka standardowe wejście
    dup(potok_fd[0]); // przekierowanie wyjścia z pajpa na stdin
    close(potok_fd[0]);
    close(potok_fd[1]); // trzeba zamknąć, inaczej display będzie czekał i nie pokaże obrazka
    close(1);
    execlp("display", argv[0], NULL);
    exit(0);
  }


  if(pid > 0){
    close(potok_fd[0]);

    plik = open(argv[1], O_RDONLY);

    while((licz = read(plik, bufor, BUF)) > 0)
      write(potok_fd[1], bufor, licz);

    close(potok_fd[1]);
  }
}
