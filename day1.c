#include <stdio.h>
#include <stdlib.h>

int main(){
    int i=50,num,count=0;
    char ip[100],alpha;
    FILE *fp;
    fp=fopen("day1input.txt","r");
    if(fp==NULL){
        printf("File was not found");
        return 1;
    }

    while(fgets(ip,100,fp)!=NULL){
            sscanf(ip,"%c%d",&alpha,&num);
            if(alpha=='L'){
                while(num!=0){
                    if(i>=0){
                    i--;
                    num--;
                    }
                    if(i==-1){
                        i=99;
                    }
                    if(i==0){
                        count++;
                    }
                }
            }
            else if(alpha=='R'){
                while(num!=0){
                    if(i<=99){
                        i++;
                        num--;
                    }
                    if(i==100){
                        i=0;
                    }
                    if(i==0){
                        count++;
                    }
                }   
            }
    }
    printf("The number of zeroes is %d",count);
    fclose(fp);
}