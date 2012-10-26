#ifndef ENVIRONMENTTESTS_H
#define ENVIRONMENTTESTS_H

#include "Interpreter/Environment.h"
#include "TestUtil.h"


void test_environment_overwrite ()
{
    start_test("Environment - Overwrite");
    Environment* environment = environment_create(NULL);
    Value* value;

    value = value_create(FLOAT_VALUE);
    value->floatVal = 1.23;
    environment_set(environment, "x", value);
    value_release(value);

    value = value_create(INTEGER_VALUE);
    value->intVal = 456;
    environment_set(environment, "x", value);
    value_release(value);

    value = environment_get(environment, "x");
    assert(value->intVal == 456);

    environment_release(environment);
}


void test_environment_shadow ()
{
    start_test("Environment - Shadow");
    Environment* environment1 = environment_create(NULL);
    Environment* environment2 = environment_create(environment1);
    Value* value;

    // Set and check original value
    value = value_create(INTEGER_VALUE);
    value->intVal = 314;
    environment_set(environment1, "x", value);
    value_release(value);

    // Check original value
    value = environment_get(environment2, "x");
    assert(value->intVal == 314);

    /// Set shadowed value
    value = value_create(INTEGER_VALUE);
    value->intVal = 789;
    environment_set(environment2, "x", value);
    value_release(value);

    // Check shadowed value
    value = environment_get(environment2, "x");
    assert(value->intVal == 789);

    environment_release(environment1);
    environment_release(environment2);
}


void test_environment ()
{
    test_environment_overwrite();
    test_environment_shadow();
}


#endif