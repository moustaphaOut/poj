#include <stdio.h>

int main(){
    float average=0, balance;

    while(scanf("%f",&balance)!=EOF)
        average += balance;
    
    printf("$%.2f\n",average/12);
    
    return 0;
}

