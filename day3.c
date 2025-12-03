#include <stdio.h>
#include <string.h>

void main(){
    FILE *fp = fopen("day3input.txt","r");
    int tens,ones=0,i,j,len,max,lastind,start,end,maxi;
    long long sum=0,lineval;
    char strin[100],maxd;
    if(fp==NULL){
        printf("File is invalid");
        return;
    }

    while(fscanf(fp,"%s",&strin)==1){
        len=strlen(strin);
        lineval=0;
        lastind=-1;
        for(i=12;i>0;i--){
            start=lastind+1;
            end=len-i;
            maxd=-1;
            maxi=-1;
            for(j=start;j<=end;j++){
                if(strin[j]=='9'){
                    maxd='9';
                    maxi=j;
                    break;
                }
                if(strin[j]>maxd){
                    maxd=strin[j];
                    maxi=j;            
                }
            }
            lineval=(lineval*10)+(maxd-'0');
            lastind=maxi;
        }
        sum+=lineval;
        
    }
    printf("The sum is %lld",sum);
    fclose(fp);
}