#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "hash_table.h"
#include "actions.h"
#include "dbg.h"

#define BASIC_LEN 200

void
add_bind(struct hsearch_data * table, char binded_key, long action)
{
    char * entry_key = malloc(2 * sizeof(char));
    entry_key[0] = binded_key;
    entry_key[1] = '\0';
    hash_put_element(table, entry_key, (void *) action);
}

long
lookfor_key(struct hsearch_data * table, char key)
{
    char entry_key[] = "\0\0";
    entry_key[0] = key;
    return (long)hash_get_element(table, entry_key);
}

ssize_t
translate(struct actions_db * actions, struct hsearch_data *table, char *buffer, size_t size)
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
            printf("%s\n", action_get_label(actions, car));
        }
      }
    free(tmp_buf);
    return idx_buffer;
    error:
        free(tmp_buf);
        return 0;
}
