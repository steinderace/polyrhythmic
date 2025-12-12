#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT(cond, msg) do {\
    if(!(cond)) {\
        printf("FAIL: %s\n", msg);\
        return 1;\
    }\
} while(0)

#define TEST_START(name) printf("Running test: %s\n", name)
#define TEST_PASS(name) printf("Passed: %s\n", name)

#endif
