#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int n, count = 0;
int isTester;
int cycle = 0;
int components = 0;

void bfs(int mat[n][n], int *vis, int source){
    count = 0;
    int q[n], parent[n];
    int f = -1, r = -1;

    vis[source] = 1;
    q[++r] = source;
    parent[r] = -1;

    while (f != r){
        int cur = q[++f];
        int par = parent[f];

        if (isTester) printf("%d ", cur);

        for (int i = 0; i < n; i++){
            count ++;

            if (i != par && mat[cur][i] && vis[i]) cycle = 1;
            if (mat[cur][i] && !vis[i]){
                vis[i] = 1;
                q[++r] = i;
                parent[r] = cur;
            }
        }
    }
}

void checkConn(int mat[n][n]){
    int vis[n], k = 1;
    for (int i = 0; i < n; i++) vis[i] = 0;

    for (int i = 0; i < n; i++){
        if (vis[i] == 0){
            components++;
            if (isTester) printf("Connected component %d: ", k++);
            bfs(mat, &vis[0], i);
        }
    }
}

void tester(){
    isTester = 1;
    printf("Enter number of vertices: "); scanf("%d", &n);

    int mat[n][n];
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    checkConn(mat);
    printf("\nNumber of connected components in graph: %d\n", components);

    if (cycle == 1) printf("Graph is Cyclic!\n");
    else printf("Graph is Acyclic!\n");
}

void plotter(){
    isTester = 0;

    printf("Generating files...\n");

    FILE *f = fopen("bfs.txt", "w");
    
    for (int k = 1; k <= 10; k++){
        n = k;
        int mat[n][n];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mat[i][j] = (i == j)? 0: 1;
            }
        }
        checkConn(mat);
        fprintf(f, "%d\t%d\n", n, count);
    }
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
