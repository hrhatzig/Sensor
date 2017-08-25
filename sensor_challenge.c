/************************************
*		Sensor Challenge			*
*									*
*	Chrysostomos Chatzigeorgiou		*
* 	25/08/2017						*
*	hrhatzig@gmail.com 				*
*									*
************************************/
#include "sensor_challenge.h"

int main(int argc, char **argv)
{
	int greater           = 0,		// Counts the final result
        threasholds_count = 0,		// count the given threasholds
        threashold 		  = 0,
        *sensors_matrix	  = 0;		// have the values of alla the sensors

    size_t num_of_sensors    = 0,	// from first line
           num_of_thresholds = 0;	// from first line

    char temp;						// help variable
	
	struct timespec  tv1, tv2;

    scanf("%zu %zu", &num_of_sensors, &num_of_thresholds);

    list_init();

	do{
        scanf("%d%c", &threashold, &temp);
        list_insert(threashold);
        threasholds_count++; 
	} while(temp!= '\n');
	
	sensors_matrix = malloc(sizeof(int)*num_of_sensors*num_of_thresholds);
	if(sensors_matrix == NULL) {
		puts("Memory allocation fail.");
		exit(1);
	}

	for(int i = 0; i < num_of_sensors; i++) {
		int counter = 0,
			num 	= 0;
		scanf("%c%d", &temp, &num);
		// if((temp != 'S') || (num != i+1))
		// 	printf("You have to give S%d. Not %c%d\n", i+1, temp, num);
		do{
	        scanf("%d%c", &threashold, &temp);
	        sensors_matrix[i*num_of_thresholds + counter] = threashold;
	        counter++; 
		} while(temp!= '\n');
		if(counter != num_of_thresholds) {
			printf("You have to give %zu threasholds. Not %d.\n", num_of_thresholds, counter);
			exit(1);
		}
	}

	clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
	#pragma omp parallel for num_threads(1) 
	for(int i = 0; i < num_of_sensors; i++) {
        printf("S%d", i+1);
        for(struct given_threasholds *curr = root->prev; curr->prev->next != root; curr = curr->prev) {
            for(int j = 0; j < num_of_thresholds; j++) {
                if(sensors_matrix[i*num_of_thresholds + j] > curr->value)
                    greater++;
            }
            printf(" %d", greater);
            greater = 0;
        }
        puts("");
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);
    // puts(" ");

    // printf("Total time = %10g seconds\n",
    //        (double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
    //        (double) (tv2.tv_sec - tv1.tv_sec));

    /* Free allocated memory */
    list_remove();
    free(sensors_matrix);

	return (0);
}

/*
*	Function that initializes an empty doubly linked list.
*/
void list_init()
{
    root = malloc(sizeof(struct given_threasholds));
    if(root == NULL) {
        printf("**Memory allocation fail.**\n");
        exit(1);
    }

    root->next = root;
    root->prev = root;
}

/*
*	Function that insert a value at the begin of a doubly linked list.
* 	You have to give:
*		- (int) the value that you wont to insert
*/
void list_insert(int value)
{
    struct given_threasholds *curr = NULL;

    curr = malloc(sizeof(struct given_threasholds));
    if(curr == NULL) {
        printf("**Memory allocation fail.**\n");
        exit(1);
    }

    curr->value = value;

    /* insert at the begin of the list */
    curr->next = root->next;
    curr->prev = root;
    curr->next->prev = curr;
    curr->prev->next = curr;
}

/*
*	Function that free a doubly linked list.
*/
void list_remove()
{
    struct given_threasholds *curr = NULL;
    for(curr = root->prev; curr->prev->next != root; curr = curr->prev) 
        free(curr);
}

/*
*	Function that prints doubly linked list.
*/
void print_list()
{
    struct given_threasholds *curr = NULL;
    for(curr = root->prev; curr->prev->next != root; curr = curr->prev) {
        printf("%d ", curr->value);
    }
    puts("");
}

/*
*	Function that prints the given sensors.
*	You have to give:
*		- (int*)   the array
*		- (size_t) the # of sensors
*		- (size_t) the # of threasholds
*/
void print_sensors(int *sensors_matrix, size_t num_of_thresholds, size_t num_of_sensors)
{
	// Print sensors
	for(int i = 0; i < num_of_sensors; i++) {
		for(int j = 0; j < num_of_thresholds; j++) {
			printf("%d ", sensors_matrix[i*num_of_thresholds + j]);
		}
		puts(" ");
	}
}