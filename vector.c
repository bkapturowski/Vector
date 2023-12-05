#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int vector_create_struct(struct vector_t **a, int N){
    if(a == NULL || N <= 0){
        return 1;
    }

    *a = malloc(sizeof(struct vector_t));
    if (*a == NULL) {
        return 2;
    }

    (*a)->ptr = malloc(sizeof(int) * N);
    if((*a)->ptr == NULL){
        free(*a);
        return 2;
    }

    (*a)->size = 0;
    (*a)->capacity = N;

    return 0;
}
void vector_destroy_struct(struct vector_t **a){
    if (a == NULL || *a == NULL) {
        return;
    }
    free((*a)->ptr);
    free(*a);
    *a = NULL;
}

int vector_create(struct vector_t *a, int N){
    if(a == NULL || N <= 0){
        return 1;
    }

    a->ptr = malloc(sizeof(int) * N);
    if(a->ptr == NULL){
        return 2;
    }
    a->size = 0;
    a->capacity = N;


    return 0;
}
void vector_destroy(struct vector_t *a){
    if (a != NULL && a->ptr != NULL){
        free(a->ptr);
        a->ptr = NULL;
        a->size = 0;
        a->capacity = 0;
    }
}

void vector_display(const struct vector_t *a){
    if(a != NULL && a->size <= a->capacity && a->size > 0 && a->ptr != NULL && a->capacity > 0){
        for (int i = 0; i < a->size; ++i) {
            printf("%d ", *(a->ptr + i));
        }
        printf("\n");
    }
}

int vector_push_back(struct vector_t *a, int value){
    if(a == NULL || a->size > a->capacity || a->size < 0 || a->ptr == NULL || a->capacity <= 0){
        return 1;
    }

    if(a->size == a->capacity) {
        int *new_data = realloc(a->ptr, 2 * a->capacity * sizeof(int));
        if(new_data == NULL){
            //free(a->ptr);
            return 2;
        }
        a->ptr = new_data;
        a->capacity *= 2;
    }

    *(a->ptr + a->size) = value;
    a->size++;

    return 0;
}
int vector_erase(struct vector_t *a, int value){
    if(a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->size > a->capacity){
        return -1;
    }

    int c=0;
    for (int i = 0; i < a->size; ++i) {
        if(*(a->ptr + i) == value)
            c++;
    }

    if (c == 0) {
        if (a->size == 0 && a->capacity >= 0) {
            int new_capacity = a->capacity / 2;
            int *new_data = realloc(a->ptr, new_capacity * sizeof(int));
            if (new_data != NULL) {
                a->ptr = new_data;
                a->capacity = new_capacity;
                return 0;
            }
            else{
                return 2;
            }
        }
    }


    for (int i = 0, j = 0; i < a->size; ++i) {
        if (*(a->ptr + i) != value) {
            *(a->ptr + j) = *(a->ptr + i);
            j++;
        }
    }


    a->size = a->size - c;

    if (a->size < a->capacity * 0.25) {
        int new_capacity = a->capacity / 2;
        if (new_capacity < 1) {
            new_capacity = 1;
        }

        int *new_data = realloc(a->ptr, new_capacity * sizeof(int));
        if (new_data != NULL) {
            a->ptr = new_data;
            a->capacity = new_capacity;
        }
        else{
            return 2;
        }
    }


    return c;
}

