#include <stdio.h>
#include <stdlib.h>

#define max 20

int n, count = 0;
int f, r;
int q[max], in[max];

int bfs(int mat[n][n]){
    f = r = -1;
    int xm = 0;

    for (int i = 0; i < n; i++)
        if(in[i] == 0)
            q[++r] = i;

    while (f != r){
        int cur = q[++f];
        xm++;

        for (int i = 0; i < n; i++){
            count++;

            if (mat[cur][i]){
                in[i]--;
                if (!in[i]) q[++r] = i;
            }
        }
    }
    return xm != n;
}

void tester(){
    printf("Enter number of vertices: "); scanf("%d", &n);

    for (int i = 0; i < n; i++) in[i] = 0;

    int mat[n][n];
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &mat[i][j]);
            if (mat[i][j]) in[j]++;
        }
    }
    if (bfs(mat)){
        printf("Cycle detected. Can't generated topological order!\n");
        exit(0);
    } else {
        printf("Topological order: ");
        for (int i = 0; i < n; i++) printf("%d ", q[i]);
    }
}

void plotter(){
    printf("Writing file...\n");
    FILE *f = fopen("top-bfs.txt", "w");
    for (int k = 1; k <= 10; k++){
        n = k;
        int mat[n][n];
        for (int i = 0; i < n; i++) in[i] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = 0;

        for (int i = 0; i < n - 1; i++){
            for (int j = i + 1; j < n; j++){
                mat[i][j] = 1;
                in[j]++;
            }
        }
        count = 0;
        bfs(mat);
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
