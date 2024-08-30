#include <stdio.h>
#include <stdlib.h>

int n, count = 0, top = -1;

int dfs(int mat[n][n], int *vis, int *track, int src, int *stack){
    vis[src] = 1;
    track[src] = 1;

    for (int i = 0; i < n; i++){
        count++;
        if (mat[src][i] && vis[i] && track[i]) return 1;
        if (mat[src][i] && !vis[i] && dfs(mat, vis, track, i, stack)) return 1;
    }
    stack[++top] = src;
    track[src] = 0;
    return 0;
}

int *conn(int mat[n][n]){
    int vis[n], track[n];
    for (int i = 0; i < n; i++) vis[i] = 0;

    int *stack = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        if (!vis[i] && dfs(mat, &vis[0], &track[0], i, stack))
            return NULL;
    }
    return stack;
}

void tester(){
    printf("Enter number of vertices: "); scanf("%d", &n);
    int mat[n][n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    
    int *stack = conn(mat);
    if (stack == NULL){
        printf("Cycle exists. Can't get topological order!\n");
        exit(0);
    }
    printf("Topological order: ");
    while (top != -1) printf("%d ", stack[top--]);
}

void plotter(){
    printf("Writing file...\n");
    FILE *f = fopen("top-dfs.txt", "w");
    for (int k = 1; k <= 10; k++){
        n = k;
        int mat[n][n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = 0;
        
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                mat[i][j] = 1;

        count = 0, top = -1;
        conn(mat);
        fprintf(f, "%d\t%d\n", n, count);
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
