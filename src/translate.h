#ifndef CTRANSLATE_H
#define CTRANSLATE_H

#ifdef __cplusplus
extern "C" {
#endif

void
add_bind(struct hsearch_data *, char, enum action);

enum action
lookfor_key(struct hsearch_data *, char);

ssize_t
translate(struct actions_db *, struct hsearch_data *, char *, size_t);


#ifdef __cplusplus
}
#endif

#endif
