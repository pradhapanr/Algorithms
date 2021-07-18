#include <stdio.h>
#include <stdlib.h>

/**
 * Very basic list structure to simplify algorithm code
 */

typedef struct Point {
    double x;
    double y;
    struct Point *next;
} Point;

typedef struct List {
    Point *head;
} List;


Point *new_point(Point *next, double x, double y);
Point *prepend_point(Point *head, double x, double y);
Point *find_index(Point *head, int index);
int is_empty(List *list);
int num_elements(List *list);