#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_POINTS 2048  // Adjust if input has more lines

typedef struct {
    long long x;
    long long y;
} Point;

// Helper to get minimum of two long longs
long long min_ll(long long a, long long b) { return (a < b) ? a : b; }

// Helper to get maximum of two long longs
long long max_ll(long long a, long long b) { return (a > b) ? a : b; }

int main() {
    FILE *fp = fopen("day9input.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open day9input.txt\n");
        return 1;
    }

    Point points[MAX_POINTS];
    int n = 0;
    
    // Read input file
    // Assumes format: "X,Y" per line
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        if (n >= MAX_POINTS) {
            printf("Error: Too many points. Increase MAX_POINTS.\n");
            break;
        }
        
        long long tx, ty;
        // Parse "x,y"
        if (sscanf(line, "%lld,%lld", &tx, &ty) == 2) {
            points[n].x = tx;
            points[n].y = ty;
            n++;
        }
    }
    fclose(fp);

    printf("Loaded %d points.\n", n);

    long long max_area = 0;

    // Iterate through every pair of vertices to form a candidate rectangle
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            
            Point p1 = points[i];
            Point p2 = points[j];

            long long min_x = min_ll(p1.x, p2.x);
            long long max_x = max_ll(p1.x, p2.x);
            long long min_y = min_ll(p1.y, p2.y);
            long long max_y = max_ll(p1.y, p2.y);

            // Calculate potential area (Discrete: width+1 * height+1)
            long long width = max_x - min_x + 1;
            long long height = max_y - min_y + 1;
            long long current_area = width * height;

            // Optimization: Skip if smaller than current best
            if (current_area <= max_area) continue;

            // --- VALIDITY CHECKS ---

            // 1. Point in Polygon Check (Ray Casting)
            // We test the center point of the rectangle
            double mid_x = (min_x + max_x) / 2.0;
            double mid_y = (min_y + max_y) / 2.0;
            
            bool inside = false;
            
            for (int k = 0; k < n; k++) {
                Point v1 = points[k];
                Point v2 = points[(k + 1) % n]; // Wrap around edge

                // We only care about vertical edges for a horizontal ray cast
                // Check if edge is vertical
                if (v1.x == v2.x) {
                    double y_low = (double)min_ll(v1.y, v2.y);
                    double y_high = (double)max_ll(v1.y, v2.y);

                    // Does our ray's Y fall within the edge's Y range?
                    if (y_low <= mid_y && mid_y < y_high) {
                        // Is the edge to the right of our point?
                        if ((double)v1.x > mid_x) {
                            inside = !inside;
                        }
                    }
                }
            }

            if (!inside) continue;

            // 2. Edge Intersection Check
            // Ensure no polygon edge slices strictly THROUGH the rectangle.
            bool intersects = false;
            
            for (int k = 0; k < n; k++) {
                Point v1 = points[k];
                Point v2 = points[(k + 1) % n];

                if (v1.x == v2.x) { 
                    // Polygon Edge is Vertical
                    // Check if edge X is strictly inside rectangle X range
                    if (v1.x > min_x && v1.x < max_x) {
                        // Check for Y overlap
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
                    // Polygon Edge is Horizontal
                    // Check if edge Y is strictly inside rectangle Y range
                    if (v1.y > min_y && v1.y < max_y) {
                        // Check for X overlap
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

            // If we pass both checks, update max_area
            max_area = current_area;
        }
    }

    printf("Largest Valid Area: %lld\n", max_area);

    return 0;
}