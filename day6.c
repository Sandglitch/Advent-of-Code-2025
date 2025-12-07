#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ROWS 200
#define MAX_COLS 20000

char grid[MAX_ROWS][MAX_COLS];
int rows = 0;
int cols = 0;

int is_col_empty(int c) {
    for (int r = 0; r < rows; r++) {
        if (grid[r][c] != ' ' && grid[r][c] != '\0' && grid[r][c] != '\n') {
            return 0;
        }
    }
    return 1;
}

int main() {
    FILE *fp = fopen("day6input.txt", "r");
    if (fp == NULL) return 1;
    for (int r = 0; r < MAX_ROWS; r++) {
        for (int c = 0; c < MAX_COLS; c++) {
            grid[r][c] = ' ';
        }
    }

    char lineBuffer[MAX_COLS];
    while (fgets(lineBuffer, MAX_COLS, fp)) {
        int len = strlen(lineBuffer);
        if (lineBuffer[len - 1] == '\n') lineBuffer[--len] = '\0';
        if (len > cols) cols = len;
        for (int c = 0; c < len; c++) {
            grid[rows][c] = lineBuffer[c];
        }
        rows++;
    }

    long long grand_total = 0;

    for (int c = 0; c < cols; c++) {
        if (is_col_empty(c)) continue;

        int start_col = c;
        int end_col = c;
        while (end_col < cols && !is_col_empty(end_col + 1)) {
            end_col++;
        }

        long long numbers[100];
        int num_count = 0;
        char operator = '?';

        for (int k = start_col; k <= end_col; k++) {
            for (int r = 0; r < rows; r++) {
                if (grid[r][k] == '+') operator = '+';
                else if (grid[r][k] == '*') operator = '*';
            }
        }

        for (int k = start_col; k <= end_col; k++) {
            long long current_val = 0;
            int has_digit = 0;

            for (int r = 0; r < rows; r++) {
                if (isdigit(grid[r][k])) {
                    current_val = (current_val * 10) + (grid[r][k] - '0');
                    has_digit = 1;
                }
            }

            if (has_digit) {
                numbers[num_count++] = current_val;
            }
        }

        if (num_count > 0) {
            long long problem_result = numbers[0];
            for (int i = 1; i < num_count; i++) {
                if (operator == '+') problem_result += numbers[i];
                else if (operator == '*') problem_result *= numbers[i];
            }
            grand_total += problem_result;
        }

        c = end_col;
    }

    printf("Grand Total: %lld\n", grand_total);
    fclose(fp);
    return 0;
}