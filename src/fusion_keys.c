#include "fusion_keys.h"
#include "translate.h"
#include "dbg.h"

#define BASIC_LEN 200

struct fusion *
fk_init()
{
    struct fusion * fusion = malloc(sizeof(struct fusion));
    check_mem(fusion);
    fusion->actions_db = action_create_db();
    raise(fusion->actions_db);
    fusion->translation_table = hash_create(BASIC_LEN);
    raise(fusion->translation_table);
    log_info("Fusion Keys POC starts\n");
    return fusion;
    error:
        return NULL;
}

void
fk_bind(struct fusion * fusion, char key, enum action action)
{
    check(fusion, "fk_bind: fusion is NULL");
    add_bind(fusion->translation_table, key, action);
    error:
        return;
}

ssize_t
fk_translate(struct fusion * fusion, char * buffer, enum action ** actions, size_t size)
{
    check(fusion, "fk_translate: fusion is NULL -> return 0");
    check(buffer, "fk_display_actions: buffer is NULL -> return 0");
    return translate(fusion->translation_table, buffer, actions, size);
    error:
        return 0;
}

void
fk_display_actions(struct fusion * fusion, enum action * actions, size_t size)
{
    check(fusion, "fk_display_actions: fusion is NULL");
    check(fusion, "fk_display_actions: actions is NULL");
    char * label;
    for (size_t index = 0; index < size; ++index)
      {
        label = action_get_label(fusion->actions_db, actions[index]);
        if (label) printf("%s\n", label);
        else printf("Unknown action\n");
      }
    error:
        return;
}

void
fk_exit(struct fusion * fusion)
{
    log_info("Fusion Keys POC ends\n");
    check(fusion, "fk_exit: fusion is NULL");
    hash_destroy(fusion->translation_table);
    action_destroy_db(fusion->actions_db);
    free(fusion);
    error:
        return;
}
