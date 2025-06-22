#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Помилка fork");
        return 1;
    }
    
    if (pid == 0) {
        for (int i = 0; i < 3; i++) {
            printf("Дочірня: Ітерація %d (PID: %d)\n", i+1, getpid());
            sleep(1);
        }
    } else {
        for (int i = 0; i < 3; i++) {
            printf("Батьківськa: Ітерація %d (PID: %d)\n", i+1, getpid());
            sleep(1);
        }
    }
    return 0;
}
