#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_CMD_LEN];
    char *args[MAX_ARGS];

    while (1) {
        printf("my_shell> ");
        if (fgets(input, MAX_CMD_LEN, stdin) == NULL){
            break;
        }

        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) {
            continue;
        }

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL && i < MAX_ARGS - 1) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        int background = 0;
        if (i > 0 && strcmp(args[i-1], "&") == 0) {
            background = 1;
            args[i-1] = NULL;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
        } else if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                perror("Command execution failed");
            }
            exit(1);
        } else {
            if (!background) {
                waitpid(pid, NULL, 0);
            } else {
                printf("[Process running in background with PID %d]\n", pid);
            }
        }
    }
    return 0;
}