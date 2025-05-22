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

/**  Returns a NULL-terminated argv array.argc_out gets the count (not including the NULL).  */
char **split_line(char *line, int *argc_out)
{
    size_t cap = 4;                 // start small, grow as needed
    size_t len = 0;
    char **argv = malloc(cap * sizeof *argv);
    if (!argv) { perror("malloc"); exit(1); }

    char *tok = strtok(line, " \t\r\n");
    while (tok) {
        if (len + 2 > cap) {        // +2 because we add tok and final NULL
            cap *= 2;
            argv = realloc(argv, cap * sizeof *argv);
            if (!argv) { perror("realloc"); exit(1); }
        }
        argv[len++] = tok;          // store pointer to token
        tok = strtok(NULL, " \t\r\n");
    }
    argv[len] = NULL;               // execvp expects this
    *argc_out = (int)len;
    return argv;
}
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
/**Handles the type command */
int handle_type (const char *command) {
    //If builtin just print it's builtin  
    if (is_builtIn(command) >= 0) {
        printf("%s is a shell builtin", command);
        return 0;
    }
    //Get the path name
    char *path = getenv("PATH");
    //Copy the path name
    char buf[strlen(path) + 1];
    strcpy(buf, path);
    //loop through all directories having the : be the delimiter
    for (char *dir = strtok(buf, ":"); dir; dir = strtok(NULL, ":")) {
        char full[MAX_PATH_LEN];
        //This builds the dir for the access to be called
        snprintf(full, sizeof(full), "%s/%s", dir, command);
        //If it is found it will print its first appearance and stop
        if (access(full, X_OK) == 0) {
            printf("%s is %s", command, full);
            return 0;
        }
    } 
    printf("%s: not found", command);
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
        //Parse through all words
        int argc;
        char **argv = split_line(input, &argc);
        if (argc == 0) { 
            free(argv); 
        }
        //Get the command
        char *first = argv[0];
        //Evaluates the command
        if (strcmp(first, "exit") == 0 ) {
            exit(0);
        } else if (strcmp(first, "echo") == 0 ) {
            //Just prints the command
            printf("%s", input + 5);
        } else if (strcmp(first, "type") == 0) {
            //handling when user wants type
            char *second = argv[1];
            handle_type(second);
        } else {
            //Check for where the command exists
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                exit(1);
            } else if (pid == 0) {
                // Child process: try to run the external command
                execvp(argv[0], argv);
                // If execvp returns, it failed
                perror(argv[0]);
                exit(1);
            } else {
                // Parent process: wait for child to finish
                int status;
                waitpid(pid, &status, 0);
            }
            printf("%s: command not found", input);
        }
        printf("\n");
    }

    
    return 0;
}
