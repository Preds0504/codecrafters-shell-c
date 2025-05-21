#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**Size of list of commands */
#define CMD_LIST_SIZE 3
/**List of Commands*/
char *cmd_list[] = {"echo", "exit", "type"};
/**Will check for valid commands*/
int is_builtIn(const char *command) {
  for (int i = 0; i < CMD_LIST_SIZE; i++) {
    if (strcmp(command, cmd_list[i]) == 0) {
        return i;
    } else if (strcmp(command, cmd_list[i]) < 0) {
        return -1;
    }
  }
  return -1;
}

int handle_type (const char *command) {
     
    //If builtin just print it's builtin  
    if (is_builtIn(command) >= 0) {
        printf("%s is a shell builtin", command);
        return 0;
    }
    char *path = getenv("PATH");
     if (!path) { 
        printf("%s: not found\n", command); 
        return 0; 
    }
    return 0;

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
            //Just prints the command
            printf("%s", input + 5);
        } else if (strcmp(first, "type") == 0) {
            char *second = strtok(NULL, " \t");
            handle_type(second);
        } else {
            //Last case is the command doesn't exist
            printf("%s: command not found", input);
        }
        printf("\n");
    }

    
    return 0;
}
