#include "minunit.h"
#include "../src/maps.h"

char *test_empty() {
    map_init();
    mu_assert(!(map_has('a')), "map_has not a");
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_empty);

    return NULL;
}

RUN_TESTS(all_tests);
