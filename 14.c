#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max 20

int n, count = 0;
int mat[max][max];
int parent[max], key[max], inMST[max];

int minKey(){
    int min = INT_MAX, minIndex;
    for (int v = 0; v < n; v++){
        if (!inMST[v] && key[v] < min){
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void prims(){
    for (int i = 0; i < n; i++){
        count++;
        key[i] = INT_MAX;
        inMST[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++){
        int u = minKey();
        inMST[u] = 1;
        for (int v = 0; v < n; v++){
            count ++;
            if (mat[u][v] && !inMST[v] && mat[u][v] < key[v]){
                key[v] = mat[u][v];
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

    prims();
    printf("Edges \t Weights\n");
    for (int i = 1; i < n; i++)
        printf("%d<->%d \t %d\n", parent[i], i, key[i]);

    int minWT = 0;
    for (int i = 0; i < n; i++) minWT += key[i];
    printf("Minimum Weight: %d\n", minWT);
}

void plotter(){
    printf("Writing file...\n");
    FILE *f = fopen("prims.txt", "w");
    for (int k = 1; k <= 10; k++){
        n = k;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = (i == j)? 0: rand();
        
        count = 0;
        prims();
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
