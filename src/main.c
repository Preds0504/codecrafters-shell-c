#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {  
    // Flush after every printf
    setbuf(stdout, NULL);



    while(true) {
        //Prompt for input
        printf("$ ");
        

        // Wait for user input
        char input[100];
        //When Using fgets there is a newline character at the end when reading
        //Will Need to remove so that it can print properly
        fgets(input, 100, stdin);
        // Remove the trailing newline
        input[strlen(input) - 1] = '\0';
        //Prints for when the command is invalid for now, all commands are invalid
        if (strcmp(input, "exit 0") == 0 ) {
            exit(0);
        } else if (strncmp(input, "echo", 4) == 0 ) {
            printf("%s\n", input + 5);
        } else {
            //Last case is the command doesn't exist
            printf("%s: command not found", input);
        }
        printf("\n");
    }

    
    return 0;
}
