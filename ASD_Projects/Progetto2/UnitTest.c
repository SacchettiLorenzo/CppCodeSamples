#include "UnitTest.h"

void fail()
{
    //UT.result[UT.current_test_index] = false;
    //UT.current_test_index++;
    printf("\033[0;31m FAILED \033[0m\n" );
}
void success()
{
    //UT.result[UT.current_test_index] = true;
    //UT.current_test_index++;
    printf("\033[0;32m PASSED \033[0m\n");
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
    for (int i = 0; i < size; i++)
    {
        if(expeced[i] != actual[i]){
            UT.fail();
            return;
        }
    }

    UT.success();
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
    for (int i = 0; i < size; i++)
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
