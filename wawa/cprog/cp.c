#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char **argv) {
    char buffer[1024];
    int src_fd, dest_fd;
    ssize_t count;

    // Check for insufficient parameters
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return -1;
    }

    // Open the source file for reading
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file");
        return -1;
    }

    // Open the destination file for writing (create it if necessary)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);  // Create with rw-r--r-- permissions
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(src_fd);
        return -1;
    }

    // Copy data from source to destination
    while ((count = read(src_fd, buffer, sizeof(buffer))) > 0) {
        ssize_t written = 0;
        while (written < count) {
            ssize_t bytes = write(dest_fd, buffer + written, count - written);
            if (bytes == -1) {
                perror("Error writing to destination file");
                close(src_fd);
                close(dest_fd);
                return -1;
            }
            written += bytes;
        }
    }

    if (count == -1) {
        perror("Error reading from source file");
        close(src_fd);
        close(dest_fd);
        return -1;
    }

    // Close the files
    close(src_fd);
    close(dest_fd);

    return 0;  // Success
}

