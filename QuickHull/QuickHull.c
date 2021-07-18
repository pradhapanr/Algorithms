#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "list.h"

Point *merge_sorted_list(Point *list1, Point *list2) {
    Point *result = NULL;

    if (list1 == NULL) {
        return list2;
    } else if (list2 == NULL) {
        return list1;
    }

    if (list1->x < list2->x) {
        result = list1;
        result->next = merge_sorted_list(list1->next, list2);
    } else if (list1->x > list2->x) {
        result = list2;
        result->next = merge_sorted_list(list1, list2->next);
    } else { //points are equal
        if (list1->y <= list2->y) {
            result = list1;
            result->next = merge_sorted_list(list1->next, list2);
        } else {
            result = list2;
            result->next = merge_sorted_list(list1, list2->next);
        }
    }
    return result;
}

void split_list(Point *source, Point **front, Point **back) {
    Point *ptr1;
    Point *ptr2;
    ptr2 = source;
    ptr1 = source->next;

    while (ptr1 != NULL) {
        ptr1 = ptr1->next;
        if (ptr1 != NULL) {
            ptr2 = ptr2->next;
            ptr1 = ptr1->next;
        }
    }

    *front = source;
    *back = ptr2->next;
    ptr2->next = NULL;
}

void merge_sort(Point **head) {
    Point *temp_head = *head;
    Point *ptr1;
    Point *ptr2;

    if ((temp_head == NULL) || (temp_head->next == NULL)) {
        return;
    }

    split_list(temp_head, &ptr1, &ptr2);

    merge_sort(&ptr1);
    merge_sort(&ptr2);

    *head = merge_sorted_list(ptr1, ptr2);
}

double calc_a(double y1, double y2) {
    return y2 - y1;
}

double calc_b(double x1, double x2) {
    return x1 - x2;
}

double calc_c(double x1, double x2, double y1, double y2) {
    return (x1 * y2) - (y1 * x2);
}

int is_larger(double a, double b, double c, double x, double y) {
    double val = (a * x) + (b * y);
    if (val > c) {
        return 1;
    }
    return 0;
}

double calc_determinant(double x1, double x2, double x3, double y1, double y2, double y3) {
    double determinant = (x1 * y2) + (x3 * y1) + (x2 * y3) - (x3 * y2) - (x2 * y1) - (x1 * y3);
    return fabs(determinant);
}

void find_hull(List *final_hull, List *hull, int elements, Point *left_point, Point *right_point);

void quick_hull(List *hull, List *list, int elements) {
    Point *left_point = find_index(list->head , 0);
    Point *right_point = find_index(list->head, elements - 1);

    double a = calc_a(left_point->y, right_point->y);
    double b = calc_b(left_point->x, right_point->x);
    double c = calc_c(left_point->x, left_point->y, right_point->x, right_point->y);

    List *top_hull = malloc(sizeof(List));
    List *bottom_hull = malloc(sizeof(List));

    top_hull->head = NULL;
    bottom_hull->head = NULL;

    Point *compare = list->head;

    for (int i = 1; i < elements - 1; i++) {
        //Point *compare = find_index(list->head, i);
        //if (!(arr[i]->x == comparisonPoint->x && arr[i]->y == comparisonPoint->y)) {}
        compare = compare->next;
        if (is_larger(a, b, c, compare->x, compare->y) == 1) {
            top_hull->head = prepend_point(top_hull->head, compare->x, compare->y);
        } else {
            bottom_hull->head = prepend_point(bottom_hull->head, compare->x, compare->y);
        }
    }

    hull->head = prepend_point(hull->head, left_point->x, left_point->y);
    hull->head = prepend_point(hull->head, right_point->x, right_point->y);

    int top_elements = num_elements(top_hull);
    int bottom_elements = num_elements(bottom_hull);

    find_hull(hull, top_hull, top_elements, left_point, right_point);
    find_hull(hull, bottom_hull, bottom_elements, right_point, left_point);
    
}

void find_hull(List *final_hull, List *hull, int elements, Point *left_point, Point *right_point) {
    if (is_empty(hull) == 1) {
        return;
    }

    double determinant = -1;
    Point *furthest = malloc(sizeof(Point));

    Point *compare = hull->head;

    for (int i = 0; i < elements; i++) {
        double num = calc_determinant(left_point->x, right_point->x, compare->x, left_point->y, right_point->y, compare->y);
        if (num > determinant) {
            determinant = num;
            furthest = find_index(hull->head, i);
        }
        compare = compare->next;
    }
    final_hull->head = prepend_point(final_hull->head, furthest->x, furthest->y);

    List *top_hull = malloc(sizeof(List));
    List *bottom_hull = malloc(sizeof(List));

    top_hull->head = NULL;
    bottom_hull->head = NULL;

    compare = hull->head;

    for (int i = 0; i < elements; i++) {
        if (!(compare->x == furthest->x && compare->y == furthest->y)) { // CHANGE THIS AFTER TO REMOVE NODE FROM HULL INSTEAD
            double a = calc_a(left_point->y, furthest->y);
            double b = calc_b(left_point->x, furthest->x);
            double c = calc_c(left_point->x, left_point->y, furthest->x, furthest->y);

            if (is_larger(a, b, c, compare->x, compare->y) == 1) {
                top_hull->head = prepend_point(top_hull->head, compare->x, compare->y);
            }

            a = calc_a(furthest->y, right_point->y);
            b = calc_b(furthest->x, right_point->x);
            c = calc_c(furthest->x, furthest->y, right_point->x, right_point->y);
        
            if (is_larger(a, b, c, compare->x, compare->y) == 1) {
                bottom_hull->head = prepend_point(bottom_hull->head, compare->x, compare->y);
            }
        }
        compare = compare->next;
    }
    int top_elements = num_elements(top_hull);
    int bottom_elements = num_elements(bottom_hull);

    find_hull(final_hull, top_hull, top_elements, left_point, furthest);
    find_hull(final_hull, bottom_hull, bottom_elements, furthest, right_point);

}

int main (int argc, char **argv) {
    double time_spent = 0.0;

    clock_t begin = clock();

    FILE *fptr = fopen(argv[1], "r");

    List *list = malloc(sizeof(List));

    int elements = 0;
    double num1;
    double num2;

    while (fscanf(fptr, "%lf", &num1) == 1 && fscanf(fptr, "%lf", &num2) == 1) {
        list->head = prepend_point(list->head, num1, num2);
        elements++;
    }

    merge_sort(&list->head);

    List *hull = malloc(sizeof(List));

    quick_hull(hull, list, elements);
    merge_sort(&hull->head);
    for (Point *temp = hull->head; temp != NULL; temp = temp->next) {
        printf("x: %.1lf y: %.1lf\n", temp->x, temp->y);
    }
    printf("%d\n", num_elements(hull));

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f\n", time_spent);
}