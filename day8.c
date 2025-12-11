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
int sz[MAX_BOXES];


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


int compareSizes(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}


int find(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent[i]); 
}

void unite(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
        sz[root_j] += sz[root_i];
        sz[root_i] = 0; 
    }
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
        sz[i] = 1;
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

    int limit = 1000;
    if (edge_count < 1000) limit = edge_count; 

    for (int i = 0; i < limit; i++) {
        unite(edges[i].u, edges[i].v);
    }

    int final_sizes[MAX_BOXES];
    int circuit_count = 0;

    for (int i = 0; i < box_count; i++) {
        if (parent[i] == i) {
            final_sizes[circuit_count++] = sz[i];
        }
    }

    qsort(final_sizes, circuit_count, sizeof(int), compareSizes);

    long long result = (long long)final_sizes[0] * (long long)final_sizes[1] * (long long)final_sizes[2];

    printf("Top 3 circuit sizes: %d, %d, %d\n", final_sizes[0], final_sizes[1], final_sizes[2]);
    printf("Answer: %lld\n", result);

    return 0;
}