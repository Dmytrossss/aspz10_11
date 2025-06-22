#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Початок програми (PID: %d)\n", getpid());
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Помилка при виклику fork()");
        return 1;
    }
    
    if (pid == 0) {
        printf("Дочірній процес (PID: %d, PPID: %d)\n", getpid(), getppid());
    } else {
        printf("Батьківський процес (PID: %d, Дочірній PID: %d)\n", getpid(), pid);
    }
    
    printf("Завершення процесу (PID: %d)\n", getpid());
    return 0;
}
