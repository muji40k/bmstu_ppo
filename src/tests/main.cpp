#include <gtest/gtest.h>
#include <vector>
#include "unit_tests_main.h"
#include "integration_tests_main.h"
#include "test_eq.hpp"

int main(int argc, char **argv)
{
    using TestFunc = void (*)(int, char**);
    const std::vector<TestFunc> funcs = {unit_tests_main,
                                         integration_tests_main};

    for (TestFunc func : funcs)
        func(argc, argv);

    return RUN_ALL_TESTS();
}

