#include <gtest/gtest.h>
#include "online_mode.h"

TEST(test_online_mode, check)
{
    OnlineMode online_mode("/home/acer/NSU_OOP_CXX/Task2/Life/lib/mode/online_mode/examples/blinker.life");
    online_mode.Launch();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}