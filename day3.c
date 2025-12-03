#include <stdio.h>
#include <string.h>

void main(){
    FILE *fp = fopen("day3input.txt","r");
    int tens,ones=0,i,j,len,max,jolt,sum=0;
    char strin[100];
    if(fp==NULL){
        printf("File is invalid");
        return;
    }

    while(fscanf(fp,"%s",&strin)==1){
        len=strlen(strin);
        max=-1;
        for(i=0;i<len;i++){
            for(j=i+1;j<len;j++){
                ones=strin[j]-'0';
                tens=strin[i]-'0';
                jolt=(tens*10)+ones;
                if(jolt>max){
                    max=jolt;
                }
            }
        }
        sum+=max;
    }
    printf("The sum is %d",sum);
    fclose(fp);
}