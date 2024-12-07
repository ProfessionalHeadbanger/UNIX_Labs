#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "/tmp/my_fifo"

int main() {
    char buffer[1024];
    // Создаем именованный канал
    mkfifo(FIFO_NAME, 0666);

    printf("Enter text to send (type 'exit' to quit):\n");
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    while (1) {
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Убираем символ новой строки
        write(fd, buffer, strlen(buffer) + 1);
        if (strcmp(buffer, "exit") == 0) {
            break;
        }
    }

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}

