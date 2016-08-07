#ifndef CFUSION_H
#define CFUSION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "actions.h"
#include "hash_table.h"
#define _GNU_SOURCE
//#include <stdlib.h>

struct fusion {
     struct actions_db * actions_db;
     struct hsearch_data * translation_table;
};

struct fusion *
fk_init();

void
fk_bind(struct fusion *, char, enum action);

void
fk_translate(struct fusion *, char *, size_t);

void
fk_exit(struct fusion *);

#ifdef __cplusplus
}
#endif

#endif
