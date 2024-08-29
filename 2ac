#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count = 0;

int binarySearch(int *a, int n, int key){
    count = 0;

    int s = 0;
    int e = n - 1;
    int mid = s + (e - s) / 2;

    while (++count && s <= e){
        if (a[mid] == key) return mid;
        else if (a[mid] < key) s = mid + 1;
        else e = mid - 1;

        mid = s + (e - s) / 2; 
    }
    return -1;
}

int linearSearch(int *a, int n, int key){
    count = 0;

    for (int i = 0; i < n; i++){
        count++;
        if (a[i] == key) return i;
    }
    return -1;
}

void tester(){
    printf("Enter number of elements: ");
    int n; scanf("%d", &n);

    int a[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    
    printf("Enter key to search: ");
    int key; scanf("%d", &key);

    printf("Index by Binary search: %d\n", binarySearch(a, n, key));
    printf("Index by Linear search: %d\n", linearSearch(a, n, key));
}

void writeFiles(const char *bestFile, const char *worstFile, const char *avgFile,int (*searchFunc)(int *, int , int)){
    FILE *fb, *fw, *fa;
    fb = fopen(bestFile, "w");
    fw = fopen(worstFile, "w");
    fa = fopen(avgFile, "w");

    int n = 2;

    while (n <= 1024){
        int *a = (int *)malloc(n * sizeof(int));

        // best case
        for (int i = 0; i < n; i++) a[i] = 1;
        searchFunc(a, n, 1);
        fprintf(fb, "%d\t%d\n", n, count);

        // worst case
        for (int i = 0; i < n; i++) a[i] = 0;
        searchFunc(a, n, 1);
        fprintf(fw, "%d\t%d\n", n, count);

        // avg case
        for (int i = 0; i < n; i++) a[i] = rand() % n;
        searchFunc(a, n, rand() % n);
        fprintf(fa, "%d\t%d\n", n, count);

        free(a);        
        n *= 2;
    }
    fclose(fb);
    fclose(fa);
    fclose(fw);
}

void plotter(){
    printf("Generating files...\n");
    writeFiles("best-linear.txt", "worst-linear.txt", "avg-linear.txt", linearSearch);
    writeFiles("best-binary.txt", "worst-binary.txt", "avg-binary.txt", binarySearch);
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
