#include <stdlib.h>
#include <stdio.h>
#include "libfusion_keys.h"
#include "dbg.h"

int main(void) {
    log_info("Fusion Keys POC starts\n");
    char buf[256];
    fk_read(buf, 256);
    printf("Readed keys: %s", buf);
    log_info("Fusion Keys POC ends\n");
    return 0;
}
