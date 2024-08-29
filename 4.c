#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int count = 0;

bool BFSM(char *text, char *pat, int n, int m){
    count = 0;

    if (m > n) return false;

    for (int i = 0; i <= n - m; i++){
        int j = 0;
        while (j < m){
            count++;
            if (pat[j] != text[i + j]) break;
            j++;
        }
        if (j == m) return true;
    }
    return false;
}

void tester(){
    printf("Enter text length and pattern length: ");
    int n, m; scanf("%d %d", &n, &m);

    char text[100], pat[100];

    printf("Enter text: ");
    getchar();
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter pattern: ");
    getchar();
    fgets(pat, sizeof(pat), stdin);
    pat[strcspn(pat, "\n")] = '\0';

    if (BFSM(text, pat, n, m)) printf("Pattern matched!\n");
    else printf("Pattern didn't match!\n");
}

void writeFiles(const char *bestFile, const char *worstFile, bool (*matchAlgo)(char *, char *, int, int)){
    FILE *fb, *fw;
    fb = fopen(bestFile, "w");
    fw = fopen(worstFile, "w");

    int n = 1000;
    int m = 10;

    char *text = (char *)malloc(n * sizeof(char));
    for (int i = 0; i < n; i++) text[i] = 'a';

    while (m <= 1000){
        char *pat = (char *)malloc(m * sizeof(char));

        // best case
        for (int i = 0; i < m; i++) pat[i] = 'a';
        matchAlgo(text, pat, n, m);
        fprintf(fb, "%d\t%d\n", m, count);

        // worst case
        pat[m - 1] = 'b';
        matchAlgo(text, pat, n, m);
        fprintf(fw, "%d\t%d\n", m, count);

        free(pat);
        m = (m < 100)? m * 10: m + 100;
    }
}

void plotter(){
    printf("Generating Files...\n");
    writeFiles("best-BFSM.txt", "worst-BFSM.txt", BFSM);
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
