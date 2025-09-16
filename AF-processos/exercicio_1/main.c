#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    int n_filhos = 2;
    pid_t pid;

    for (int i = 0; i < n_filhos; i++) {
        fflush(stdout);
        pid = fork();

        if (pid < 0) {               
            exit(1);
        }

        if (pid == 0) {
            printf("Processo filho %d criado\n", getpid());
            fflush(stdout);
            exit(0);  // forca a finalizacao do processo filho
        } else {
            wait(NULL);
            printf("Processo pai criou %d\n", pid);
            fflush(stdout);
        }
    }

    printf("Processo pai finalizado!\n");
    return 0;
}
