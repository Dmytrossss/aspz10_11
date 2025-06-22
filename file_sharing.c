#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd = open("shared.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    if (fd < 0) {
        perror("Помилка відкриття файлу");
        return 1;
    }
    
    const char *parent_msg = "Батьківський процес\n";
    const char *child_msg = "Дочірній процес\n";
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Помилка fork");
        close(fd);
        return 1;
    }
    
    if (pid == 0) {
        write(fd, child_msg, strlen(child_msg));
        printf("Дочірній процес записав у файл\n");
    } else {
        write(fd, parent_msg, strlen(parent_msg));
        printf("Батьківський процес записав у файл\n");
    }
    
    close(fd);
    return 0;
}
