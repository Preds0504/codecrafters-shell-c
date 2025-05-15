#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  //Prompt for input
  printf("$ ");
  

  // Wait for user input
  char input[100];
  fgets(input, 100, stdin);

  //Prints for when the command is invalid for now all commands are invalid
  printf("%s: command not found\n", input);
  return 0;
}
