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

void
fk_translate(struct fusion * fusion, char * buffer, size_t size)
{
    translate(fusion->actions_db, fusion->translation_table, buffer, size);
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
