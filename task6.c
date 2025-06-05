#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

int main() {
    char *dirs[] = {getenv("HOME"), "/usr/bin", "/etc"};
    char command[512];
    int i;

    // List permissions for each directory
    for (i = 0; i < 3; i++) {
        printf("Listing permissions for %s:\n", dirs[i]);
        snprintf(command, 512, "ls -l %s", dirs[i]);
        if (system(command) != 0) {
            fprintf(stderr, "Error listing %s\n", dirs[i]);
        }
        printf("\n");
    }

    // Attempt to read, write, execute a sample file in /usr/bin (e.g., ls)
    printf("Testing access to /usr/bin/ls:\n");
    FILE *fp = fopen("/usr/bin/ls", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot read /usr/bin/ls\n");
    } else {
        printf("Can read /usr/bin/ls\n");
        fclose(fp);
    }

    fp = fopen("/usr/bin/ls", "w");
    if (fp == NULL) {
        fprintf(stderr, "Cannot write to /usr/bin/ls\n");
    } else {
        printf("Can write to /usr/bin/ls\n");
        fclose(fp);
    }

    if (system("/usr/bin/ls") == 0) {
        printf("Can execute /usr/bin/ls\n");
    } else {
        fprintf(stderr, "Cannot execute /usr/bin/ls\n");
    }

    return 0;
}
