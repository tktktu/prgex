#include <stdio.h>
#include <limits.h>

int main(int argc, char *argv[]){
  int i, n = 123456789;

  for(i = 2; n != 1; i++){
    while( (n % i == 0) ){
      printf("* %d ", i);
      n /= i;
    }
  }
  printf("\n");
  return 0;
}
