// Написать программу на языке С/С++, которая породит ровно n (число n считывается при запуске) процессов-потомков. Каждый потомок должен вывести свой PID на экран и завершиться. Родительский процесс должен дождаться завершения всех процессов-потомков, вывести сообщение "Все n процессов-потомков завершены" и завершиться. В коде процесса-потомка должен быть по крайней мере один вызов fork().

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_processes(int remaining) {
    if (remaining <= 0) return; // Базовый случай: больше не нужно порождать процессы

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Мы в потомке
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        // Порождаем следующие процессы
        create_processes(remaining - 1);
        exit(0); // Завершаем потомка, чтобы он не продолжал цикл родителя
    } else {
        // Родительский процесс ждет завершения потомка
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Number of processes must be a positive integer.\n");
        return 1;
    }

    printf("Parent process: PID = %d\n", getpid());
    create_processes(n); // Запускаем создание потомков
    printf("Все %d процессов-потомков завершены.\n", n);
    return 0;
}


