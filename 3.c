#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count = 0;

void bubbleSort(int *a, int n){
    count = 0;
    for (int i = 0; i < n - 1; i++){
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++){
            count++;
            if (a[j] > a[j + 1]){
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}

void selectionSort(int *a, int n){
    count = 0;
    for (int i = 0; i < n; i++){
        int minIndex = i;
        for (int j = i + 1; j < n; j++){
            count++;
            if (a[j] < a[minIndex]) minIndex = j;
        }

        if (minIndex != i){
            int tmp = a[minIndex];
            a[minIndex] = a[i];
            a[i] = tmp;
        }
    }
}

void insertionSort(int *a, int n){
    count = 0;
    for (int i = 1; i < n; i++){
        int j = i - 1;
        int val = a[i];
        while (++count && a[j] > val){
            a[j + 1] = a[j];
            j--;

            if (j < 0) break;
        }
        a[j + 1] = val;
    }
}

void tester(){
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int choice;
    printf("1. Selection Sort\n2. Bubble Sort\n3. Insertion Sort\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: selectionSort(a, n); break;
    case 2: bubbleSort(a, n); break;
    case 3: insertionSort(a, n); break;
    
    default: printf("Invalid choice!\n");
    }
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

void writeFiles(const char *bestFile, const char *worstFile, const char *avgFile, void (*sortFunc)(int *, int)){
    FILE *fw, *fb, *fa;
    fb = fopen(bestFile, "w");
    fw = fopen(worstFile, "w");
    fa = fopen(avgFile, "w");

    int n = 10;
    while (n <= 30000){
        int *a = (int *)malloc(n * sizeof(int));

        // best case
        for (int i = 0; i < n; i++) a[i] = i + 1;
        sortFunc(a, n);
        fprintf(fb, "%d\t%d\n", n, count);

        // worst case
        for (int i = 0; i < n; i++) a[i] = n - i;
        sortFunc(a, n);
        fprintf(fw, "%d\t%d\n", n, count);

        // avg case
        for (int i = 0; i < n; i++) a[i] = rand() % n;
        sortFunc(a, n);
        fprintf(fa, "%d\t%d\n", n, count);

        free(a);
        n = (n < 10000)? n * 10: n + 10000;
    }
    fclose(fb);
    fclose(fw);
    fclose(fa);
}

void plotter(){
    printf("Generating files...\n");
    writeFiles("best-bubble.txt", "worst-bubble.txt", "avg-bubble.txt", bubbleSort);
    writeFiles("best-selection.txt", "worst-selection.txt", "avg-selection.txt", selectionSort);
    writeFiles("best-insertion.txt", "worst-insertion.txt", "avg-insertion.txt", insertionSort);
    printf("Files generated successfully!\n");
}

int main(){
    int choice;
    printf("1. Tester\n2. Plotter\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) tester();
    else if (choice == 2) plotter();
    else printf("Invalid choice!\n");
    
    return 0;
}
