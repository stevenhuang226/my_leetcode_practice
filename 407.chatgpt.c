
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int h, i, j;
} Cell;

int cmp(const void *a, const void *b) {
    return ((Cell*)a)->h - ((Cell*)b)->h;
}

#define HEAP_SIZE 40005
Cell heap[HEAP_SIZE];
int heapSize;

void push(Cell c) {
    heap[heapSize++] = c;
    int cur = heapSize - 1;
    while (cur > 0) {
        int par = (cur - 1) / 2;
        if (heap[par].h <= heap[cur].h) break;
        Cell tmp = heap[par]; heap[par] = heap[cur]; heap[cur] = tmp;
        cur = par;
    }
}

Cell pop() {
    Cell ret = heap[0];
    heap[0] = heap[--heapSize];
    int cur = 0;
    while (1) {
        int l = cur * 2 + 1, r = cur * 2 + 2, small = cur;
        if (l < heapSize && heap[l].h < heap[small].h) small = l;
        if (r < heapSize && heap[r].h < heap[small].h) small = r;
        if (small == cur) break;
        Cell tmp = heap[cur]; heap[cur] = heap[small]; heap[small] = tmp;
        cur = small;
    }
    return ret;
}

int trapRainWater(int** heightMap, int m, int* heightMapColSize){
    if (m == 0 || *heightMapColSize == 0) return 0;
    int n = *heightMapColSize;
    bool visited[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            visited[i][j] = false;
    heapSize = 0;

    // push all boundary
    for (int i = 0; i < m; i++) {
        push((Cell){heightMap[i][0], i, 0});
        push((Cell){heightMap[i][n-1], i, n-1});
        visited[i][0] = visited[i][n-1] = true;
    }
    for (int j = 0; j < n; j++) {
        push((Cell){heightMap[0][j], 0, j});
        push((Cell){heightMap[m-1][j], m-1, j});
        visited[0][j] = visited[m-1][j] = true;
    }

    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    int water = 0;
    while (heapSize > 0) {
        Cell cur = pop();
        for (int d = 0; d < 4; d++) {
            int ni = cur.i + dirs[d][0], nj = cur.j + dirs[d][1];
            if (ni < 0 || nj < 0 || ni >= m || nj >= n || visited[ni][nj]) continue;
            visited[ni][nj] = true;
            if (heightMap[ni][nj] < cur.h) {
                water += cur.h - heightMap[ni][nj];
                push((Cell){cur.h, ni, nj});
            } else {
                push((Cell){heightMap[ni][nj], ni, nj});
            }
        }
    }
    return water;
}

