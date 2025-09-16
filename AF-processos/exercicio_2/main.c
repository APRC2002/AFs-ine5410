#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

// processos filhos chamam essa funcao para criar 3 netos cada
void criar_netos() {
    for (int i = 0; i < 3; i++) {
        fflush(stdout);
        pid_t pid = fork();

        if (pid < 0) {
            exit(1);
        } else if (pid == 0) {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            fflush(stdout);
            sleep(5);
            printf("Processo %d finalizado\n", getpid());
            fflush(stdout);
            exit(0);
        } else {
            wait(NULL);
        }
    }

    printf("Processo %d finalizado\n", getpid());
    fflush(stdout);
    exit(0);
}

// processo principal chama essa funcao para criar 2 filhos
void criar_filhos() {
    for (int i = 0; i < 2; i++) {
        fflush(stdout);
        pid_t pid = fork();

        if (pid < 0) {
            exit(1);
        } else if (pid == 0) {
            printf("Processo %d, filho de %d\n", getpid(), getppid());
            fflush(stdout);
            criar_netos();
            exit(0);
        } else {
            wait(NULL);
        }
    }
}

int main(int argc, char** argv) {
    criar_filhos();
    printf("Processo principal %d finalizado\n", getpid());
    return 0;
}
