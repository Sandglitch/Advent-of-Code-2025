#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    FILE *fp=fopen("day4input.txt","r");
    if(fp==NULL){
        printf("File was not loaded");
        exit(0);
    }
    int rollnum=0,i,j,valroll=0;
    char input[200][200];
    int row=0;
    while(fscanf(fp,"%s",input[row])==1){
        row++;
    }
    int col=strlen(input[0]);
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            if(input[i][j]=='@'){
                rollnum=0;
                if((i==0 && j==0)||(i==0 && j==col-1)||(i==(row-1) && j==(col-1))||(i==(row-1) && j==0)){
                   rollnum++;
                }
                else if(i==0){
                    if(input[i][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i][j+1]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j+1]=='@'){
                        rollnum++;
                    }
                }
                else if(j==(col-1)){
                    if(input[i-1][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i-1][j]=='@'){
                        rollnum++;
                    }
                    if(input[i][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j]=='@'){
                        rollnum++;
                    }
                }
                else if(i==(row-1)){
                    if(input[i-1][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i-1][j]=='@'){
                        rollnum++;
                    }
                    if(input[i-1][j+1]=='@'){
                        rollnum++;
                    }
                    if(input[i][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i][j+1]=='@'){
                        rollnum++;
                    }
                }
                else if(j==0){
                    if(input[i-1][j]=='@'){
                        rollnum++;
                    }
                    if(input[i-1][j+1]=='@'){
                        rollnum++;
                    }
                    if(input[i][j+1]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j+1]=='@'){
                        rollnum++;
                    }
                }
                else{
                    if(input[i-1][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i-1][j]=='@'){
                        rollnum++;
                    }
                    if(input[i-1][j+1]=='@'){
                        rollnum++;
                    }
                    if(input[i][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i][j+1]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j-1]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j]=='@'){
                        rollnum++;
                    }
                    if(input[i+1][j+1]=='@'){
                        rollnum++;
                    }
                
                }
                if(rollnum<4){
                    valroll++;
                }
            }
        }
    }
    printf("%d",valroll);
    fclose(fp);
}