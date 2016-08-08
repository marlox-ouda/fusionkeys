#ifndef CACTIONS_H
#define CACTIONS_H

#ifdef __cplusplus
//extern "C" {
#endif

enum action
{
#define KEY(key, value) key = value,
#include "actions.inc"
#undef KEY
};

struct actions_db
{
    struct hsearch_data * labels;
    //struct hsearch_data * 
};

struct actions_db *
action_create_db();

void
action_destroy_db(struct actions_db *);

char *
action_get_label(struct actions_db * ,enum action);

#ifdef __cplusplus
//}
#endif

#endif
