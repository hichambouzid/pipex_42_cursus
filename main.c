#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
 #include <sys/wait.h>
 
int main() {
    int i;
    pid_t pid;

    // Create 3 child processes using fork()
    for (i = 0; i < 3; i++) {
        pid = fork();

        if (pid == 0) { // Child process
            printf("Child %d with PID %d\n", i + 1, getpid());
            // Child process exits after printing
            return 0;
        } else if (pid < 0) { // Error handling
            perror("fork failed");
            return 1;
        }
    }

    // Parent process
    // Wait for all child processes to complete
    for (i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Parent process with PID %d\n", getpid());

    return 0;
}
