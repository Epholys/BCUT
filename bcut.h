/******************************************************************************
 *
 * BCUT - Barebones C Unit Tests
 * Copyright 2015 Thomas Munoz (epholys@gmail.com)
 *
 * BCUT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BCUT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BCUT. If not, see <http://www.gnu.org/licenses/>.
 * 
 *****************************************************************************/

/*! \file
 *  \brief The Barebones C Unit Test functions and macros.
 *  
 * # Use
 * Declare and define every unit test with BCUT_TEST(). In each unit test, use
 * BCUT_ASSERT() to validate a boolean expression. Finally, run a test suite by
 * calling bcut_suite_run().
 *
 * # Exemple
 * ~~~c
 * #include"bcut.h"
 * 
 * bool greater(int x, int y) { return x > y; }
 * 
 * BCUT_TEST(greater_test)  { BCUT_ASSERT(greater(1337,42)); }
 * 
 * int main()
 * {
 *  bcut_suite_run("Dummy test", 1, greater_test);
 *  return 0;
 * }
 * ~~~
 */

#ifndef BCUT_H
#define BCUT_H


#include<stdbool.h>
#include<stdarg.h>
#include<stdio.h>
#include<string.h>

#ifndef BCUT_BUFFER_SIZE
/*! \brief Size of the character buffer used in every TEST and ASSERT
 */
#define BCUT_BUFFER_SIZE (128)
#endif

/*! \brief Function's pointer typedef of BCUT_TEST() for using it in
 *  bcut_run_suite.
 */
typedef void (*bcut_test_fn) (char*, bool*);

/*! \brief Function signature of a BCUT unit test function.
 *
 *  \param[in] name Identifier of the function's signature generated.
 *  
 *  \param[out] bcut_error A string of length BCUT_BUFFER_SIZE in which
 *  the error message will be written if a BCUT_ASSERT is not respected.
 *  \param[in,out] bcut_pass The boolean indicating wether the test is
 *  validated.
 *  
 */
#define BCUT_TEST(name)                                                 \
    void name (char* bcut_error, bool* bcut_pass)

/*! \brief Basic assertion that modify bcut_pass and bcut_error if it is not
 *  validated.
 *
 *  Several BCUT_ASSERT() per BCUT_TEST() is authorized, but only the first
 *  failure will be reported.
 */
#define BCUT_ASSERT(expr)                                                \
    do{                                                                  \
        if(*bcut_pass) {                                                 \
            *bcut_pass=(expr);                                           \
            if(!(*bcut_pass)) {                                          \
                snprintf(bcut_error, BCUT_BUFFER_SIZE, "%s: l%d: "#expr, \
                         __func__, __LINE__);                            \
            }                                                            \
        }                                                                \
    }while(0)

/*! \brief Groups and tests several BCUT_TEST() in a row, printing wether it
 * succeeded and where it failed, if applicable.
 *
 *  \param[in] name The suite's name that will be reminded at the beginning of
 * the tests.
 *  \param[in] n The number of BCUT_TEST() provided by the variadic arguments.
 *  \param[in] ... All the bcut_test_fn -typed BCUT_TEST() that will be
 * evaluated.
 */
static inline void bcut_suite_run(const char* name, size_t n, ...)
{
    size_t i = 0;
    char error_buffer[BCUT_BUFFER_SIZE];
    bool pass = true;
    bcut_test_fn unit_test = NULL;

    va_list args;
    va_start (args, n);
    
    printf("Testing %s: ", name);
    for(i=0; i<n && pass; ++i)
    {
        unit_test = va_arg(args, bcut_test_fn);
        unit_test(error_buffer, &pass);
        if(!pass)
        {
            printf("\n\tFAIL: %s\n", error_buffer);
        }           
    }
    if(pass)
    {
        printf("PASSED!\n");
    }
}


#endif /* BCUT_H */
