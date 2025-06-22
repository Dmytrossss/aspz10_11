#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Початковий процес (PID: %d)\n", getpid());
    
    pid_t pid1 = fork();
    
    if (pid1 < 0) {
        perror("Помилка першого fork");
        return 1;
    }
    
    if (pid1 == 0) {
        printf("Перший дочірній (PID: %d)\n", getpid());
        
        pid_t pid2 = fork();
        
        if (pid2 < 0) {
            perror("Помилка другого fork");
            return 1;
        }
        
        if (pid2 == 0) {
            printf("Другий дочірній (PID: %d)\n", getpid());
        } else {
            wait(NULL);
        }
    } else {
        wait(NULL);
    }
    
    return 0;
}
