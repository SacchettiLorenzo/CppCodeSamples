#include <stdbool.h>
#include <stdarg.h>

typedef struct UnitTest
{
    void (*new_unit_test)(int);
    void (*fail)(int);
    void (*success)();
    void (*assert_true)();
    void (*assert_false)();
    void (*assert_equals_int)(const int, const int);
    void (*assert_equals_float)(const float, const float);
    void (*assert_equals_char_array)(const char*, const char*);
    void (*assert_equals_bool)(const bool, const bool);
    void (*assert_not_equals_int)(const int, const int);
    void (*assert_not_equals_float)(const float, const float);
    void (*assert_not_equals_char_array)(const char*, const char*);
    void (*assert_not_equals_bool)(const bool, const bool);
    void (*assert_null)(void*);
    void (*assert_not_null)(void*);
    void (*assert_same)(void*, void*);
    void (*assert_not_same)(void*, void*);
    void (*perform_test)();
    int current_test_index;
    bool *result;
} UT;

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

void fail()
{
    UT.result[UT.current_test_index] = false;
}
void success()
{
    UT.result[UT.current_test_index] = true;
}

void assert_true(bool expected){
    if(expected == true){
        UT.success();
    }else{
        UT.fail();
    }
}
void assert_false(bool expected){
    if(expected == false){
        UT.success();
    }else{
        UT.fail();
    }
}

void assert_equals_int(const int expected, const int actual){
    if(expected == actual){
        UT.success();
    }else{
        UT.fail();
    }
}

void assert_equals_float(const float expected, const float actual){
    if(expected == actual){
        UT.success();
    }else{
        UT.fail();
    }
}

void assert_equals_char_array(const char* expeced, const char* actual, int size){
    for (size_t i = 0; i < size; i++)
    {
        if(expeced[i] != actual[i]){
            UT.fail();
            return;
        }
    }

    UT.success();
    /*TODO: check if works*/
}

void assert_equals_bool(const bool expected, const bool actual){
if(expected == actual){
        UT.success();
    }else{
        UT.fail();
    }
}

void assert_not_equals_int(const int expected, const int actual){
    if(expected != actual){
        UT.success();
    }else{
        UT.fail();
    }
}
void assert_not_equals_float(const float expected, const float actual){
    if(expected != actual){
        UT.success();
    }else{
        UT.fail();
    }
}
void assert_not_equals_char_array(const char* expeced, const char* actual, int size){
    int equal = 0;
    for (size_t i = 0; i < size; i++)
    {
        if(expeced[i] == actual[i]){
            equal++;
        }
    }
    if(equal == size){
        UT.fail();
    }else{
        UT.success();
    }
    
}
void assert_not_equals_bool(const bool expected, const bool actual){
    if(expected != actual){
        UT.success();
    }else{
        UT.fail();
    }
}


void assert_null(void* ptr){
    if(ptr == NULL){
        UT.success();
    }else{
        UT.fail();
    }
}
void assert_not_null(void* ptr){
    if(ptr != NULL){
        UT.success();
    }else{
        UT.fail();
    }
}
void assert_same(void* expected, void* actual){
    if(expected == actual){
        UT.success();
    }else{
        UT.fail();
    }
}
void assert_not_same(void* expected, void* actual){
    if(expected != actual){
        UT.success();
    }else{
        UT.fail();
    }
}