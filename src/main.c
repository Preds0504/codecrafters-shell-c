#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char * input;
    int buffer = 100;


  // Flush after every printf
  setbuf(stdout, NULL);

  //This will print the $
  //This is the prompt for the new command
  printf("$ ");
  //Takes input from the command line
  fgets(input, buffer, stdin);
  printf("%s: command not found\n", input);

  // Wait for user input
  char input[100];
  fgets(input, 100, stdin);
  return 0;
}
