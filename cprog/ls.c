#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    char dirname[256];  // Increased buffer size to handle longer directory paths
    DIR *p;
    struct dirent *d;
    
    // Ask for directory name
    printf("Enter directory name: ");
    scanf("%s", dirname);

    // Open the directory
    p = opendir(dirname);
    if (p == NULL) {
        perror("Cannot find directory");
        exit(1);  // Exit with error code 1
    }

    // Read and print directory entries
    while ((d = readdir(p)) != NULL) {
        printf("%s\n", d->d_name);  // Print each entry (file or folder)
    }

    // Close the directory
    closedir(p);
    
    return 0;
}

