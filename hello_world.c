#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
  int add_together(int x, int y) {
    int result = x+y;
    return result;
  }
  int foo = 1;
  int bar = 75;
  add_together(foo, bar);
  for (int i = 0; i < 10; i++){
    puts("a string that previously read ''hello, world!''");
  }
  while(foo <atoi(argv[0])){
    puts("a string that previously read ''hello, world!''");
    foo += 1;
  }
  return 0;
}
