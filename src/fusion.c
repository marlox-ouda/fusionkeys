#include "fusion.h"
//#include <stdlib.h>
//#include <unistd.h>
//#include "hash_table.h"
//#include "actions.h"
#include "translate.h"
#include "dbg.h"

#define BASIC_LEN 200

struct fusion *
fk_init()
{
    struct fusion * fusion = malloc(sizeof(struct fusion));
    check_mem(fusion);
    fusion->actions_db = action_create_db();
    fusion->translation_table = hash_create(BASIC_LEN);
    log_info("Fusion Keys POC starts\n");
    return fusion;
    error:
        return NULL;
}

void
fk_bind(struct fusion * fusion, char key, enum action action)
{
    add_bind(fusion->translation_table, key, action);
}

ssize_t
fk_translate(struct fusion * fusion, char * buffer, enum action ** actions, size_t size)
{
    return translate(fusion->translation_table, buffer, actions, size);
}

void
fk_display_actions(struct fusion * fusion, enum action * actions, size_t size)
{
    char * label;
    for (size_t index = 0; index < size; ++index)
      {
        label = action_get_label(fusion->actions_db, actions[index]);
        if (label) printf("%s\n", label);
        else printf("????\n");
      }
}

void
fk_exit(struct fusion * fusion)
{
    log_info("Fusion Keys POC ends\n");
    if (fusion)
      {
        hash_destroy(fusion->translation_table);
        action_destroy_db(fusion->actions_db);
        free(fusion);
      }
}
