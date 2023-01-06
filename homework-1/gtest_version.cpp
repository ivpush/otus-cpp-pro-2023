// Google test for version

#include "lib.h"

#include <gtest/gtest.h>

TEST(Version, GreaterNull)
{
    ASSERT_TRUE(version() > 0);
}

