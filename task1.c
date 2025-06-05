#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main() {
    FILE *fp;
    char line[MAX_LINE];
    char *username, *uid_str;
    int uid;
    int regular_users = 0;

    // Execute getent passwd command
    fp = popen("getent passwd", "r");
    if (fp == NULL) {
        perror("Error executing getent passwd");
        return 1;
    }

    printf("Regular users (UID > 1000):\n");
    // Read output line by line
    while (fgets(line, MAX_LINE, fp) != NULL) {
        // Parse username:password:uid:...
        username = strtok(line, ":");
        strtok(NULL, ":"); // Skip password
        uid_str = strtok(NULL, ":"); // Get UID
        uid = atoi(uid_str);

        // Check for regular users (UID > 1000)
        if (uid > 1000) {
            printf("%s (UID: %d)\n", username, uid);
            regular_users++;
        }
    }

    pclose(fp);
    printf("Total regular users found: %d\n", regular_users);
    return 0;
}
