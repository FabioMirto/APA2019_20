#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);

int main(){
    char src[50], regexp[10];
    char *c;
    printf("Inserisci la stringa sorgente in cui cercare l'espressione regolare\n");
    gets(src);
    printf("Inserisci l'espressione regolare\n");
    scanf("%s", regexp);
    c = cercaRegexp(src, regexp);
    if(c)
        printf("%s", c);
    else
        printf("Espressione regolare non trovata");

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int i, j, k, flag = 1, control = 1;
    for(i = 0; i < strlen(src); i++){
        for (j = 0, k = 0; j < strlen(regexp); j++, k++) {
            if (src[i + k] == regexp[j]) {
                flag = 1;
            } else if (regexp[j] == '.') {
                flag= 1;
            } else if(regexp[j] == '['){
                j++;
                if(regexp[j] == '^'){
                    j++;
                    while(regexp[j] != ']'){
                        if(control == 1 && regexp[j] != src[i + k]){
                            control = 1;
                        } else
                            control = 0;
                        j++;
                    }
                    if (control)
                        flag = 1;
                    else {
                        flag = 0;
                        break;
                    }
                } else {
                    j++;
                    while(regexp[j] != ']'){
                        j++;
                        if(control == 0 && regexp[j] != src[i + k]){
                            control = 0;
                        } else
                            control = 1;
                        j++;
                    }
                    if (control)
                        flag = 1;
                    else {
                        flag = 0;
                        break;
                    }
                }
            }  else if(regexp[j] == '\\'){
                j++;
                if(regexp[j] == 'a' && islower(src[i+k])){
                    flag = 1;
                } else if(regexp[j] == 'A' && isupper(src[i+k])){
                    flag = 1;
                } else{
                    flag = 0;
                    break;
                }
            }
            else {
                flag = 0;
                break;
            }

        }
        if (flag)
            return (src + i);
    }
    if(!flag)
        return NULL;

}
