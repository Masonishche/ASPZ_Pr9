#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_PATH 256

int main() {
    char filename[] = "mixed_perms.txt";
    char command[512];
    pid_t pid;

    // Create file as regular user
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error creating file");
        return 1;
    }
    fprintf(fp, "Mixed permissions test\n");
    fclose(fp);

    // Set ownership to root and mixed permissions
    snprintf(command, 512, "sudo chown root:root %s", filename);
    if (system(command) != 0) {
        fprintf(stderr, "Error changing ownership\n");
        return 1;
    }

    snprintf(command, 512, "sudo chmod 640 %s", filename);
    if (system(command) != 0) {
        fprintf(stderr, "Error changing permissions\n");
        return 1;
    }

    // Fork to test access from another process
    pid = fork();
    if (pid == -1) {
        perror("Error forking");
        return 1;
    } else if (pid == 0) {
        // Child process: attempt to read
        fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "Child: Cannot read file\n");
        } else {
            printf("Child: Can read file\n");
            fclose(fp);
        }

        // Child process: attempt to write
        fp = fopen(filename, "a");
        if (fp == NULL) {
            fprintf(stderr, "Child: Cannot write file\n");
        } else {
            printf("Child: Can write file\n");
            fclose(fp);
        }
        exit(0);
    } else {
        // Parent process: wait for child
        wait(NULL);

        // Parent process: attempt to read
        fp = fopen(filename, "r");
        if (fp == NULL) {
            fprintf(stderr, "Parent: Cannot read file\n");
        } else {
            printf("Parent: Can read file\n");
            fclose(fp);
        }

        // Parent process: attempt to write
        fp = fopen(filename, "a");
        if (fp == NULL) {
            fprintf(stderr, "Parent: Cannot write file\n");
        } else {
            printf("Parent: Can write file\n");
            fclose(fp);
        }
    }

    return 0;
}
