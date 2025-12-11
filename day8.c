#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BOXES 2000
#define MAX_EDGES 2000000

typedef struct {
    int id;
    long long x, y, z;
} Point;

typedef struct {
    int u, v;
    double dist;
} Edge;

Point boxes[MAX_BOXES];
Edge edges[MAX_EDGES];
int parent[MAX_BOXES];

double get_dist(Point a, Point b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    long long dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    if (e1->dist < e2->dist) return -1;
    if (e1->dist > e2->dist) return 1;
    return 0;
}

int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]);
}

int unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
        return 1;
    }
    return 0;
}

int main() {
    FILE *fp = fopen("day8input.txt", "r");
    if (!fp) return 1;

    int box_count = 0;
    while (fscanf(fp, "%lld,%lld,%lld", &boxes[box_count].x, &boxes[box_count].y, &boxes[box_count].z) == 3) {
        boxes[box_count].id = box_count;
        box_count++;
    }
    fclose(fp);

    for (int i = 0; i < box_count; i++) {
        parent[i] = i;
    }

    int edge_count = 0;
    for (int i = 0; i < box_count; i++) {
        for (int j = i + 1; j < box_count; j++) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].dist = get_dist(boxes[i], boxes[j]);
            edge_count++;
        }
    }

    qsort(edges, edge_count, sizeof(Edge), compareEdges);

    int successful_merges = 0;
    long long answer = 0;

    for (int i = 0; i < edge_count; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (unite(u, v)) {
            successful_merges++;

            if (successful_merges == box_count - 1) {
                answer = boxes[u].x * boxes[v].x;
                printf("Last connection between Box %d (X=%lld) and Box %d (X=%lld)\n", 
                       u, boxes[u].x, v, boxes[v].x);
                break;
            }
        }
    }

    printf("Product of X coordinates: %lld\n", answer);

    return 0;
}