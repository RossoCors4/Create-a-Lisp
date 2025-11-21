#include <stdio.h>
#include <stdlib.h>

/* If compiling on Windows, we compile these functions */
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* fake readline function*/
char* readLine(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function*/

void add_history(char* unused) {}

/* Otherwise include the editline header*/
#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv) {

  /*Print version and exit info*/
  puts("iPrompt version 0.0.0.0.0.0.1");
  puts("Press ctrl+c to exit\n");

  /* never ending loop*/
  while (1){

    /* Output our iPrompt */
    char* input =readline("iPrompt>> ");
    /* Read a line, max size 2048 */
    add_history(input);
    /* Echo input to the User*/
    printf("No you're a %s\n", input);
    free(input);
  }
return 0;
}
