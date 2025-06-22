#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("Помилка fork");
            return 1;
        }
        
        if (pid == 0) {
            printf("Дочірній %d (PID: %d)\n", i+1, getpid());
            sleep(1);
            return 0;
        }
    }
    
    while (wait(NULL) > 0);
    printf("Всі дочірні процеси завершено\n");
    return 0;
}
