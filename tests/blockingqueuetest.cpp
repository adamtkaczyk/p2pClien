#include "blockingqueuetest.h"

BlockingQueueTest::BlockingQueueTest()
{

}

TEST_F(BlockingQueueTest,test_push_simple)
{
    simpaleQueue_.push(1);
    EXPECT_EQ(simpaleQueue_.size(),1);
    int max = 1000;
    for(int i = 0; i < max; i++)
        simpaleQueue_.push(i);
    EXPECT_EQ(simpaleQueue_.size(), max + 1);
}

TEST_F(BlockingQueueTest,test_pop_simple)
{
    simpaleQueue_.push(1);
    auto value = simpaleQueue_.pop();
    EXPECT_EQ(value,1);
    EXPECT_EQ(simpaleQueue_.size(),0);
    int max = 1000;
    for(int i = 0; i < max; i++)
        simpaleQueue_.push(i);

    for(int i = 0; i < max; i++)
    {
        auto value = simpaleQueue_.pop();
        EXPECT_EQ(value,i);
        EXPECT_EQ(simpaleQueue_.size(),max - 1 - i);
    }
}

TEST_F(BlockingQueueTest,test_push_sptr)
{
    sptrQueue_.push(std::make_unique<int>(1));
    EXPECT_EQ(sptrQueue_.size(),1);
    int max = 1000;
    for(int i = 0; i < max; i++)
    {
        auto ptr = std::make_unique<int>(i);
        sptrQueue_.push(move(ptr));
    }
    EXPECT_EQ(sptrQueue_.size(), max + 1);
}

TEST_F(BlockingQueueTest,test_pop_sptr)
{
    sptrQueue_.push(std::make_unique<int>(1));
    auto ptr = sptrQueue_.pop();
    EXPECT_EQ(*ptr,1);
    EXPECT_EQ(sptrQueue_.size(),0);
    int max = 1000;
    for(int i = 0; i < max; i++)
    {
        auto ptr = std::make_unique<int>(i);
        sptrQueue_.push(move(ptr));
    }

    for(int i = 0; i < max; i++)
    {
        auto ptr = sptrQueue_.pop();
        EXPECT_EQ(*ptr,i);
        EXPECT_EQ(sptrQueue_.size(),max - 1 - i);
    }
}
