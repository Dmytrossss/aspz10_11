#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_INPUT 1024

int main() {
    char input[MAX_INPUT];
    
    while (1) {
        printf("dumbsh> ");
        
        if (!fgets(input, MAX_INPUT, stdin)) {
            break;
        }
        
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "exit") == 0) {
            break;
        }
        
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Помилка fork");
            continue;
        }
        
        if (pid == 0) {
            execlp(input, input, NULL);
            perror("Помилка виконання команди");
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(pid, &status, 0);
            
            if (WIFEXITED(status)) {
                printf("Процес завершено з кодом: %d\n", WEXITSTATUS(status));
            }
        }
    }
    
    return 0;
}
