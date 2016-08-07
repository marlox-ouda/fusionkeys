#ifndef CACTIONS_H
#define CACTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

enum action
{
#define KEY(key, value) key = value,
#include "actions.inc"
#undef KEY
};

#ifdef __cplusplus
}
#endif

#endif
