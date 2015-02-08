#include "MyProject.h"
#include "MCircularBufferTest.h"

//#include <iostream>

MCircularBufferTest::MCircularBufferTest()
	: m_circularBuffer(4)
{

}

MCircularBufferTest::~MCircularBufferTest()
{

}

void MCircularBufferTest::SetUpTestCase()
{
	//std::cout << "gtest MCircularBufferTest static SetUpTestCase execute" << std::endl;
	GLog->Logf(TEXT("gtest MCircularBufferTest static SetUpTestCase execute"));
}

void MCircularBufferTest::TearDownTestCase()
{
	//std::cout << "gtest MCircularBufferTest static TearDownTestCase execute" << std::endl;
	GLog->Logf(TEXT("gtest MCircularBufferTest static TearDownTestCase execute"));
}

void MCircularBufferTest::SetUp()
{
	//std::cout << "gtest MCircularBufferTest SetUp execute" << std::endl;
	GLog->Logf(TEXT("gtest MCircularBufferTest SetUp execute"));
}

void MCircularBufferTest::TearDown()
{
	//std::cout << "gtest MCircularBufferTest TearDown execute" << std::endl;
	GLog->Logf(TEXT("gtest MCircularBufferTest TearDown execute"));
}


TEST_F(MCircularBufferTest, size)
{
	EXPECT_TRUE(m_circularBuffer.size() == 0);
}

//TEST_F(MCircularBufferTest, PushOne)
//{
//	EXPECT_TRUE(c_buffer.push('a') == true);
//	EXPECT_TRUE(c_buffer.count() == 1);
//}
//
//TEST_F(MCircularBufferTest, PushOnFull)
//{
//	for (int i = 0; i < 128; ++i) {
//		static_cast<void>(c_buffer.push('a'));
//	}
//	EXPECT_TRUE(c_buffer.push('a') == false);
//	EXPECT_TRUE(c_buffer.count() == 128);
//}
//
//TEST_F(MCircularBufferTest, PopEmpty)
//{
//	c_buffer.pop();
//	EXPECT_TRUE(c_buffer.count() == 0);
//}
//
//TEST_F(MCircularBufferTest, PopOne)
//{
//	c_buffer.push('a');
//	c_buffer.push('b');
//	c_buffer.pop();
//	EXPECT_TRUE(c_buffer.count() == 1);
//}
//
//TEST_F(MCircularBufferTest, PushOneFront)
//{
//	c_buffer.push('a');
//	EXPECT_TRUE(c_buffer.front() == 'a');
//	EXPECT_TRUE(c_buffer.count() == 1);
//}
//
//TEST_F(MCircularBufferTest, PushSequentialFront)
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
