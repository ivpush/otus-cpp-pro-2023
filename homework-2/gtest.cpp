// Google test for Helper functions

#include <string>
#include <cstdlib>

#include "lib.h"

#include <gtest/gtest.h>

// 1. inet_pton4 
TEST(Helpers, inet_pton4)
{
    // Arrange - try correct ipv4 address
    std::string line {"127.0.0.1"};
    uint32_t    addr;
    bool        res;

    // convert correct ipv4 address
    res = inet_pton4 (line, addr);

    ASSERT_TRUE(res == true);
    ASSERT_EQ(addr, 0x7f000001);

    // try incorrect addr - wrong char
    line = "192.bb.0.1";

    res = inet_pton4 (line, addr);

    ASSERT_TRUE(res == false);

    // try incorrect addr - wrong octet
    line = "192.328.0.1";

    res = inet_pton4 (line, addr);

    ASSERT_TRUE(res == false);
}

// 2. filter
TEST(Helpers, Filter)
{
    uint32_t    addr = 0xC0A80A07;  // 192.168.10.7
    bool res;

    ASSERT_TRUE (filter (addr, 192));
    ASSERT_FALSE(filter (addr, 127));

    ASSERT_TRUE (filter (addr, 192, 168));

    ASSERT_FALSE(filter (addr, 192, 167));
    ASSERT_FALSE(filter (addr, 127, 168));
    ASSERT_FALSE(filter (addr, 190, 160));

    ASSERT_TRUE (filter (addr, 192, 168, 10));

    ASSERT_FALSE(filter (addr, 192, 168,  7));
    ASSERT_FALSE(filter (addr, 127, 168, 10));
    ASSERT_FALSE(filter (addr, 190, 160,  3));

    ASSERT_TRUE (filter_any (addr, 192));
    ASSERT_TRUE (filter_any (addr, 168));
    ASSERT_TRUE (filter_any (addr,  10));
    ASSERT_TRUE (filter_any (addr,   7));

    ASSERT_FALSE(filter_any (addr, 127));
    ASSERT_FALSE(filter_any (addr,  76));
}
