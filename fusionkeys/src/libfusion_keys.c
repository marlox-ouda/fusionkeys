#include <stdio.h>
#include <unistd.h>
#include "libfusion_keys.h"
#include "dbg.h"


static int buf[256];

ssize_t fk_read(char *buffer, size_t size) {
    return read(STDIN_FILENO, buffer, size); 
}
