#include <stdio.h>
#include <string.h>

int main() {
    char fn[100], pat[100], temp[200];
    FILE *fp;
    
    // Get file name
    printf("Enter file name: ");
    scanf("%s", fn);

    // Get pattern to search for
    printf("Enter pattern to be searched: ");
    scanf("%s", pat);

    // Open file for reading
    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1; // Exit if the file can't be opened
    }

    // Read each line and check for the pattern
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        if (strstr(temp, pat)) {
            printf("%s", temp); // Print the line if the pattern is found
        }
    }

    // Close the file
    fclose(fp);

    return 0;
}

