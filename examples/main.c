#include <unistd.h>
#include "../src/fusion_keys.h"
#include "../src/dbg.h"

#define BUF_MAX_SIZE 256

int
main(void)
{
    struct fusion * fusion = fk_init();
    raise(fusion);
    enum action * actions = NULL;

    char buf[BUF_MAX_SIZE];
    ssize_t buf_size;

    fk_bind(fusion, 'a', A_UP);
    fk_bind(fusion, 'b', A_PLAY);
    fk_bind(fusion, 'c', A_LEFT);
    fk_bind(fusion, 'd', A_RIGHT);
    fk_bind(fusion, 'e', A_DOWN);
    buf_size = read(STDIN_FILENO, buf, BUF_MAX_SIZE);
    check(buf_size > 0, "read(stdio) fail");
    buf_size = fk_translate(fusion, buf, &actions, buf_size);
    fk_display_actions(fusion, actions, buf_size);
    error:
        fk_exit(fusion);
}
