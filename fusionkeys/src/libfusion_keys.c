#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libfusion_keys.h"
#include "maps.h"
#include "dbg.h"


static int buf[256];

void fk_init() {
    map_init();
}

void fk_exit() {
    map_free();
}

ssize_t fk_read(char *buffer, size_t size) {
    size_t idx_buffer = 0;
    size_t idx_end;
    char *tmp_buf = malloc(size * sizeof(char));
    int car;
    check_mem(tmp_buf);
    check(buffer != NULL, "buffer is null");
    idx_end = read(STDIN_FILENO, tmp_buf, size); 
    check(idx_end > 0, "read(stdio) fail");
    for (size_t idx_tmp_buf = 0; idx_tmp_buf < idx_end; ++idx_tmp_buf) {
        car = map_get(tmp_buf[idx_tmp_buf]);
        if (car) {
            buffer[idx_buffer++] = (char)(car);
        }
    }
    free(tmp_buf);
    return idx_buffer;
    error:
        free(tmp_buf);
        return 0;
}
