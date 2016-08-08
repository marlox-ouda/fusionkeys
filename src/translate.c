#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
#include "hash_table.h"
#include "actions.h"
#include "dbg.h"

#define BASIC_LEN 200

void
add_bind(struct hsearch_data * translation_table, char binded_key, enum action action)
{
    char * entry_key = calloc(2, sizeof(char));
    check_mem(entry_key);
    entry_key[0] = binded_key;
    check(translation_table, "add_bind: translation_table is NULL -> fail to add a binding");
    hash_put_element(translation_table, entry_key, (void *)(long)(unsigned int) action);
    error:
         return;
}

enum action
lookfor_key(struct hsearch_data * translation_table, char key)
{
    char entry_key[] = "\0\0";
    entry_key[0] = key;
    check(translation_table, "lookfor_key: translation_table is NULL -> return A_NIL action");
    return (enum action)(unsigned int)(long)hash_get_element(translation_table, entry_key);
    error:
        return A_NIL;
}

ssize_t
translate(struct hsearch_data * translation_table, char * input_keys, enum action ** output_actions, size_t size)
{
    ssize_t output_size = 0;
    enum action current_action;
    (*output_actions) = malloc(size * sizeof(enum action));
    check_mem(output_actions);
    check(translation_table, "translate: translation_table is NULL -> return -1");
    check(input_keys != NULL, "translate: input_keys buffer is null -> return -1");
    for (size_t index = 0; index < size; ++index)
      {
        if (input_keys == '\0') break;
        current_action = lookfor_key(translation_table, input_keys[index]);
        if (current_action != (unsigned int)(long)NIL) {
            (*output_actions)[output_size++] = current_action;
        }
      }
    return output_size;
    error:
        if (*output_actions) free(*output_actions);
        return -1;
}
