#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH 256

int main() {
    char filename[] = "tempfile.txt";
    char command[512];
    FILE *fp;

    // Create file as regular user
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(fp, "Temporary content\n");
    fclose(fp);

    // Change ownership to root
    snprintf(command, 512, "sudo chown root:root %s", filename);
    if (system(command) != 0) {
        fprintf(stderr, "Error changing ownership\n");
        return 1;
    }

    // Change permissions to read-only for others
    snprintf(command, 512, "sudo chmod 644 %s", filename);
    if (system(command) != 0) {
        fprintf(stderr, "Error changing permissions\n");
        return 1;
    }

    // Check read access
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot read file\n");
    } else {
        printf("File is readable\n");
        fclose(fp);
    }

    // Check write access
    fp = fopen(filename, "a");
    if (fp == NULL) {
        fprintf(stderr, "Cannot write to file\n");
    } else {
        printf("File is writable\n");
        fclose(fp);
    }

    return 0;
}
