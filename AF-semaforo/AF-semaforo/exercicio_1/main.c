#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

FILE* out;

sem_t sem_A;
sem_t sem_B;

typedef struct {
    sem_t* meu_semaforo;
    sem_t* outro_semaforo;
    int iters;
} thread_args;

void *thread_a(void *args) {
    thread_args *arg = (thread_args *) args;
    sem_t* sem_A = arg->meu_semaforo;
    sem_t* sem_B = arg->outro_semaforo;
    for (int i = 0; i < arg->iters; ++i) {
        sem_wait(sem_A);
        fprintf(out, "A");
        fflush(stdout);
        sem_post(sem_B);
    }
    return NULL;
}

void *thread_b(void *args) {
    thread_args *arg = (thread_args *) args;
    sem_t* sem_B = arg->meu_semaforo;
    sem_t* sem_A = arg->outro_semaforo;
    for (int i = 0; i < arg->iters; ++i) {
        sem_wait(sem_B);
        fprintf(out, "B");
        fflush(stdout);
        sem_post(sem_A);
    }
    return NULL;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s [ITERAÇÕES]\n", argv[0]);
        return 1;
    }
    int iters = atoi(argv[1]);
    srand(time(NULL));
    out = fopen("result.txt", "w");

    pthread_t ta, tb;

    // Inicializa semáforos
    sem_init(&sem_A, 0, 1);
    sem_init(&sem_B, 0, 1);

    // Cria estrutura de argumentos para as threads
    thread_args arg_A;
    arg_A.meu_semaforo = &sem_A;
    arg_A.outro_semaforo = &sem_B;
    arg_A.iters = iters;

    thread_args arg_B;
    arg_B.meu_semaforo = &sem_B;
    arg_B.outro_semaforo = &sem_A;
    arg_B.iters = iters;

    // Cria threads
    pthread_create(&ta, NULL, thread_a, (void *) &arg_A);
    pthread_create(&tb, NULL, thread_b, (void *) &arg_B);

    // Espera pelas threads
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    // Destrói semáforos
    sem_destroy(&sem_A);
    sem_destroy(&sem_B);

    //Imprime quebra de linha e fecha arquivo
    fprintf(out, "\n");
    fclose(out);
  
    return 0;
}
