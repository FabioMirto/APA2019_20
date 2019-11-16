#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);

int main(){
    char src[50], regexp[10];
    char *c;
    gets(src);
    scanf("%s", regexp);
    c = cercaRegexp(src, regexp);
    if(c)
        printf("%s", c);
    else
        printf("Espressione regolare non trovata");

    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int i, j, k, f = 1, c = 1;
    for(i = 0; i < strlen(src); i++){
        for (j = 0, k = 0; j < strlen(regexp); j++, k++) {
            if (src[i + k] == regexp[j]) {
                f = 1;
            } else if (regexp[j] == '.') {
                f = 1;
            } else if(regexp[j] == '\\'){
                j++;
                if(regexp[j] == 'a' && islower(src[i+k])){
                    f = 1;
                } else if(regexp[j] == 'A' && isupper(src[i+k])){
                    f = 1;
                } else{
                    f = 0;
                    break;
                }
            } else if(regexp[j] == '['){
                j++;
                if(regexp[j] == '^'){
                    j++;
                    while(regexp[j] != ']'){
                        if(c == 1 && regexp[j] != src[i +k]){
                            c = 1;
                        } else
                            c = 0;
                        j++;
                    }
                    if (c)
                        f = 1;
                    else {
                        f = 0;
                        break;
                    }
                } else {
                    j++;
                    while(regexp[j] != ']'){
                        j++;
                        if(c == 0 && regexp[j] != src[i +k]){
                            c = 0;
                        } else
                            c = 1;
                        j++;
                    }
                    if (c)
                        f = 1;
                    else {
                        f = 0;
                        break;
                    }
                }
            }
            else {
                f = 0;
                break;
            }

        }
        if (f)
            return (src + i);
    }
    if(!f)
        return NULL;
}
