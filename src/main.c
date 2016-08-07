#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "hash_table.h"
#include "actions.h"
#include "translate.h"
#include "dbg.h"

#define BASIC_LEN 200

int
main(void)
{
    struct hsearch_data * translate_table;
    struct actions_db * actions_db;
    log_info("Fusion Keys POC starts\n");

    translate_table = hash_create(BASIC_LEN);
    actions_db = action_create_db();
    
    char buf[256];

    add_bind(translate_table, 'a', A_UP);
    add_bind(translate_table, 'b', A_PLAY);
    add_bind(translate_table, 'c', A_LEFT);
    add_bind(translate_table, 'd', A_RIGHT);
    add_bind(translate_table, 'e', A_DOWN);
    translate(actions_db, translate_table, buf, 256);
    //printf("Readed keys: %s", buf);
    log_info("Fusion Keys POC ends\n");
    hash_destroy(translate_table);
    action_destroy_db(actions_db);
}
