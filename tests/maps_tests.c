#include "minunit.h"
#include "../src/maps.h"

char *test_empty() {
    map_init();
    mu_assert(!map_has('a'), "map_has not a");
    map_free();
    return NULL;
}

char *test_put_and_has() {
    map_init();
    mu_assert(!map_has('b'), "map_has not b");
    mu_assert(map_put('b', 1) == 0, "map_put return 0");
    mu_assert(map_has('b'), "map_has b");
    mu_assert(map_put('b', 1) == 0, "map_put return 0");
    mu_assert(map_put('b', 1) == 0, "map_put return 0");
    mu_assert(!map_has('c'), "map_has not c");
    map_free();
    return NULL;
}

char *test_put_and_get() {
    map_init();
    mu_assert(map_get('d') == 0, "map_get(d) return 0");
    mu_assert(map_put('d', 2) == 0, "map_put return 0 (ok)");
    mu_assert(map_get('d') == 2, "map_get(d) return 2");
    mu_assert(map_put('d', 4) == 0, "map_put return 0 (ok)");
    mu_assert(map_get('d') == 4, "map_get(d) return 4");
    mu_assert(map_get('e') == 0, "map_get(e) return 0");
    map_free();
    return NULL;
}

char *test_put_delete_and_has() {
    map_init();
    mu_assert(!map_has('f'), "map_has(f) false(1)");
    mu_assert(map_put('f', 2) == 0, "map_put return 0 (ok)");
    mu_assert(map_has('f'), "map_has(f) true");
    mu_assert(map_delete('f') == 0, "map_delete(f) return 0 (ok)");
    mu_assert(!map_has('f'), "map_has(f) false(2)");
    mu_assert(map_delete('f') == -1, "map_delete(f) return -1 (fail)");
    mu_assert(!map_has('f'), "map_has(f) false(3)");
    map_free();
    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_empty);
    mu_run_test(test_put_and_has);
    mu_run_test(test_put_and_get);
    mu_run_test(test_put_delete_and_has);

    return NULL;
}

RUN_TESTS(all_tests);
