#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <search.h>
//#include "libfusion_keys.h"
//#include "maps.h"
#include "hash_table.h"
#include "actions.h"
#include "dbg.h"

#define BASIC_LEN 200

void
insert_key(struct hsearch_data * table, char key, long action)
{
    char * entry_key = malloc(2 * sizeof(char));
    entry_key[0] = key;
    entry_key[1] = '\0';
    hash_put_element(table, entry_key, (long *) action);
}

long
lookfor_key(struct hsearch_data * table, char key)
{
    char entry_key[] = "\0\0";
    entry_key[0] = key;
    return (long)hash_get_element(table, entry_key);
}

char *
action_key(int index)
{
    char * entry_key = malloc(5 * sizeof(char));
    entry_key[4] = '\0';
    entry_key[3] = (index >> 24) & 0xFF;
    entry_key[2] = (index >> 16) & 0xFF;
    entry_key[1] = (index >> 8) & 0xFF;
    entry_key[0] = index & 0xFF;
    return entry_key;
}

ssize_t
translate(struct hsearch_data * actions, struct hsearch_data *table, char *buffer, size_t size)
{
    size_t idx_buffer = 0;
    size_t idx_end;
    char *tmp_buf = malloc(size * sizeof(char));
    int car;
    check_mem(tmp_buf);
    check(buffer != NULL, "buffer is null");
    idx_end = read(STDIN_FILENO, tmp_buf, size); 
    check(idx_end > 0, "read(stdio) fail");
    for (size_t idx_tmp_buf = 0; idx_tmp_buf < idx_end; ++idx_tmp_buf)
      {
        car = lookfor_key(table, tmp_buf[idx_tmp_buf]);
        if (car != (long)NIL) {
            printf("%s\n", (char *)hash_get_element(actions, action_key(car)));
        }
      }
    free(tmp_buf);
    return idx_buffer;
    error:
        free(tmp_buf);
        return 0;
}

void
insert_action(struct hsearch_data * actions_name, int index, char label[])
{
    hash_put_element(actions_name, action_key(index), strdup(label));
}

void
load_actions(struct hsearch_data * actions_name)
{
#define KEY(label, valeur) insert_action(actions_name, valeur, #label);
#include "actions.inc"
#undef KEY
}


int
main(void)
{
    struct hsearch_data * translate_table;
    struct hsearch_data * actions_name;
    log_info("Fusion Keys POC starts\n");

    translate_table = hash_create(BASIC_LEN);
    actions_name = hash_create(200);
    
    char buf[256];

    load_actions(actions_name);

    insert_key(translate_table, 'a', A_UP);
    insert_key(translate_table, 'b', A_PLAY);
    insert_key(translate_table, 'c', A_LEFT);
    insert_key(translate_table, 'd', A_RIGHT);
    insert_key(translate_table, 'e', A_DOWN);
    translate(actions_name, translate_table, buf, 256);
    //printf("Readed keys: %s", buf);
    log_info("Fusion Keys POC ends\n");
    hdestroy_r(translate_table);
    hdestroy_r(actions_name);
}
