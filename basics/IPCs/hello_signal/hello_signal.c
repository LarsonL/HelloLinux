#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PARENT_PRINT_DELAY 2
#define CHILD_DELAY_TIME 5

int parent_lock = 0;

void sig_usr1(int signum) {
    if (signum == SIGUSR1) {
        parent_lock = 1;
    }
}

int main() {
    
    // Register a signal
    signal(SIGUSR1, sig_usr1);

    pid_t PID = fork();
    int exit_code;
    

    switch (PID)
    {
        case -1:
            perror("Fork Error\n");
            break;

        case 0:
            printf("[Child] Process Start!\n");
            sleep(CHILD_DELAY_TIME);
            printf("[Child] Trigger the signal!\n");
            kill(getppid(), SIGUSR1);
            break;
        
        default:
            printf("[Parent] Start, wait for Signal\n");
            // Sleep to wait for signal
            while(parent_lock == 0) {
                printf("[Parent] Waiting for child signal...\n");
                sleep(PARENT_PRINT_DELAY);
            }
            printf("[Parent] Get the signal!\n");
            parent_lock = 0;
            wait(&exit_code);
            break;
    }
    

    return 0;
}