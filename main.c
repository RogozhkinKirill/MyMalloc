#include <stdio.h>
#include "myMalloc.h"


int main() {
    initMemory();

    char * buf = myMalloc(16);
    myFree(buf);
    char * buf1 = myMalloc(16);

    return 0;
}
