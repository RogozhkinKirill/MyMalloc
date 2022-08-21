#include "myMalloc.h"

#include <stdio.h>


#define BUF_SIZE 1000
#define MAX_SLICES 100

static char memory[BUF_SIZE];

typedef struct slice {
    char * begin;
    int size;
} SLICE, *pSLICE;

static int cnt_shared_slices = 0;

static SLICE free_slices[MAX_SLICES];
static SLICE shared_slices[MAX_SLICES];

int initMemory(void) {
    for(int i=0; i<MAX_SLICES; i++) {
        free_slices[i].begin = shared_slices[i].begin = NULL;
        free_slices[i].size =  shared_slices[i].size = 0;
    }

    cnt_shared_slices = 0;

    free_slices[0].begin = memory;
    free_slices[0].size = BUF_SIZE;

    return 0;
}

static int splitSlice(int pos, int sz) {
    for(int i=0; i<MAX_SLICES; i++) {
        if(!free_slices[i].begin) {
            free_slices[i].begin = free_slices[pos].begin + sz;
            free_slices[i].size = free_slices[pos].size - sz;

            return 1;
        }
    }

    return 0;
}

char * myMalloc(int sz) {
    if(cnt_shared_slices < MAX_SLICES) {
        for(int i=0; i<MAX_SLICES; i++) {
            if(free_slices[i].begin && free_slices[i].size >= sz) {
                cnt_shared_slices++;

                shared_slices[i].begin = free_slices[i].begin;

                if(splitSlice(i, sz)) {
                    shared_slices[i].size = sz;
                } else {
                    shared_slices[i].size = free_slices[i].size;
                }


                free_slices[i].begin = NULL;
                free_slices[i].size = 0;

                return shared_slices[i].begin;
            }
        }
    }

    return NULL;
}

char * myFree(char * ptr_slice) {
    for(int i=0; i<MAX_SLICES; i++) {
        if(ptr_slice == shared_slices[i].begin) {
            free_slices[i].begin = shared_slices[i].begin;
            free_slices[i].size =  shared_slices[i].size;

            shared_slices[i].begin = NULL;
            shared_slices[i].size = 0;
            cnt_shared_slices--;

            return ptr_slice;
        }
    }

    return NULL;
}

int myAvail(void) {
    int res = 0;

    for(int i=0; i<MAX_SLICES; i++) {
        if(free_slices[i].begin)
            res += free_slices[i].size;
    }

    return res;
}
