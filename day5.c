#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Range {
    long long min;
    long long max;
};

int main() {
    FILE *fp = fopen("day5input.txt", "r");
    if (fp == NULL) return 1;

    struct Range ranges[5000];
    int count = 0;
    char line[100];

    while (fgets(line, sizeof(line), fp)) {
        if (strchr(line, '-') != NULL) {
            sscanf(line, "%lld-%lld", &ranges[count].min, &ranges[count].max);
            count++;
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (ranges[j].min > ranges[j + 1].min) {
                struct Range temp = ranges[j];
                ranges[j] = ranges[j + 1];
                ranges[j + 1] = temp;
            }
        }
    }
    long long total_fresh = 0;
    long long last_counted_id = -1;

    for (int i = 0; i < count; i++) {
        long long start = ranges[i].min;
        long long end = ranges[i].max;
        if (start <= last_counted_id) {
            start = last_counted_id + 1;
        }
        if (end >= start) {
            long long new_ids = (end - start) + 1;
            total_fresh += new_ids;
            
            last_counted_id = end;
        }
    }

    printf("Total unique fresh ingredients: %lld\n", total_fresh);
    
    fclose(fp);
    return 0;
}