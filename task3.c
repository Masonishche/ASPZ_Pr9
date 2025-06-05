#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_PATH 256

int main() {
    char filename[] = "testfile.txt";
    char homedir[MAX_PATH];
    char copy_path[MAX_PATH];
    char command[512];

    // Get home directory
    snprintf(homedir, MAX_PATH, "%s", getenv("HOME"));

    // Create file as regular user
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(fp, "Test content\n");
    fclose(fp);

    // Copy file as root to home directory
    snprintf(copy_path, MAX_PATH, "%s/copied_testfile.txt", homedir);
    snprintf(command, 512, "sudo cp %s %s", filename, copy_path);
    if (system(command) != 0) {
        fprintf(stderr, "Error copying file with sudo\n");
        return 1;
    }

    // Attempt to modify copied file as regular user
    fp = fopen(copy_path, "a");
    if (fp == NULL) {
        fprintf(stderr, "Cannot modify file: Permission denied\n");
    } else {
        fprintf(fp, "Modified content\n");
        fclose(fp);
        printf("File modified successfully\n");
    }

    // Attempt to delete file with rm
    snprintf(command, 512, "rm %s", copy_path);
    printf("Attempting to delete file with rm...\n");
    if (system(command) != 0) {
        fprintf(stderr, "Error: Cannot delete file with rm\n");
    } else {
        printf("File deleted successfully\n");
    }

    return 0;
}
