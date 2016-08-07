#include "actions.h"
#include <stdlib.h>
#include "hash_table.h"
#include "dbg.h"


char *
action_key(int index)
{
    char * entry_key = malloc(5 * sizeof(char));
    check_mem(entry_key);
    entry_key[4] = '\0';
    entry_key[3] = (index >> 24) & 0xFF;
    entry_key[2] = (index >> 16) & 0xFF;
    entry_key[1] = (index >> 8) & 0xFF;
    entry_key[0] = index & 0xFF;
    return entry_key;
    error:
        return NULL;
}

void
actions_add_label(struct hsearch_data * labels_db, int index, char label[])
{
    hash_put_element(labels_db, action_key(index), strdup(label));
}

struct actions_db *
action_create_db()
{
    struct actions_db * db = malloc(sizeof(struct actions_db));
    check_mem(db);
    db->labels = hash_create(200);
#define KEY(label, valeur) actions_add_label(db->labels, valeur, #label);
#include "actions.inc"
#undef KEY
    return db;
    error:
        return NULL;
}


char *
action_get_label(struct actions_db * db, enum action action)
{
    char * label = hash_get_element(db->labels, action_key(action));
    if (label == (char *)NIL) {
        return NULL;
    }
    return label;
}

void
action_destroy_db(struct actions_db * db)
{
    hash_destroy(db->labels);
    free(db);
}
