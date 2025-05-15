#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  //Prompt for input
  printf("$ ");
  

  // Wait for user input
  char input[100];
  //When Using fgets there is a newline character at the end when reading
  //Will Need to remove so that it can print properly
  fgets(input, 100, stdin);
  // Remove the trailing newline
  input[strlen(input) - 1] = '\0';


  //TODO
  //Prints for when the command is invalid for now, all commands are invalid
  printf("%s: command not found", input);
  return 0;
}
