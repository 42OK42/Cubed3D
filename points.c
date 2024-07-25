#include <stdio.h>

typedef struct
{
    float x;
    float y;
} t_point;

#define NULL_TERMINATOR {-1.0f, -1.0f}

int main() {
    // Declare and initialize the null-terminated array of points
    t_point points[] = {
        {0.0f, 1.0f},
        {2.0f, 3.0f},
        {4.0f, 5.0f},
        NULL_TERMINATOR // Null terminator
    };

    // Assign the array to a variable (not strictly necessary as it's already done during declaration)
    t_point *points_array = points;

    // Print the points to demonstrate usage
    for (int i = 0; points_array[i].x != -1.0f || points_array[i].y != -1.0f; ++i) {
        printf("Point %d: (%f, %f)\n", i, points_array[i].x, points_array[i].y);
    }

    return 0;
}