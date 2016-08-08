#include <hash_table.h>
#include <stdlib.h>
#include "dbg.h"


struct hsearch_data *
hash_create(ssize_t len) {
    struct hsearch_data * table;
    table = malloc(sizeof(table));
    check_mem(table);
    check(hcreate_r(len, table), "Fail to create an htable");
    return table;
    error:
    return NULL;
}

void
hash_put_element(struct hsearch_data * table, char * key, void * data)
{
    ENTRY new_entry = { key, data };
    ENTRY *ret_entry = &new_entry;
    check(hsearch_r(new_entry, ENTER, &ret_entry, table), "Fail to insert a key");
    ret_entry->data = data;
    error:
    return;
}

void *
hash_get_element(struct hsearch_data * table, char * key)
{
    ENTRY looked_entry = { key, NULL };
    ENTRY *found_entry = &looked_entry;
    if (hsearch_r(looked_entry, FIND, &found_entry, table))
      {
        return found_entry->data;
      }
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
    if (hsearch_r(looked_entry, FIND, &found_entry, table))
      {
        found_entry->data = NIL;
      }
}

void
hash_destroy(struct hsearch_data * table)
{
    if (!table)
        hdestroy_r(table);
}
