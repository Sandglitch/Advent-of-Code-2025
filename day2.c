#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    FILE *fp=fopen("day2input.txt","r");
    long long sum=0, aid,bid,i;
    int mid;
    char comma,strin[40];
    while(fscanf(fp,"%lld-%lld%c",&aid,&bid,&comma)>=2){
        for(i=aid;i<=bid;i++){
            sprintf(strin,"%lld",i);
            if(strlen(strin)%2==0){
                mid=(strlen(strin)/2);
                if(strncmp(&strin[0],&strin[mid],mid)==0){
                    sum+=i;
                }

            }
        }

    }
    printf("The value is %lld",sum);
    fclose(fp);
        
}