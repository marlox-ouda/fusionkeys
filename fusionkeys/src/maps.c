#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "maps.h"
#include "dbg.h"

static mapblock_T *maphash[MAPHASH_SIZE] = { 0 };


void map_init() {
    memset(maphash, 0, sizeof(maphash));
}

void map_free() {
    mapblock_T *map;
    mapblock_T *next_map;
    for (int hash = 0; hash < MAPHASH_SIZE; ++hash) {
        for (map = maphash[hash]; map; map = next_map) {
            next_map = map->next;
            free(map);
        }
    }
    map_init();
}

inline const int map_hash(char key) {
    return ((int) key) % MAPHASH_SIZE;
}

bool map_has(char key) {
    mapblock_T *map;
    for (map = maphash[map_hash(key)]; map; map = map->next) {
        if (map->key == key) return true;
    }
    return false;
}

int map_put(char key, int new_act) {
    mapblock_T **map;
    for (map = &maphash[map_hash(key)]; *map; *map = (*map)->next) {
        if ((*map)->key == key) {
            (*map)->act = new_act;
            return 0;
        }
    }
    *map = malloc(sizeof(mapblock_T));
    check_mem(*map);
    (*map)->next = NULL;
    (*map)->key  = key;
    (*map)->act  = new_act;
    return 0;
    error:
        return 1;
}
