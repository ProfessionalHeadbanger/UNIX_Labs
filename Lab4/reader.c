#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "/tmp/my_fifo"

int main() {
    char buffer[1024];
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    while (1) {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            printf("Received: %s\n", buffer);
            if (strcmp(buffer, "exit") == 0) {
                printf("Program exited\n");
                break;
            }
        }
    }

    close(fd);
    return 0;
}

