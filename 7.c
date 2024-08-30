#include <stdio.h>

int n, count = 0;
int isTester, cycle = 0;
int components = 0;

void dfs(int mat[n][n], int *vis, int source, int par){
    vis[source] = 1;

    if (isTester) printf("%d ", source);

    for (int i = 0; i < n; i++){
        count++;
        if (i != par && mat[source][i] && vis[i]) cycle = 1;
        else if (mat[source][i] && !vis[i]) dfs(mat, vis, i, source);
    }
}

void checkConn(int mat[n][n]){
    int vis[n], k = 1;
    for (int i = 0; i < n; i++) vis[i] = 0;

    for (int i = 0; i < n; i++){
        if (!vis[i]){
            components++;
            if (isTester) printf("Connected component %d: ", k++);
            dfs(mat, &vis[0], i, -1);
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
    printf("\nNumber of connected components: %d\n", components);
    if (cycle) printf("Graph is Cyclic!\n");
    else printf("Graph is Acyclic!\n");
}

void plotter(){
    printf("Generating files...\n");

    isTester = 0;
    FILE *f = fopen("dfs.txt", "w");

    for (int k = 1; k <= 10; k++){
        n = k;
        int mat[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = (i == j)? 0: 1;
        
        count = 0;
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
