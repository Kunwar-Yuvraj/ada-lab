// dijkstra
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max 20

int n, count = 0;
int mat[max][max];
int parent[max], dist[max], in[max];

int minKey(){
    int min = INT_MAX, minIndex;

    for (int v = 0; v < n; v++){
        if (!in[v] && dist[v] < min){
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(int src){
    for (int i = 0; i < n; i++){
        count++;

        dist[i] = INT_MAX;
        in[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int i = 0; i < n - 1; i++){
        int u = minKey();
        in[u] = 1;

        for (int v = 0; v < n; v++){
            count++;
            int tmp = dist[u] + mat[u][v];

            if (mat[u][v] && dist[u] != INT_MAX && !in[v] && tmp < dist[v]){
                dist[v] = tmp;
                parent[v] = u;
            }
        }
    }
}

void tester(){
    printf("Enter number of vertices: "); scanf("%d", &n);
    
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    dijkstra(0);

    printf("Vertices \t Distance from (0)\n");
    for (int i = 0; i < n; i++) printf("%d \t %d\n", i, dist[i]);
}

void plotter(){
    printf("Writing file...\n");
    FILE *f = fopen("dijkstra.txt", "w");
    for (int k = 1; k <= 10; k++){
        n = k;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = (i == j)? 0: rand();
        
        count = 0;
        dijkstra(0);
        fprintf(f, "%d\t%d\n", n , count);
    }
    fclose(f);
    printf("File written successfully!\n");
}

int main(){
    printf("1. Tester\n2. Plotter\n");
    printf("Enter your choice: ");
    int choice; scanf("%d", &choice);

    if (choice == 1) tester();
    else if (choice == 2) plotter();
    else printf("Invalid choice!\n");
    
    return 0;
}
