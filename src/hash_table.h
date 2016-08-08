#ifndef CHASH_TABLE_H
#define CHASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdbool.h>
#include <search.h>

//#define BASIC_LEN 200
#define NIL (void *)(-1)

struct hsearch_data *
hash_create(ssize_t);

void
hash_put_element(struct hsearch_data *, char *, void *);

void *
hash_get_element(struct hsearch_data *, char *);

bool
hash_has_element(struct hsearch_data *, char *);

void
hash_delete_element(struct hsearch_data *, char *);

void
hash_destroy(struct hsearch_data *);

#ifdef __cplusplus
}
#endif

#endif
