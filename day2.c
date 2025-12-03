#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    FILE *fp=fopen("day2input.txt","r");
    long long sum=0, aid,bid,i,j;
    int mid,k,len,matchflag,invalidflag;
    char comma,strin[40];
    while(fscanf(fp,"%lld-%lld%c",&aid,&bid,&comma)>=2){
        for(i=aid;i<=bid;i++){
            sprintf(strin,"%lld",i);
            len=strlen(strin);
            invalidflag=0;
            for(k=1;k<=len/2;k++){
                if(len%k==0){
                    matchflag=1;
                    for(j=k;j<len;j+=k){
                        if(strncmp(&strin[0],&strin[j],k)!=0){
                            matchflag=0;
                            break;
                        }
                    }
                    if(matchflag==1){
                        invalidflag=1;
                        break;
                    }
                }
            }
            if(invalidflag==1){
                sum+=i;
            }
        }

    }
    printf("The value is %lld",sum);
    fclose(fp);
        
}