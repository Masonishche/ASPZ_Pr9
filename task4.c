#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Executing whoami:\n");
    if (system("whoami") != 0) {
        fprintf(stderr, "Error executing whoami\n");
        return 1;
    }

    printf("\nExecuting id:\n");
    if (system("id") != 0) {
        fprintf(stderr, "Error executing id\n");
        return 1;
    }

    return 0;
}
