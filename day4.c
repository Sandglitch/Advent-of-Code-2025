#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){
    FILE *fp=fopen("day4input.txt","r");
    if(fp==NULL){
        printf("File was not loaded");
        exit(0);
    }
    char input[200][200];
    char temp[200][200];
    int row = 0;
    long long total_removed = 0;
    int removed_this_round;
    int i, j, r, dr, dc, ni, nj, neighbors;

    while (fscanf(fp, "%s", input[row]) == 1) {
        row++;
    }
    int col = strlen(input[0]);

    do {
        removed_this_round = 0;

        for (r = 0; r < row; r++) {
            strcpy(temp[r], input[r]);
        }

        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (temp[i][j] == '@') {
                    neighbors = 0;
                    for (dr = -1; dr <= 1; dr++) {
                        for (dc = -1; dc <= 1; dc++) {
                            if (dr == 0 && dc == 0) continue;

                            ni = i + dr;
                            nj = j + dc;

                            if (ni >= 0 && ni < row && nj >= 0 && nj < col) {
                                if (temp[ni][nj] == '@') {
                                    neighbors++;
                                }
                            }
                        }
                    }

                    if (neighbors < 4) {
                        input[i][j] = '.';
                        removed_this_round++;
                        total_removed++;
                    }
                }
            }
        }
    } while (removed_this_round > 0);

    printf("%lld", total_removed);
    fclose(fp);
}