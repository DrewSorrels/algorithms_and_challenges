#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


bool cells[601][601] = { { false } } ;

int max(int first, int second){
  if(first > second){
    return first;
  } else {
    return second;
  }
}

bool inBounds(int x, int y){
  return x >= 0 && y >= 0 && x < 601 && y < 601;
}

int sumDigits(int x, int y){
  int sum = 0;
  x -= 300;
  y -= 300; // Normalize cells so that (200, 200) becomes (0, 0)
  x = abs(x);
  y = abs(y);

  //printf("(%d, %d)", x, y);
  while(x != 0){
    sum += x % 10;
    x /= 10;
  }
  while( y != 0){
    sum += y % 10;
    y /= 10;
  }
  return sum;
}

int visitCell(int x, int y){
  if(inBounds(x, y)){
    if(cells[x][y] || sumDigits(x, y) > 19){
      return 0;
    }
    cells[x][y] = true;
  } else {
    return 0;
  }
  return 1 + visitCell( x + 1, y ) + visitCell( x - 1, y ) + visitCell( x, y + 1 ) + visitCell( x, y - 1 );
  //return 1 + max( max( visitCell( x + 1, y ), visitCell( x - 1, y )), max( visitCell( x, y + 1 ), visitCell( x, y - 1 )));
}

int length(){
  return 401; //sizeof(cells) / sizeof(cells[0]);
}

void main(){

  int distance = visitCell(300, 300);
  printf("\"%d\"", distance);
}