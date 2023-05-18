#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	status = 0;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process\n");
        exit(128);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child exited with status: %d\n",status);
        }
    } else {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }

    return 0;
}
