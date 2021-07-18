#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * The maximum the array can take if the numbers in the file
 * are separated by spaces is (FILE_SIZE / 2) integers.
 */

int find_max_values(FILE *fptr) {
    fseek(fptr, 0L, SEEK_END);
    int length = ftell(fptr) / 2;
    rewind(fptr);
    return length;
}

long merge(int *num_array, int start, int middle, int end) {
    long inversions = 0;
    int left_size = middle - start + 1;
    int right_size = end - middle;

    int *left_array = malloc(sizeof(int) * left_size);
    int *right_array = malloc(sizeof(int) * right_size);

    for (int i = 0; i < left_size; i++) {
        left_array[i] = num_array[start + i];
    }

    for (int j = 0; j < right_size; j++) {
        right_array[j] = num_array[middle + 1 + j];
    }

    int left_idx = 0;
    int right_idx = 0;
    int merge_idx = start;
    

    while (left_idx < left_size && right_idx < right_size) {
        if (left_array[left_idx] < right_array[right_idx]) {
            num_array[merge_idx] = left_array[left_idx];
            left_idx++;
        } else {
            num_array[merge_idx] = right_array[right_idx];
            right_idx++;
            inversions = inversions + (left_size - left_idx);
        }
        merge_idx++;
    }

    while (left_idx < left_size) {
        num_array[merge_idx] = left_array[left_idx];
        left_idx++;
        merge_idx++;
    }

    while (right_idx < right_size) {
        num_array[merge_idx] = right_array[right_idx];
        right_idx++;
        merge_idx++;
    }
    return inversions;
}

long merge_sort(int *num_array, int start, int end) {
    long inversions = 0;
    if (start < end) {
        int middle;
        
        middle = (start + end) / 2;
        inversions += merge_sort(num_array, start, middle);
        inversions += merge_sort(num_array, (middle + 1), end);
        inversions += merge(num_array, start, middle, end);
    }
    return inversions;
}

int main(int argc, char **argv) {
    double time_spent = 0.0;

    clock_t begin = clock();

    FILE *fptr = fopen(argv[1], "r");
    int length = find_max_values(fptr);

    int *num_array = malloc(sizeof(int) * length);

    int elements = 0;
    int num;
    long inversions = 0;

    while (fscanf(fptr, "%d", &num) == 1) {
        num_array[elements] = num;
        elements++;
    }

    inversions = merge_sort(num_array, 0, elements);

    printf("Number of inversions: %ld\n", inversions);

    fclose(fptr);
    free(num_array);

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f\n", time_spent);
    
    return 0;
}