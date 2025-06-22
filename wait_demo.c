#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Помилка fork");
        return 1;
    }
    
    if (pid == 0) {
        printf("Дочірній процес запущено (PID: %d)\n", getpid());
        sleep(2);
        printf("Дочірній процес завершується\n");
        return 42;
    } else {
        printf("Батьківський процес очікує завершення...\n");
        
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Дочірній процес завершено з кодом: %d\n", WEXITSTATUS(status));
        }
    }
    
    return 0;
}
