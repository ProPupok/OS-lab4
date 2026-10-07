#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

void print_info(const char* process_name, clock_t start_time) {
    clock_t current_time = clock();
    double exec_time_ms = ((double)(current_time - start_time) / CLOCKS_PER_SEC) * 1000.0;
    printf("[%s] PID: %d, Parent PID: %d, Execution time: %.3f ms\n", 
           process_name, getpid(), getppid(), exec_time_ms);
}

int main() {
    clock_t start_time = clock();
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        print_info("Child 1", start_time);
        exit(0);
    } 

    pid2 = fork();
    if (pid2 == 0) {
        print_info("Child 2", start_time);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    print_info("Main Parent", start_time);

    return 0;
}
