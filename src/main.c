#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**Maximum possible path legnth*/
#define MAX_PATH_LEN 1024
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
    //Get the path name
    char *path = getenv("PATH");
     if (!path) { 
        printf("%s: not found\n", command); 
        return 0; 
    }
    //Copy the path name
    char buf[strlen(path) + 1];
    strcpy(buf, path);
    //loop through all directories having the : be the delimiter
    for (char *dir = strtok(buf, ":"); dir; dir = strtok(NULL, ":")) {
        char full[MAX_PATH_LEN];
        snprintf(full, sizeof(full), "%s/%s", dir, command);
        if (access(full, X_OK) == 0) {
            printf("%s is %s\n", command, full);
            break;
        }
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
            //handling when user wants type
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
