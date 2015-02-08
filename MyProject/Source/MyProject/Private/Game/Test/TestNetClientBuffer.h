#ifndef __CIRCULARBUFFERTEST_H
#define __CIRCULARBUFFERTEST_H

#include "MCircularBuffer.h"
//#include "gtest/gtest.h"
//
//class CircularBufferTest : public testing::Test
//{
//protected:
//	virtual void SetUp() 
//	{
//		// None yet
//	}
//	virtual void TearDown() 
//	{
//		// None yet
//	}
//	CircularBuffer<unsigned char, 128> c_buffer;
//};
//
//TEST_F(CircularBufferTest, InitialValueSize)
//{
//	EXPECT_TRUE(c_buffer.count() == 0);
//}
//
//TEST_F(CircularBufferTest, PushOne)
//{
//	EXPECT_TRUE(c_buffer.push('a') == true);
//	EXPECT_TRUE(c_buffer.count() == 1);
//}
//
//TEST_F(CircularBufferTest, PushOnFull)
//{
//	for (int i = 0; i < 128; ++i) {
//		static_cast<void>(c_buffer.push('a'));
//	}
//	EXPECT_TRUE(c_buffer.push('a') == false);
//	EXPECT_TRUE(c_buffer.count() == 128);
//}
//
//TEST_F(CircularBufferTest, PopEmpty)
//{
//	c_buffer.pop();
//	EXPECT_TRUE(c_buffer.count() == 0);
//}
//
//TEST_F(CircularBufferTest, PopOne)
//{
//	c_buffer.push('a');
//	c_buffer.push('b');
//	c_buffer.pop();
//	EXPECT_TRUE(c_buffer.count() == 1);
//}
//
//TEST_F(CircularBufferTest, PushOneFront)
//{
//	c_buffer.push('a');
//	EXPECT_TRUE(c_buffer.front() == 'a');
//	EXPECT_TRUE(c_buffer.count() == 1);
//}
//
//TEST_F(CircularBufferTest, PushSequentialFront)
//{
//	c_buffer.push('a');
//	c_buffer.push('b');
//	c_buffer.push('c');
//	EXPECT_TRUE(c_buffer.front() == 'a');
//	c_buffer.pop();
//	EXPECT_TRUE(c_buffer.front() == 'b');
//	c_buffer.pop();
//	EXPECT_TRUE(c_buffer.front() == 'c');
//	c_buffer.pop();
//	EXPECT_TRUE(c_buffer.count() == 0);
//}
//
//int main(int argc, char *argv[])
//{
//	testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}

#endif				// __CIRCULARBUFFERTEST_H