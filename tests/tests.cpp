#define BOOST_TEST_DYNAMIC_LINK
#define BOOST_TEST_MODULE Main

// Here we test all the uses and misuses of the program. These mostly have to
// with calling the program, passing arguments, reading from and writing to
// files, and error handling.

#include "testutils.hpp"
#include "../src/MAIN.hpp"
#include <boost/test/unit_test.hpp>

// Test that the simulation runs
BOOST_AUTO_TEST_CASE(useCase) {

    // Check that the program runs
    BOOST_CHECK_NO_THROW(doMain());

}