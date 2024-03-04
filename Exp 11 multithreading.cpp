#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

#define NUM_THREADS 5

void *print_hello(void *thread_id) {
    intptr_t tid;
    tid = (intptr_t)thread_id;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    intptr_t t;
    
    for(t = 0; t < NUM_THREADS; t++) {
        printf("Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            return -1;
        }
    }
    
    // Wait for all threads to complete
    for(t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }
    
    printf("All threads have completed.\n");
    pthread_exit(NULL);
}

