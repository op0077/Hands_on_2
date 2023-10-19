#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

int main() {
    sem_t *sem;

    sem = sem_open("/my_semaphore1", O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Child process trying to lock the semaphore...\n");

        if (sem_wait(sem) == 0) {
            printf("Child process locked the semaphore.\n");

            sleep(2);

            sem_post(sem);
            printf("Child process released the semaphore.\n");
        } else {
            perror("sem_wait");
        }

        sem_close(sem);
        sem_unlink("/my_semaphore");

    } else {
        printf("Parent process trying to lock the semaphore...\n");

        if (sem_wait(sem) == 0) {
            printf("Parent process locked the semaphore.\n");

            sleep(2);

            sem_post(sem);
            printf("Parent process released the semaphore.\n");
        } else {
            perror("sem_wait");
        }

        sem_close(sem);
        sem_unlink("/my_semaphore");
    }

    return 0;
}