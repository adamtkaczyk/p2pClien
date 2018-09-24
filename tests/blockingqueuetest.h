#ifndef BLOCKINGQUEUETEST_H
#define BLOCKINGQUEUETEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "datastruct/blockingqueue.h"

class BlockingQueueTest : public ::testing::Test
{
public:
    BlockingQueueTest();
    BlockingQueue<int> simpaleQueue_;
    BlockingQueue<std::unique_ptr<int>> sptrQueue_;
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

#endif // BLOCKINGQUEUETEST_H
