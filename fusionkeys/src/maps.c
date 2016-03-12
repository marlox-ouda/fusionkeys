#include <string.h>
#include <stdbool.h>
#include "maps.h"
#include "dbg.h"

static mapblock_T *maphash[MAPHASH_SIZE] = { 0 };


void map_init() {
    memset(maphash, 0, sizeof(maphash));
}

bool map_has(char key) {
    const int index = ((int) key) % MAPHASH_SIZE;
    for (mapblock_T *map = maphash[index]; map; map = map->next) {
        if (map->key == key) return true;
    }
    return false;
}
