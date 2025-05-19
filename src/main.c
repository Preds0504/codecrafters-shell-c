#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**Size of list of commands */
#define CMD_LIST_SIZE 3
/**List of Commands*/
char *cmd_list[] = {"echo", "exit", "type"};
/**Will check for valid commands*/
int is_command(char *command) {
  for (int i = 0; i < CMD_LIST_SIZE; i++) {
    if (strcmp(command, cmd_list[i]) == 0) {
        return i;
    } else if (strcmp(command, cmd_list[i]) < 0) {
        return -1;
    }
  }
  return -1;
}

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
        //Get the command
        char *first = strtok(input, " \t");
        //Evaluates the command
        if (strcmp(first, "exit") == 0 ) {
            exit(0);
        } else if (strcmp(first, "echo") == 0 ) {
            printf("%s", input + 5);
        } else if (strcmp(first, "type") == 0) {
            char *second = strtok(NULL, " \t");  
            if (is_command(second) >= 0) {
                printf("%s is a shell builtin", second);
            } else {
                printf("%s: not found", second);
            }
        } else {
            //Last case is the command doesn't exist
            printf("%s: command not found", input);
        }
        printf("\n");
    }

    
    return 0;
}
