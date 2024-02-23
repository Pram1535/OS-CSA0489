#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd, n;
    char buffer[1024];

    fd = creat("test.txt", 0644);
    if (fd < 0) { perror("Error creating file"); exit(1); }

    write(fd, "Hello, world!\n", 14);
    close(fd);

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) { perror("Error opening file"); exit(1); }

    n = read(fd, buffer, sizeof(buffer) - 1);
    if (n < 0) { perror("Error reading file"); exit(1); }
    buffer[n] = '\0';

    printf("Read from file: %s\n", buffer);
    close(fd);

    fd = open("test.txt", O_WRONLY | O_APPEND);
    if (fd < 0) { perror("Error opening file"); exit(1); }

    write(fd, "This is appended text.\n", 23);
    close(fd);

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) { perror("Error opening file"); exit(1); }

    n = read(fd, buffer, sizeof(buffer) - 1);
    if (n < 0) { perror("Error reading file"); exit(1); }
    buffer[n] = '\0';

    printf("Read from file after appending: %s\n", buffer);
    close(fd);

    return 0;
}

