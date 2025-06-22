#include <stdio.h>
#include <unistd.h>

int main() {
    int counter = 0;
    
    printf("Початкове значення: %d\n", counter);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Помилка fork");
        return 1;
    }
    
    if (pid == 0) {
        counter += 10;
        printf("Дочірній: counter = %d\n", counter);
    } else {
        sleep(1);
        counter += 5;
        printf("Батьківський: counter = %d\n", counter);
    }
    
    return 0;
}
