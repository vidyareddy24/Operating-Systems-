#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (fork() == 0) {
        sleep(1);
        char *data = (char*) shmat(shmid, NULL, 0);
        printf("Child read: %s\n", data);
        shmdt(data);
    } else {
        char *data = (char*) shmat(shmid, NULL, 0);
        strcpy(data, "Hello from Parent!");
        shmdt(data);
        wait(NULL);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}

