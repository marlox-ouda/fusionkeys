#include <hash_table.h>
#include <stdlib.h>
#include "dbg.h"


struct hsearch_data *
hash_create(ssize_t len) {
    struct hsearch_data * table;
    table = malloc(sizeof(table));
    check_mem(table);
    check(hcreate_r(len, table), "hash_create: fail to create an htable -> return NULL");
    return table;
    error:
    if (table) free(table);
    return NULL;
}

void
hash_put_element(struct hsearch_data * table, char * key, void * data)
{
    ENTRY new_entry = { key, data };
    ENTRY *ret_entry = &new_entry;
    check(table, "hash_put_element: table is NULL -> fail to insert a key");
    check(key, "hash_put_element: key is NULL -> fail to insert a key");
    check(hsearch_r(new_entry, ENTER, &ret_entry, table), "hash_put_element: fail to insert a key");
    ret_entry->data = data;
    error:
    return;
}

void *
hash_get_element(struct hsearch_data * table, char * key)
{
    ENTRY looked_entry = { key, NULL };
    ENTRY *found_entry = &looked_entry;
    check(table, "hash_get_element: table is NULL -> fail to get a key -> return NIL");
    check(key, "hash_get_element: key is NULL -> fail to get a key -> return NIL");
    if (hsearch_r(looked_entry, FIND, &found_entry, table))
      {
        return found_entry->data;
      }
    error:
        return NIL;
}

bool
hash_has_element(struct hsearch_data * table, char * key)
{
    return (hash_get_element(table, key) != NIL);
}

void
hash_delete_element(struct hsearch_data * table, char * key)
{
    ENTRY looked_entry = { key, NULL };
    ENTRY *found_entry = &looked_entry;
    check(table, "hash_delete_element: table is NULL -> fail to delete a key");
    check(key, "hash_delete_element: key is NULL -> fail to delete a key");
    if (hsearch_r(looked_entry, FIND, &found_entry, table))
      {
        found_entry->data = NIL;
      }
    error:
        return;
}

void
hash_destroy(struct hsearch_data * table)
{
    check(table, "hash_destroy: table is NULL -> fail to destroy it");
    hdestroy_r(table);
    error:
         return;
}
