#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x;
    long long y;
} Point;

#define MAX_POINTS 2000

int main() {
    FILE *fp = fopen("day9input.txt", "r");
    if (!fp) return 1;

    Point tiles[MAX_POINTS];
    int count = 0;

    while (fscanf(fp, "%lld,%lld", &tiles[count].x, &tiles[count].y) == 2) {
        count++;
        if (count >= MAX_POINTS) break;
    }
    fclose(fp);

    long long max_area = 0;

    for (int i = 0; i < count; i++) {
        for (int j = i; j < count; j++) {
            long long width = llabs(tiles[i].x - tiles[j].x) + 1;
            long long height = llabs(tiles[i].y - tiles[j].y) + 1;

            long long area = width * height;

            if (area > max_area) {
                max_area = area;
            }
        }
    }

    printf("Largest area: %lld\n", max_area);
    return 0;
}