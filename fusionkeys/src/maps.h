#ifndef CMAPS_H
#define CMAPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/* Must be power of 2 */
#define MAPHASH_SIZE 256

/*
 * Structure used for mapping keys to act
 */
typedef struct mapblock mapblock_T;

struct mapblock {
    mapblock_T    * next;   /* next mapblock in the list */
    char            key;    /* mapping from */
    char            act;    /* mapping to */
};


void map_init();
bool map_has(char);
int map_put(char, int);

#ifdef __cplusplus
}
#endif

#endif
