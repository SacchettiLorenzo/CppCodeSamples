#include <stdio.h>
#include <stdlib.h>

int main() {
    // Your data to be stored
    char data[] = "your_data_here";

    // Set the environment variable
    if (setenv("YOUR_VARIABLE_NAME", data, 1) != 0) {
        perror("Error setting environment variable");
        return 1;
    }

    // Optionally, print the environment variable to verify
    char *env_value = getenv("YOUR_VARIABLE_NAME");
    if (env_value != NULL) {
        printf("Environment variable value: %s\n", env_value);
    } else {
        printf("Environment variable not found\n");
    }

    return 0;
}