#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void execute_command(char **args, int num_args, int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);
            close(input_fd);
        }

        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);
            close(output_fd);
        }

        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        if (input_fd != STDIN_FILENO) {
            close(input_fd);
        }

        if (output_fd != STDOUT_FILENO) {
            close(output_fd);
        }

        waitpid(pid, NULL, 0);
    } else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
}

void execute_pipeline(char **args, int num_args) {
    int num_pipes = 0;
    for (int i = 0; i < num_args; i++) {
        if (strcmp(args[i], "|") == 0) {
            num_pipes++;
            args[i] = NULL;
        }
    }

    int input_fd = STDIN_FILENO;
    for (int i = 0; i <= num_pipes; i++) {
        int pipe_fd[2];
        if (pipe(pipe_fd) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        execute_command(&args[input_fd], num_args - input_fd, input_fd, pipe_fd[1]);

        close(pipe_fd[1]);
        input_fd = pipe_fd[0];
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("MyShell> ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        char *args[MAX_ARGS];
        int num_args = 0;

        // Parse input into arguments
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[num_args++] = token;
            token = strtok(NULL, " ");
        }

        if (num_args == 0) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            // Exit the shell
            break;
        } else if (strcmp(args[0], "cd") == 0) {
            // Change directory
            if (num_args != 2) {
                printf("Usage: cd <directory>\n");
                continue;
            }

            if (chdir(args[1]) < 0) {
                perror("chdir");
            }
        } else {
            // Redirect output to temporary file
            char tmp_filename[] = "/tmp/myshellXXXXXX";
            int output_fd = mkstemp(tmp_filename);
            if (output_fd < 0) {
                perror("mkstemp");
                exit(EXIT_FAILURE);
            }

            execute_pipeline(args, num_args);

            // Read and display output from temporary file
            char buffer[MAX_INPUT_SIZE];
            lseek(output_fd, 0, SEEK_SET);
            ssize_t bytes_read = read(output_fd, buffer, sizeof(buffer));
            if (bytes_read < 0) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            buffer[bytes_read] = '\0';
            printf("%s\n", buffer);

            close(output_fd);
            unlink(tmp_filename); // Remove temporary file
        }
    }

    return 0;
}
