#ifndef ENVIRONMENTTESTS_H
#define ENVIRONMENTTESTS_H

#include "Interpreter/Environment.h"
#include "TestUtil.h"


void environment_set_int (Environment* environment, const char* symbol, int value);
void environment_check_int (Environment* environment, const char* symbol, int value);


void test_environment_overwrite ()
{
    start_test("Environment - Overwrite");
    Environment* environment = environment_create(NULL);

    environment_set_int(environment, "x", 123);
    environment_check_int(environment, "x", 123);
    environment_set_int(environment, "x", 456);
    environment_check_int(environment, "x", 456);

    environment_release(environment);
}


void test_environment_shadow ()
{
    start_test("Environment - Shadow");
    Environment* environment1 = environment_create(NULL);
    Environment* environment2 = environment_create(environment1);

    environment_set_int(environment1, "x", 123);
    environment_check_int(environment1, "x", 123);
    environment_check_int(environment2, "x", 123);
    environment_set_int(environment2, "x", 456);
    environment_check_int(environment1, "x", 123);
    environment_check_int(environment2, "x", 456);

    environment_release(environment1);
    environment_release(environment2);
}


void test_environment_missing ()
{
    start_test("Environment - Missing");
    Environment* environment = environment_create(NULL);

    assert(environment_get(environment, "x") == NULL);

    environment_release(environment);
}


void test_environment ()
{
    test_environment_overwrite();
    test_environment_shadow();
    test_environment_missing();
}


void environment_set_int (Environment* environment, const char* symbol, int intVal)
{
    Value* value = value_create(INTEGER_VALUE);
    value->intVal = intVal;
    environment_set(environment, symbol, value);
    value_release(value);
}


void environment_check_int (Environment* environment, const char* symbol, int intVal)
{
    Value* value = environment_get(environment,symbol);
    assert(value->type == INTEGER_VALUE);
    assert(value->intVal == intVal);
}


#endif