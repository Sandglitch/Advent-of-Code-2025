#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Range {
    long long min;
    long long max;
};

void main() {
    FILE *fp = fopen("day5input.txt", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    struct Range ranges[200];
    int range_count = 0;
    long long fresh_count = 0;
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        if (strchr(line, '-') != NULL) {
            sscanf(line, "%lld-%lld", &ranges[range_count].min, &ranges[range_count].max);
            range_count++;
        }
        else if (strlen(line) > 1) {
            long long id;
            if (sscanf(line, "%lld", &id) == 1) {
                
                int is_fresh = 0;
                for (int i = 0; i < range_count; i++) {
                    if (id >= ranges[i].min && id <= ranges[i].max) {
                        is_fresh = 1;
                        break;
                    }
                }

                if (is_fresh == 1) {
                    fresh_count++;
                }
            }
        }
    }
    printf("Total fresh ingredients: %lld\n", fresh_count);

    fclose(fp);
}