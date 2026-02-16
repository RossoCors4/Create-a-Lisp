#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

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

long eval_op(long x, char* op, long y){
  if (strcmp(op, "+")==0) { return x+y;}
  if (strcmp(op, "-")==0) { return x-y;}
  if (strcmp(op, "*")==0) { return x*y;}
  if (strcmp(op, "/")==0) { return x/y;}

  if (strcmp(op, "%")==0) { return x%y;}
  return 0;
}
long eval(mpc_ast_t* t){
  /* If tagged as number return it directly*/
  if(strstr(t->tag, "number")){
    return atoi(t->contents);
  }
  /* THe operator is always second child */
  char* op = t->children[1]->contents;

  /* We store the third child in 'x' */
  long x = eval(t->children[2]);

  /* Iterate the remaining children and combineing*/
  int i = 3;
  while(strstr(t->children[i]->tag, "expr")){
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }
  return x;
}
int main(int argc, char** argv) {
  
  /* Create some parsers */
  mpc_parser_t* Number    = mpc_new("number");
  mpc_parser_t* Operator  = mpc_new("operator");
  mpc_parser_t* Expr      = mpc_new("expr");
  mpc_parser_t* Abba      = mpc_new("abba");
  mpc_parser_t* Lispy     = mpc_new("lispy");
  
  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                   \
      number  : /-?[0-9]+/  ;                           \
      operator: '+' | '-' | '*' | '/' | '%' ;                 \
      expr    : <number> | '(' <operator> <expr>+ ')' ; \
      abba    : /[a-b]+/ ;                              \
      lispy   : /^/ <operator> <expr>+ <abba>? /$/ ;            \
    ",
  Number, Operator, Expr, Lispy, Abba);

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
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* on success print the AST */
      //mpc_ast_print(r.output);
      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
    } else {
      /* otherwise print the error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    free(input);
  }
mpc_cleanup(5, Number, Operator, Expr, Abba, Lispy);
return 0;
}
