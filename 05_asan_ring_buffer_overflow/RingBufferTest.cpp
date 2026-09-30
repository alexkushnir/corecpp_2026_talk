// ASan demo: an off-by-one in the ring buffer's wrap-around check writes
// one int past the end of a 100-byte (25-int) buffer. The test passes;
// ASan reports heap-buffer-overflow with shadow byte [04].
#include <gtest/gtest.h>
#include "Producer.h"

TEST(RingBuffer, ProducerFillsBuffer) {
  RingBuffer ring(25);           // 25 ints = 100 bytes
  Producer producer(ring);
  producer.Run(30);              // wraps around once
  EXPECT_EQ(ring.Pushed(), 30u);
}