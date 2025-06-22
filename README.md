### Звіт з виконання лабораторної роботи №10_11
 

**Система:** Linux Mint 22.1 'Xia' MATE Edition (VirtualBox)  

**Виконавець: Гнилицький Дмитро**  

**Група: ТВ-33**

**Варіант №3** 

---

### **Завдання: 1**  
**Пункт лекції:** 2.1, 2.3 (Як працює fork(), Використання системного виклику fork)  
**Код (`fork_demo.c`):**  
```c
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
```

**Вивід:**

![image](https://github.com/user-attachments/assets/9984769a-7e89-4e63-9996-6f9fa159664b)


```
dima@dima-VirtualBox:~/aspz10_11$ ./fork_demo
Початок програми (PID: 3432)
Батьківський процес (PID: 3432, Дочірній PID: 3433)
Завершення процесу (PID: 3432)
Дочірній процес (PID: 3433, PPID: 1)
Завершення процесу (PID: 3433)
```

**Висновок:**  
Демонстрація базового використання `fork()`, що відповідає пункту 2.3 лекції. Виклик `fork()` створює новий процес, який є копією батьківського.

---

### **Завдання: 2**  
**Відповідає пункту лекції:** 2.4 (Експеримент: імітація роботи в процесах)  
**Код (`process_work.c`):**  
```c
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
```

**Вивід:**

![image](https://github.com/user-attachments/assets/c19664b9-02a3-4ee4-b316-2f1a6f8879b4)


```
dima@dima-VirtualBox:~/aspz10_11$ ./process_work
Батьківськa: Ітерація 1 (PID: 3435)
Дочірня: Ітерація 1 (PID: 3436)
Батьківськa: Ітерація 2 (PID: 3435)
Дочірня: Ітерація 2 (PID: 3436)
Батьківськa: Ітерація 3 (PID: 3435)
Дочірня: Ітерація 3 (PID: 3436)
```

**Висновок:**  
Експеримент демонструє паралельне виконання батьківського та дочірнього процесів, що відповідає пункту 2.4 лекції. Вивід показує чергування ітерацій між процесами.

---

### **Завдання: 3**  
**Відповідає пункту лекції:** 2.5 (Копіювання даних при fork)  
**Код (`data_copy.c`):**  
```c
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
```

**Вивід:**

![image](https://github.com/user-attachments/assets/cf68d813-ebc3-40e2-93ad-d48d7417b9b4)


```
dima@dima-VirtualBox:~/aspz10_11$ ./data_copy
Початкове значення: 0
Дочірній: counter = 10
Батьківський: counter = 5
```

**Висновок:**  
Експеримент ілюструє механізм копіювання пам'яті при виклику `fork()`, що відповідає пункту 2.5 лекції. Кожен процес працює зі своєю копією змінних.

---

### **Завдання: 4**  
**Відповідає пункту лекції:** 2.6 (Процеси та відкриті файли)  
**Код (`file_sharing.c`):**  
```c
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
```

**Вивід:**

![image](https://github.com/user-attachments/assets/41eb5371-f7bd-4192-a4a3-c10c074e11bf)


```
dima@dima-VirtualBox:~/aspz10_11$ ./file_sharing
cat shared.txt
Батьківський процес записав у файл
Дочірній процес записав у файл
Батьківський процес
Дочірній процес
```

**Висновок:**  
Демонстрація спільного доступу до файлів після `fork()`, що відповідає пункту 2.6 лекції. Обидва процеси записують в один файл через успадкований файловий дескриптор.

---

### **Завдання: 5**  
**Відповідає пункту лекції:** 2.7, 2.8 (Проєкт: Dumb Shell, Запуск dumbsh)  
**Код (`dumbsh.c`):**  
```c
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
```

**Тестування:**

![image](https://github.com/user-attachments/assets/853502e2-b39a-4190-883f-c21097e3b566)


```
dima@dima-VirtualBox:~/aspz10_11$ ./dumbsh
dumbsh> ls
data_copy      dumbsh	       fork_demo       multiple_forks.c  wait_demo
data_copy.c    dumbsh.c        fork_demo.c     process_work	 wait_demo.c
double_fork    file_sharing    Makefile        process_work.c
double_fork.c  file_sharing.c  multiple_forks  shared.txt
Процес завершено з кодом: 0
dumbsh> whoami
dima
Процес завершено з кодом: 0
dumbsh> exit

```

**Висновок:**  
Реалізація простої оболонки, що відповідає пунктам 2.7-2.8 лекції. Використовує комбінацію `fork()`, `execlp()` і `waitpid()` для виконання команд.

---

### **Завдання: 6**  
**Відповідає пункту лекції:** 2.9 (API wait — деталі)  
**Код (`wait_demo.c`):**  
```c
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
```

**Вивід:**

![image](https://github.com/user-attachments/assets/e2134f8e-b847-4bc7-914e-26bec2fab06e)


```
dima@dima-VirtualBox:~/aspz10_11$ ./wait_demo
Батьківський процес очікує завершення...
Дочірній процес запущено (PID: 3448)
Дочірній процес завершується
Дочірній процес завершено з кодом: 42

```

**Висновок:**  
Демонстрація роботи `waitpid()` для отримання статусу завершення дочірнього процесу, що відповідає пункту 2.9 лекції.

---

### **Завдання: 7**  
**Відповідає пункту лекції:** 2.10 (Fork Bomb та створення декількох дітей)  
**Код (`multiple_forks.c`):**  
```c
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
```

**Вивід:**

![image](https://github.com/user-attachments/assets/13ca5867-aca8-4fcd-98dc-409a2ff7dfdb)


```
dima@dima-VirtualBox:~/aspz10_11$ ./multiple_forks
Дочірній 1 (PID: 3451)
Дочірній 2 (PID: 3452)
Дочірній 3 (PID: 3453)
Всі дочірні процеси завершено

```

**Висновок:**  
Створення кількох дочірніх процесів у циклі, що відповідає пункту 2.10 лекції. Батьківський процес очікує завершення всіх дітей.

---

### **Завдання: Варіант №3**  

**Код (`double_fork.c`):**  
```c
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
```

**Вивід:**

![image](https://github.com/user-attachments/assets/1ad32c36-c53e-4d61-98b4-6b4dbfc127ed)


```
dima@dima-VirtualBox:~/aspz10_11$ ./double_fork
Початковий процес (PID: 3454)
Перший дочірній (PID: 3455)
Другий дочірній (PID: 3456)

```

**Висновок:**  
Виконання практичного завдання з подвійного виклику `fork()`. Створення ієрархії процесів: батько -> дитина -> онук.

---

### **Makefile для керування проектом**  
```makefile
CC = gcc
CFLAGS = -Wall -Wextra
TARGETS = fork_demo process_work data_copy file_sharing dumbsh wait_demo multiple_forks double_fork

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) shared.txt
```
