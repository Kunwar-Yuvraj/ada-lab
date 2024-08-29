#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int count = 0;

int euclid(int m, int n){
    count = 0;
    while (n != 0){
        count++;
        int tmp = m % n;
        m = n;
        n = tmp;
    }
    return m;
}

int consInt(int m, int n){
    count = 0;
    int min = (m < n)? m: n;
    
    for (int i = min; i > 0; i--){
        count++;
        if (m % i == 0 && n % i == 0) return i;
    }
    return (m > n)? m: n;
}

int modified(int m, int n){
    count = 0;
    if (n == 0 || m == 0) return (m > n)? m: n;

    while (++count && m != n){
        if (m > n) m -= n;
        else n -= m;
    }
    return n;
}

void tester(){
    int m, n;
    printf("Enter two numbers: ");
    scanf("%d %d", &m, &n);

    printf("GCD Using Euclid: %d\n", euclid(m, n));
    printf("GCD Using Consecutive Integer: %d\n", consInt(m, n));
    printf("GCD Using Modified: %d\n", modified(m, n));
}

void writeFiles(const char *bestFile, const char *worstFile, int (*gcdFunc)(int, int)){
    FILE *fb, *fw;
    fb = fopen(bestFile, "w");
    fw = fopen(worstFile, "w");

    if (!fb || !fw){
        printf("Error while opening file / File doesn't exist!\n");
        if (fb) fclose(fb);
        if (fw) fclose(fw);
        return;
    }

    for (int i = 10; i <= 100; i += 10){
        int max = INT_MIN;
        int min = INT_MAX;

        for (int j = 2; j <= i; j++){
            for (int k = 2; k <= i; k++){
                gcdFunc(j, k);
                if (count < min) min = count;
                if (count > max) max = count;
            }
        }
        fprintf(fb, "%d\t%d\n", i, min);
        fprintf(fw, "%d\t%d\n", i, max);
    }
    fclose(fb);
    fclose(fw);
}

void plotter(){
    writeFiles("Best-Euclid.txt", "Worst-Euclid.txt", euclid);
    writeFiles("Best-ConsInt.txt", "Worst-ConsInt.txt", consInt);
    writeFiles("Best-Modified.txt", "Worst-Modified.txt", modified);

    printf("Files generated successfully!\n");
}

int main(){
    int choice;
    printf("1.Tester\n2.Plotter\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) tester();
    else if (choice == 2) plotter();
    else printf("Invalid choice!\n");

    return 0;
}
