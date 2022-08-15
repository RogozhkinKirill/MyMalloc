#ifndef MYMALLOC_H
#define MYMALLOC_H

/**
 * @brief initMemory init memory. It should be called before using static memory
 * @return returns 1 if it was succesfull initialization
 */
int initMemory(void);

/**
 * @brief myMalloc get pointer to memory with desired size
 * @param sz - size of desired memory
 * @retval return the pointer to memory, if function returns NULL it means error
 */
char * myMalloc(int sz);

/**
 * @brief myFree free memory that was got by calling myMalloc
 * @param ptr_slice - pointer which shoud be freed
 * @return if memory freed succesfull, function return the same pointer, else NULL
 */
char * myFree(char * ptr_slice);

#endif // MYMALLOC_H
