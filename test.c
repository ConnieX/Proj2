#include <stdio.h>

int test(int* p){
    *p = 10;
    printf("P: %d", *p);
    return 1;
}

int main(){
    int x = 5;
    test(&x);
    printf("X: %d", x);
}