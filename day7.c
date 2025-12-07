#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_R 200
#define MAX_C 200

char grid[MAX_R][MAX_C];
int rows = 0, cols = 0;
long long memo[MAX_R][MAX_C];

long long solve(int r, int c) {
    if (r >= rows || c < 0 || c >= cols) {
        return 1;
    }

    if (memo[r][c] != -1) {
        return memo[r][c];
    }

    long long count = 0;
    char cell = grid[r][c];

    if (cell == '.' || cell == 'S') {
        count = solve(r + 1, c);
    }
    else if (cell == '^') {
        count = solve(r + 1, c - 1) + solve(r + 1, c + 1);
    }

    return memo[r][c] = count;
}

int main() {
    FILE *fp = fopen("day7input.txt", "r");
    if (!fp) return 1;

    while (fscanf(fp, "%s", grid[rows]) == 1) {
        rows++;
    }
    cols = strlen(grid[0]);
    fclose(fp);

    for(int i=0; i<MAX_R; i++) {
        for(int j=0; j<MAX_C; j++) {
            memo[i][j] = -1;
        }
    }

    int start_r = -1, start_c = -1;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 'S') {
                start_r = r;
                start_c = c;
            }
        }
    }

    long long total_timelines = solve(start_r, start_c);

    printf("Total timelines: %lld\n", total_timelines);
    return 0;
}