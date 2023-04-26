#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* customer(void* arg) {
	int* n = malloc(4);
	*n = 1;
	while (*n<5) {
		printf("%i\n", *n);
		*n += 1;
		sleep(2);
	}
	return n;
}

int main (int argc, char** argv) {
	pthread_t c1;
	void* retval = NULL;
	
	pthread_create(&c1, NULL, &customer, NULL);

	pthread_join(c1, &retval);
	printf("Returned: %i\n", *(int*)retval);
	free(retval);

	return 0;
}

