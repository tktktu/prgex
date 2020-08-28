#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 100

int str2value(char str[]);

int main(){
  char str[N] = "";
  
  printf("INT_MAX = %d\n", INT_MAX);
  printf("INT_MIN = %d\n", INT_MIN);

  scanf("%s", str);
  
  printf("%d\n", str2value(str));

  //test case
  //printf("%s => %d\n", "2", str2value("2"));
  //printf("%s => %d\n", "0", str2value("0"));
  //printf("%s => %d\n", "-5", str2value("-5"));

  //printf("%s => %d\n", "2147483647", str2value("2147483647"));
  //printf("%s => %d\n", "2147483648", str2value("2147483648"));

  //printf("%s => %d\n", "-2147483648", str2value("-2147483648"));
  //printf("%s => %d\n", "-2147483649", str2value("-2147483649"));
  return 0;
}

int str2value(char str[]){
  int i, val = 0;

  //strが負の値の場合、INT_MINのみオーバーフローチェック
  //strが正の値の場合、INT_MAXのみオーバーフローチェック
  if(str[0] == '-'){
    for(i = 1; str[i]; i++){
      //文字が数字かをチェック
      if( str[i] < '0' || '9' < str[i]){
        printf("Not Number :%s\n", str);
        return 0;
      }
      // val * 10 はオーバーフローを起こすかチェック
      // val * 10 >= INT_MIN を式変形
      if( val >= INT_MIN / 10 ){
        val *= 10;
      }else{
        printf("Overflow\n");
        return 0;
      }
      // val + (-1 * (str[i] - '0') ) はオーバーフローを起こすかチェック
      // val + (-1 * (str[i] - '0') ) >= INT_MIN を式変形
      if( val >= INT_MIN - (-1 * (str[i] - '0')) ){
        val += (-1 * (str[i] - '0'));
      }else{
        printf("Overflow\n");
        return 0;
      }
    }
  }else{
    for(i = 0; str[i]; i++){
      //文字が数字かをチェック
      if( str[i] < '0' || '9' < str[i]){
        printf("Not Number :%s\n", str);
        return 0;
      }
      // val * 10 はオーバーフローを起こすかチェック
      // val * 10 <= INT_MAX を式変形
      if( val <= INT_MAX / 10 ){
        val *= 10;
      }else{
        printf("Overflow\n");
        return 0;
      }
      // val + (str[i] - '0') はオーバーフローを起こすかチェック
      // val + (str[i] - '0') <= INT_MAX を式変形
      if( val <= INT_MAX - (str[i] - '0') ){
        val += (str[i] - '0');
      }else{
        printf("Overflow\n");
        return 0;
      }
    }
  }
  return val;
}
