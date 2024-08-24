#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count = 0;

void merge_sort(int array[], int length);
void merge(int left_array[], int right_array[], int array[], int left_size, int right_size);
void generate_worst_case(int arr[], int beg, int end);
void plotter();

int main() {
    int choice;
    printf("Enter 1 to sort manually, 2 to run plotter: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int n;
        printf("Enter number of elements: ");
        scanf("%d", &n);
        int array[n];
        printf("Enter elements: ");
        for (int i = 0; i < n; i++)
            scanf("%d", &array[i]);

        merge_sort(array, n);

        for (int i = 0; i < n; i++) 
            printf("%d ", array[i]);
        printf("\n");
    } else if (choice == 2) {
        plotter();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

void merge_sort(int array[], int length) {
    if (length <= 1) return;
    
    int middle = length / 2;
    
    int left_array[middle];
    int right_array[length - middle];

    int i = 0;
    int j = 0;

    for (; i < length; i++) {
        if (i < middle)
            left_array[i] = array[i];
        else
            right_array[j++] = array[i];
    }

    merge_sort(left_array, middle);
    merge_sort(right_array, length - middle);
    merge(left_array, right_array, array, middle, length - middle);
}

void merge(int left_array[], int right_array[], int array[], int left_size, int right_size) {
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_size && r < right_size) {
        count++; // Count the comparisons
        if (left_array[l] < right_array[r]) 
            array[i] = left_array[l++];
        else 
            array[i] = right_array[r++];
        i++;
    }

    while (l < left_size) 
        array[i++] = left_array[l++];
    
    while (r < right_size)
        array[i++] = right_array[r++];
}

void generate_worst_case(int arr[], int beg, int end) {
    if (beg < end) {
        int mid = (beg + end) / 2;
        int i, j, k;
        int n1 = mid - beg + 1;
        int n2 = end - mid;
        int left[n1], right[n2];
        for (i = 0; i < n1; i++) left[i] = arr[2 * i];
        for (j = 0; j < n2; j++) right[j] = arr[2 * j + 1];
        generate_worst_case(left, beg, mid);
        generate_worst_case(right, mid + 1, end);
        for (i = 0; i < n1; i++) arr[i] = left[i];
        for (j = 0; j < n2; j++) arr[n1 + j] = right[j];
    }
}

void plotter() {
    int *arr, n;
    srand(time(NULL));
    FILE *f1, *f2, *f3, *f4;
    f1 = fopen("Mergebest1.txt", "w");
    f2 = fopen("Mergeworst1.txt", "w");
    f3 = fopen("Mergeavg1.txt", "w");
    f4 = fopen("Worstdata1.txt", "w");

    for (n = 2; n <= 1024; n *= 2) {
        arr = (int *)malloc(sizeof(int) * n);
        
        // Best case: Array is already sorted
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        count = 0;
        merge_sort(arr, n);
        fprintf(f1, "%d\t%d\n", n, count);
        
        // Worst case: Generate the worst case
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;
        generate_worst_case(arr, 0, n - 1);
        count = 0;
        merge_sort(arr, n);
        fprintf(f2, "%d\t%d\n", n, count);

        // Save worst-case data
        for (int i = 0; i < n; i++)
            fprintf(f4, "%d ", arr[i]);
        fprintf(f4, "\n");

        // Average case: Array filled with random numbers
        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
        count = 0;
        merge_sort(arr, n);
        fprintf(f3, "%d\t%d\n", n, count);

        free(arr);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    printf("Data has been written to files.\n");
}
