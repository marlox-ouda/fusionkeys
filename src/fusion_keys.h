#ifndef CFUSION_H
#define CFUSION_H

//#define _GNU_SOURCE
#include "actions.h"
#include "hash_table.h"
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif


struct fusion {
     struct actions_db * actions_db;
     struct hsearch_data * translation_table;
};

extern struct fusion *
fk_init();

extern void
fk_bind(struct fusion *, char, enum action);

extern ssize_t
fk_translate(struct fusion *, char *, enum action **, size_t);

extern void
fk_display_actions(struct fusion *, enum action *, size_t);

extern void
fk_exit(struct fusion *);

#ifdef __cplusplus
}
#endif

#endif
