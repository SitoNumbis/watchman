/* Copyright 2017-present Facebook, Inc.
 * Licensed under the Apache License, Version 2.0 */

#include <folly/portability/GTest.h>

#include "watchman/RingBuffer.h"

using namespace watchman;
using namespace ::testing;

TEST(RingBufferTest, writes_can_be_read) {
  RingBuffer<int> rb{2};
  rb.write(10);
  rb.write(11);
  auto result = rb.readAll();
  EXPECT_EQ(2, result.size());
  EXPECT_EQ(10, result[0]);
  EXPECT_EQ(11, result[1]);

  rb.write(12);
  result = rb.readAll();
  EXPECT_EQ(11, result[0]);
  EXPECT_EQ(12, result[1]);
}

TEST(RingBufferTest, writes_can_be_cleared) {
  RingBuffer<int> rb{10};
  rb.write(3);
  rb.write(4);
  auto result = rb.readAll();
  EXPECT_EQ(2, result.size());
  EXPECT_EQ(3, result[0]);
  EXPECT_EQ(4, result[1]);
  rb.clear();
  rb.write(5);
  result = rb.readAll();
  EXPECT_EQ(1, result.size());
  EXPECT_EQ(5, result[0]);
}