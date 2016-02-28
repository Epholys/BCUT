# BCUT
Barebones C Unit Tests

## Use
Declare and define every unit test with BCUT_TEST(). In each unit test, use BCUT_ASSERT() to validate a boolean expression. Finally, run a test suite by calling bcut_suite_run().

## Exemple

~~~c
#include"bcut.h"

bool greater(int x, int y) { return x > y; }

BCUT_TEST(greater_test)  { BCUT_ASSERT(greater(1337,42)); }

int main()
{
	bcut_suite_run("Dummy test", 1, greater_test);
	return 0;
}
~~~

## Hacking
By default, if a unit test fails, a message containing __func__, __LINE__ and the boolean expression tested is displayed. To avoid buffer overflows, this message has a limited size of 128 bytes defined by the macro BCUT_BUFFER_SIZE which you can easily override.
