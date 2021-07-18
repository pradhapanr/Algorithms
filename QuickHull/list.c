#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Point *new_point(Point *next, double x, double y) {
    Point *point = malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    point->next = next;
    return point;
}

Point *prepend_point(Point *head, double x, double y) {
    Point *point = new_point(head, x, y);
    head = point;
    return head;
}

Point *find_index(Point *head, int index) {
    Point *temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp;
}

int is_empty(List *list) {
    if (list->head == NULL) {
        return 1;
    }
    return 0;
}

int num_elements(List *list) {
    Point *temp = list->head;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}
