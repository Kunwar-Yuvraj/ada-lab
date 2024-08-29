#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int dist[100][100];
int n;
int count;

void floyds(int adj[n][n], int n){
    count = 0;

    // init dist
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adj[i][j] == -1) dist[i][j] = INT_MAX;
            else dist[i][j] = adj[i][j];

    // floyd-warshalls algo
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            int tmp = dist[i][k];
            for (int j = 0; j < n; j++){
                if (dist[i][j] > tmp){
                    count++;
                    if (dist[k][j] != INT_MAX && dist[i][j] > tmp + dist[k][j]){
                        dist[i][j] = tmp + dist[k][j];
                    }
                }
            }
        }
    }
}

void tester(){
    printf("Enter numbe of nodes: ");
    scanf("%d", &n);
    
    printf("Enter adjacency matrix:\n");
    int adj[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    floyds(adj, n);
    printf("Shortest path between every pair:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (dist[i][j] == INT_MAX) printf("INF ");
            else printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

void writeFiles(const char *bestFile, const char *worstFile, void (*shortestPath)(int a[n][n], int)){
    FILE *fb, *fw;
    fb = fopen(bestFile, "w");
    fw = fopen(worstFile, "w");

    srand(time(NULL));

    for (int k = 2; k < 12; k++){
        n = k;
        int adj[n][n];
        // best case: fully connected with minimal weight
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = (i == j)? 0: 1;
        shortestPath(adj, n);
        fprintf(fb, "%d\t%d\n", n, count);
        
        // worst case: connected graph with random weights
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = (i == j)? 0: rand() + 100 + 1;
        shortestPath(adj, n);
        fprintf(fw, "%d\t%d\n", n, count);
    }
    fclose(fb);
    fclose(fw);
}

void plotter(){
    printf("Generating files...!\n");
    writeFiles("best-floyds.txt", "worst-floyds.txt", floyds);
    printf("Files generated successfully!\n");
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
