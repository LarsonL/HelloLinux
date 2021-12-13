#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO_MAX_CHAR 1024
#define FIFO_NAME "/tmp/fifo.1"
#define SEND_AMOUNT 10

void server(int fifofile) {

}

int main() {

    pid_t PID = fork();
    int exit_code, fd;
    

    switch (PID)
    {
        case -1:
            perror("Fork Error");
            break;
        
        case 0:
            printf("Child Process, starting server...\n");
            if ((mkfifo(FIFO_NAME, 0777)<0) && (errno != EEXIST)) {
                perror("FIFO could not generate.");
            }
            printf("Create FIFO Successfully\n");

            fd = open(FIFO_NAME, O_WRONLY, 0);

            unlink(FIFO_NAME);
            
            for (int i=0; i<SEND_AMOUNT; i++) {
                char buffer[FIFO_MAX_CHAR] = {0};
                sprintf(buffer, "Hello Parent (FIFO) %d", i);
                int retval = write(fd, buffer, sizeof(buffer));
                printf("Send msg %d\n", i);
                sleep(1);
            }

            

            break;

        default:
            printf("Sleep for 1 sec for child to go.\n");
            sleep(1);

            printf("Check if file created\n");
            system("ls -al /tmp/fifo.1");

            fd = open(FIFO_NAME, O_RDONLY, 0);
            if (fd < 0) {
                printf("FIFO Read unsuccessfully: %s\n", strerror(errno));
                wait(&exit_code);
                return errno;
            }
            
            int n, count = 0;
            while (1) {
                char buffer[FIFO_MAX_CHAR] = {0};
                n = read(fd, buffer, sizeof(buffer));
                printf("Get: %s\n", buffer);
                count++;
                if(count == SEND_AMOUNT) {
                    break;
                }
            }

            wait(&exit_code);

            break;
    }




    return errno;
}