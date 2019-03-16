#include "testAssert.h"

int assertTrue(int actualValue, int expectedValue, char* message) {
    if (actualValue != expectedValue) {
        printf(message);
        printf(", Actual: %d, Expected: %d\n", actualValue, expectedValue);
        return 1;
    }
    return 0;
}