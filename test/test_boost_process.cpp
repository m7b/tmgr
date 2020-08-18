#define BOOST_TEST_MODULE boost_process
#include <boost/test/unit_test.hpp>

// workaround for a boost bug..
#ifndef __kernel_entry
#define __kernel_entry
#endif

#include <boost/process.hpp>

BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_TEST_MESSAGE("<boost/process.hpp> is fine!");
}