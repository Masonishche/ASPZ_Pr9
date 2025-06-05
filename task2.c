#include <stdio.h>
#include <stdlib.h>

int main() {
    // Execute cat /etc/shadow with sudo
    int result = system("sudo cat /etc/shadow");
    if (result != 0) {
        fprintf(stderr, "Error: Failed to execute cat /etc/shadow with sudo\n");
        return 1;
    }
    return 0;
}
