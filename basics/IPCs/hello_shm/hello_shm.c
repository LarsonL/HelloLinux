#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHARED_MEM_SIZE 0x400000

int main() {

    printf("System V Shared Memory Management\n");
    pid_t PID = fork();
    int exit_code;
    

    switch (PID)
    {
        case -1:
            perror("Fork Error\n");
            break;

        case 0:
            printf("[Child] Start Process.\n");
            key_t key_c = ftok("/tmp/shm.1", 0);
            int shmid_c = shmget(key_c, SHARED_MEM_SIZE, IPC_CREAT|0666);
            char *p_c = shmat(shmid_c, NULL, 0);

            printf("[Child] Shared Memory Created\n");
            sleep(5);
            memset(p_c, 'A', SHARED_MEM_SIZE);
            printf("[Child] Memory Set Complete\n");
            while(p_c[0] == 'A') {
                sleep(1);
            }
            printf("[Child] Get Value: %c\n", p_c[0]);

            break;
    
        default:
            printf("[Parent] Start Process.\n");
            sleep(1);
            key_t key_p = ftok("/tmp/shm.1", 0);
            int shmid_p = shmget(key_p, SHARED_MEM_SIZE, 0666);
            char *p_p = shmat(shmid_p, NULL, 0);
            printf("[Parent] Shared Memory Connected\n");
            while(p_p[0] != 'A') {
                printf("[Parent] Wait for child to store keyword\n");
                sleep(1);
            }
            printf("[Parent] Get value: %c\n", p_p[0]);
            printf("[Parent] Memory Set Complete\n");
            memset(p_p, 'B', SHARED_MEM_SIZE);
            printf("[Parent] Wait for child to end\n");
            wait(&exit_code);
            
            break;
    }

    

    return 0;
}