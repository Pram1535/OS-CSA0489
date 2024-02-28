#include <stdio.h>
#include <unistd.h>

void printNumbers(int start, int end, int step, char* label) {
    for (int i = start; i <= end; i += step) {
        printf("%s: %d\n", label, i);
    }
}

int main() {
    int pid;

    for (int i = 0; i < 4; ++i) {
        pid = fork();

        if (pid < 0) {
            printf("Fork failed.\n");
            return 1;
        } else if (pid == 0) {
            // Child process
            if (i == 0) {
                printf("Child %d (PID: %d) - Odd numbers:\n", i + 1, getpid());
                printNumbers(1, 20, 2, "Odd");
            } else if (i == 1) {
                printf("Child %d (PID: %d) - Even numbers:\n", i + 1, getpid());
                printNumbers(2, 20, 2, "Even");
            } else if (i == 2) {
                printf("Child %d (PID: %d) - Multiples of 3:\n", i + 1, getpid());
                printNumbers(3, 20, 3, "Multiple of 3");
            } else if (i == 3) {
                printf("Child %d (PID: %d) - Multiples of 5:\n", i + 1, getpid());
                printNumbers(5, 20, 5, "Multiple of 5");
            }
            return 0;
        }
    }

    // Parent process
    return 0;
}

