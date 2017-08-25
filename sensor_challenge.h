#ifndef SENSOR_CHALLENGE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

struct given_threasholds {
    int value;
    struct given_threasholds *next;
    struct given_threasholds *prev;
};

extern void list_init	 ();
extern void list_insert	 (int value);
extern void list_remove	 ();
extern void print_list	 ();
extern void print_sensors(int *sensors_matrix, size_t num_of_thresholds, size_t num_of_sensors);

struct given_threasholds *root;

#endif // SENSOR_CHALLENGE_H