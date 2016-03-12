#include <stdlib.h>
#include <stdio.h>
#include "libfusion_keys.h"
#include "dbg.h"

int main(void) {
    log_info("Fusion Keys POC starts\n");
    char buf[256];
    fk_init();
    map_put('a', 98);
    map_put('b', 100);
    map_put('c', 97);
    map_put('d', 120);
    map_put('e', 140);
    fk_read(buf, 256);
    printf("Readed keys: %s", buf);
    fk_exit();
    log_info("Fusion Keys POC ends\n");
    return 0;
}
