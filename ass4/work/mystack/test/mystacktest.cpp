#include "ass4/work/mystack/product/mystack.h"
#include "gtest/gtest.h"
/*
using ::testing::_;
using ::testing::Return;
*/
class mystackTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};

TEST_F(mystackTest, create_stack)
{
    Fontys::stackMeta<int> stack;
    EXPECT_EQ(0, stack.nofelem());
}
