#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_POINTS 2048 

typedef struct {
    long long x;
    long long y;
} Point;

long long min_ll(long long a, long long b) { return (a < b) ? a : b; }

long long max_ll(long long a, long long b) { return (a > b) ? a : b; }

int main() {
    FILE *fp = fopen("day9input.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open day9input.txt\n");
        return 1;
    }

    Point points[MAX_POINTS];
    int n = 0;
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        if (n >= MAX_POINTS) {
            printf("Error: Too many points. Increase MAX_POINTS.\n");
            break;
        }
        
        long long tx, ty;
        if (sscanf(line, "%lld,%lld", &tx, &ty) == 2) {
            points[n].x = tx;
            points[n].y = ty;
            n++;
        }
    }
    fclose(fp);

    printf("Loaded %d points.\n", n);

    long long max_area = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            
            Point p1 = points[i];
            Point p2 = points[j];

            long long min_x = min_ll(p1.x, p2.x);
            long long max_x = max_ll(p1.x, p2.x);
            long long min_y = min_ll(p1.y, p2.y);
            long long max_y = max_ll(p1.y, p2.y);
            long long width = max_x - min_x + 1;
            long long height = max_y - min_y + 1;
            long long current_area = width * height;

            if (current_area <= max_area) continue;
            double mid_x = (min_x + max_x) / 2.0;
            double mid_y = (min_y + max_y) / 2.0;
            
            bool inside = false;
            
            for (int k = 0; k < n; k++) {
                Point v1 = points[k];
                Point v2 = points[(k + 1) % n]; 

                if (v1.x == v2.x) {
                    double y_low = (double)min_ll(v1.y, v2.y);
                    double y_high = (double)max_ll(v1.y, v2.y);

                    if (y_low <= mid_y && mid_y < y_high) {
                        if ((double)v1.x > mid_x) {
                            inside = !inside;
                        }
                    }
                }
            }

            if (!inside) continue;
            bool intersects = false;
            
            for (int k = 0; k < n; k++) {
                Point v1 = points[k];
                Point v2 = points[(k + 1) % n];

                if (v1.x == v2.x) { 
                    if (v1.x > min_x && v1.x < max_x) {
                        long long edge_y_min = min_ll(v1.y, v2.y);
                        long long edge_y_max = max_ll(v1.y, v2.y);
                        
                        long long overlap_start = max_ll(edge_y_min, min_y);
                        long long overlap_end = min_ll(edge_y_max, max_y);
                        
                        if (overlap_start < overlap_end) {
                            intersects = true;
                            break;
                        }
                    }
                } else { 
                    if (v1.y > min_y && v1.y < max_y) {
                        long long edge_x_min = min_ll(v1.x, v2.x);
                        long long edge_x_max = max_ll(v1.x, v2.x);
                        
                        long long overlap_start = max_ll(edge_x_min, min_x);
                        long long overlap_end = min_ll(edge_x_max, max_x);
                        
                        if (overlap_start < overlap_end) {
                            intersects = true;
                            break;
                        }
                    }
                }
            }

            if (intersects) continue;
            max_area = current_area;
        }
    }

    printf("Largest Valid Area: %lld\n", max_area);

    return 0;
}