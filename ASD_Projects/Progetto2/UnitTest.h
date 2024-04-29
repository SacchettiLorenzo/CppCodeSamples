#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void fail();
void success();
void assert_true(bool expected);
void assert_false(bool expected);
void assert_equals_int(const int expected, const int actual);
void assert_equals_float(const float expected, const float actual);
void assert_equals_char_array(const char* expeced, const char* actual, int size);
void assert_equals_bool(const bool expected, const bool actual);
void assert_not_equals_int(const int expected, const int actual);
void assert_not_equals_float(const float expected, const float actual);
void assert_not_equals_char_array(const char* expeced, const char* actual, int size);
void assert_not_equals_bool(const bool expected, const bool actual);
void assert_null(void* ptr);
void assert_not_null(void* ptr);
void assert_same(void* expected, void* actual);
void assert_not_same(void* expected, void* actual);

static struct UnitTest
{
    void (*fail)();
    void (*success)();
    void (*assert_true)(bool);
    void (*assert_false)(bool);
    void (*assert_equals_int)(const int, const int);
    void (*assert_equals_float)(const float, const float);
    void (*assert_equals_char_array)(const char*, const char*,int);
    void (*assert_equals_bool)(const bool, const bool);
    void (*assert_not_equals_int)(const int, const int);
    void (*assert_not_equals_float)(const float, const float);
    void (*assert_not_equals_char_array)(const char*, const char*,int);
    void (*assert_not_equals_bool)(const bool, const bool);
    void (*assert_null)(void*);
    void (*assert_not_null)(void*);
    void (*assert_same)(void*, void*);
    void (*assert_not_same)(void*, void*);
    void (*perform_test)();
    int current_test_index;
    bool *result;
} ;
static struct UnitTest UT = {&fail,&success,&assert_true,&assert_false,&assert_equals_int,&assert_equals_float,&assert_equals_char_array,&assert_equals_bool,
        &assert_not_equals_int,&assert_not_equals_float,&assert_not_equals_char_array,&assert_not_equals_bool,&assert_null,&assert_not_null,&assert_same,&assert_not_same,NULL,0,NULL};


