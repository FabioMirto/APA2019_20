#include <stdio.h>

int gcd(int a, int b);

int main() {
    int a, b, tmp, res = 0;
    printf("Digita due numeri interi positivi\n");
    scanf("%d %d", &a, &b);

   res = gcd(a, b);
   if(res == 1){
       printf("I numeri '%d' '%d' sono primi tra loro", a, b);
   }else{
       printf("Il massimo comun divisore tra '%d' e '%d' è %d", a, b, res);
   }
    return 0;
}

int gcd(int a, int b){
    int tmp;
    if(b > a){
        tmp = b;
        b = a;
        a = tmp;
    }
    if(a % b == 0){
        return b;
    }
    if(a % 2 == 0 && b % 2 == 0){
        return gcd(a/2, b/2) * 2;
    } else if (a % 2 != 0 && b % 2 == 0){
        return gcd(a , b/2);
    } else if (a % 2 != 0 && b % 2 != 0){
        return gcd((a-b)/2, b);
    } else if (a % 2 == 0 && b % 2 != 0){
        return gcd(a/2, b);
    }
}
