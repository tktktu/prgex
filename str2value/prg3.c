#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 100

int _pow10(int exp);
int _digit(int num);
int _msd(int num);
int _delmsd(int num);
int str2value(char str[]);

int main(){
  long i, n, m, sign;
  char str[N];
  //char str[N] = "-123";
  
  printf("INT_MAX = %d\n", INT_MAX);
  printf("INT_MIN = %d\n", INT_MIN);

  scanf("%s", str);

  printf("%d\n", str2value(str));

  return 0;
}

//10のn乗を返す
int _pow10(int n){
  int val = 1, i;
  for(i = 1; i < n; i++){
    val *= 10;
  }
  return val;
}

//int型の桁数を返す
//_digit(1321)なら返り値は4
int _digit(int num){
  int digit = 0;
  while( num != 0 ){
    num = num / 10;
    digit++;
  }
  return digit;
}

//int型numの最上位の桁(Most Significant Digit)を返す
//_msd(1924)なら1を返す
int _msd(int num){
  return num / _pow10(_digit(num));
}

//int型numの最上位の桁(Most Significant Digit)を削除した値を返す
//_delmsd(1924)なら924を返す
int _delmsd(int num){
  return num % _pow10(_digit(num));
}

int str2value(char str[]){
  int i, offset, keta, val = 0;
  int str_digit = 0, cmp;
  int num[N], sign;

  for(i = 0; str[i]; i++){
    if(str[i] != '-')
      str_digit++;
  }

  //strが負の値の場合、INT_MINのみオーバーフローチェック
  //strが正の値の場合、INT_MAXのみオーバーフローチェック
  if(str[0] == '-'){
    sign = -1;
    cmp = INT_MIN;
  }else{
    sign = 1;
    cmp = INT_MAX;
  }

  // (1).文字列の桁数 > INT_MAX(INT_MIN)の桁数
  //     の場合、文字列は必ずオーバーフロー
  // (2).文字列の桁数 < INT_MAX(INT_MIN)の桁数
  //     の場合、文字列は必ずオーバフローを起こさない
  // (3).文字列の桁数 == INT_MAX(INT_MIN)の桁数
  //     の場合、オーバーフローが起こる場合があるので
  //     さらに条件追加
  i = 0;
  if( str_digit > _digit(cmp) ){
    printf("Overflow\n");
    return 0;
  }else if( str_digit == _digit(cmp) ){
    while(str[i]){
      if(str[i] == '-') {
        i++;
        continue;
      }
      //(3.1).str[i] < str[i]に対応するINT_MAX(INT_MIN)の桁の数
      //      オーバーフローが確定したので以降の処理を中断
      //(3.2).str[i] > str[i]に対応するINT_MAX(INT_MIN)の桁の数
      //      オーバーフローは絶対に起こさないのでbreak
      //(3.3).str[i] == str[i]に対応するINT_MAX(INT_MIN)の桁の数
      //      オーバーフローが起こるか判断できないので
      //      valを計算しつつループ継続
      //(補足)strが負の場合、INT_MINと比較する(正の場合、INT_MAXと比較)
      //      このときINT_MINから取り出したn桁目の数に-1(sign)をかけて
      //      正の値に変換している
      //      つまり、不等式の両辺に-1をかけて，
      //      不等号の向きを逆にしている(例:[-3 < -2] -> [3 > 2])
      //      こうすることで，strが正、負の値両方で同じ等式が使える
      if( (str[i] - '0') >  (sign * _msd(cmp)) ){
        printf("Overflow\n");
        return 0;
      }else if((str[i] - '0') <  (sign * _msd(cmp)) ){
        break;
      }
      //符号 * n桁目の数 * 10^str_digit
      val += sign * ((str[i] - '0') * _pow10(str_digit));
      cmp = _delmsd(cmp);
      str_digit--;
      i++;
    }
  }

  //(2)または(3.2)のbreak後の残りの計算
  while(str[i]){
    if(str[i] == '-') {
      i++;
      continue;
    }
    //符号 * n桁目の数 * 10^str_digit
    val += sign * ((str[i] - '0') * _pow10(str_digit));
    str_digit--;
    i++;
  }

  return val;
}
