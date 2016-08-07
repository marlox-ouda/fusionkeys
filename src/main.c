//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
#include "fusion.h"
#include "actions.h"
//#include "translate.h"
//#include "dbg.h"

int
main(void)
{
    struct fusion * fusion = fk_init();

    char buf[256];

    fk_bind(fusion, 'a', A_UP);
    fk_bind(fusion, 'b', A_PLAY);
    fk_bind(fusion, 'c', A_LEFT);
    fk_bind(fusion, 'd', A_RIGHT);
    fk_bind(fusion, 'e', A_DOWN);
    fk_translate(fusion, buf, 256);
    //printf("Readed keys: %s", buf);
    fk_exit(fusion);
}
