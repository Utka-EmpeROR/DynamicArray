#include "pch.h"
#include "../DynamicArrayLibrary/Array.h"

TEST(Constructor)
{
    Array<int> arr;

    ASSERT_EQ(arr.size(), 0);
}

TEST(Constructor_with_param)
{
    Array<int> arr(5);

    ASSERT_EQ(arr.size(), 0);
}

TEST(Insert)
{
    Array<int> arr;

    arr.insert(10);

    ASSERT_EQ(arr.size(), 1);

    ASSERT_EQ(arr[0], 10);
}

TEST(Insert_with_index)
{
    Array<int> arr;

    arr.insert(10);
    arr.insert(20);
    arr.insert(1, 15);

    ASSERT_EQ(arr.size(), 3);

    ASSERT_EQ(arr[0], 10);
    ASSERT_EQ(arr[1], 15);
    ASSERT_EQ(arr[2], 20);
}

TEST(Remove)
{
    Array<int> arr;

    arr.insert(10);
    arr.insert(20);
    arr.insert(30);

    arr.remove(1);  //

    ASSERT_EQ(arr.size(), 2);

    ASSERT_EQ(arr[0], 10);
    ASSERT_EQ(arr[1], 30);
}

TEST(Copy_constructor)
{
    Array<int> arr;

    arr.insert(10);
    arr.insert(20);

    Array<int> arrCopy(arr);

    ASSERT_EQ(arrCopy.size(), 2);

    ASSERT_EQ(arrCopy[0], 10);
    ASSERT_EQ(arrCopy[1], 20);
}

TEST(Copy_assignment_operator)
{
    Array<int> arr;

    arr.insert(10);
    arr.insert(20);

    Array<int> arrCopy;
    arrCopy = arr;

    ASSERT_EQ(arrCopy.size(), 2);

    ASSERT_EQ(arrCopy[0], 10);
    ASSERT_EQ(arrCopy[1], 20);
}

TEST(Iterators)
{
    Array<int> arr;

    arr.insert(10);
    arr.insert(20);
    arr.insert(30);

    auto it = arr.iterator();

    ASSERT_TRUE(it.hasNext());

    ASSERT_EQ(it.get(), 10);

    it.next();
    ASSERT_EQ(it.get(), 20);

    it.next();
    ASSERT_EQ(it.get(), 30);

    it.next();
    ASSERT_FALSE(it.hasNext());
}

TEST(Reverse_iterators)
{
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.insert(30);

    auto rit = arr.reverseIterator();

    ASSERT_TRUE(rit.hasNext());
    ASSERT_EQ(rit.get(), 30);

    rit.next();
    ASSERT_EQ(rit.get(), 20);

    rit.next();
    ASSERT_EQ(rit.get(), 10);

    rit.next();
    ASSERT_FALSE(rit.hasNext());
}

TEST(String_Constructor)
{
    Array<std::string> arr;

    ASSERT_EQ(arr.size(), 0);
}

TEST(String_Constructor_with_param)
{
    Array<std::string> arr(5);

    ASSERT_EQ(arr.size(), 0);
}

TEST(String_Insert)
{
    Array<std::string> arr;

    arr.insert("Aa");

    ASSERT_EQ(arr.size(), 1);

    ASSERT_EQ(arr[0], "Aa");
}

TEST(String_Insert_with_index)
{
    Array<std::string> arr;

    arr.insert("Aa");
    arr.insert("Cc");
    arr.insert(1, "Bb");

    ASSERT_EQ(arr.size(), 3);

    ASSERT_EQ(arr[0], "Aa");
    ASSERT_EQ(arr[1], "Bb");
    ASSERT_EQ(arr[2], "Cc");
}

TEST(String_Remove)
{
    Array<std::string> arr;

    arr.insert("Aa");
    arr.insert("Bb");
    arr.insert("Cc");

    arr.remove(1);

    ASSERT_EQ(arr.size(), 2);

    ASSERT_EQ(arr[0], "Aa");
    ASSERT_EQ(arr[1], "Cc");
}

TEST(String_Copy_constructor)
{
    Array<std::string> arr;

    arr.insert("Aa");
    arr.insert("Bb");

    Array<std::string> arrCopy(arr);

    ASSERT_EQ(arrCopy.size(), 2);

    ASSERT_EQ(arrCopy[0], "Aa");
    ASSERT_EQ(arrCopy[1], "Bb");
}

TEST(String_Copy_assignment_operator)
{
    Array<std::string> arr;

    arr.insert("Aa");
    arr.insert("Bb");

    Array<std::string> arrCopy;
    arrCopy = arr;  

    ASSERT_EQ(arrCopy.size(), 2);

    ASSERT_EQ(arrCopy[0], "Aa");
    ASSERT_EQ(arrCopy[1], "Bb");
}


TEST(String_Iterators)
{
    Array<std::string> arr;

    arr.insert("Aa");
    arr.insert("Bb");
    arr.insert("Cc");

    auto it = arr.iterator();

    ASSERT_TRUE(it.hasNext());

    ASSERT_EQ(it.get(), "Aa");

    it.next();
    ASSERT_EQ(it.get(), "Bb");

    it.next();
    ASSERT_EQ(it.get(), "Cc");

    it.next();
    ASSERT_FALSE(it.hasNext());
}

TEST(String_Reverse_iterators)
{
    Array<std::string> arr;
    arr.insert("Aa");
    arr.insert("Bb");
    arr.insert("Cc");

    auto rit = arr.reverseIterator();

    ASSERT_TRUE(rit.hasNext());
    ASSERT_EQ(rit.get(), "Cc");

    rit.next();
    ASSERT_EQ(rit.get(), "Bb");

    rit.next();
    ASSERT_EQ(rit.get(), "Aa");

    rit.next();
    ASSERT_FALSE(rit.hasNext());
}

/*
TEST(ArrayTest, InsertAndRetrieve) {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.insert(i + 1);
    }
    ASSERT_EQ(arr.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

TEST(ArrayTest, InsertAtIndex) {
    Array<int> arr;
    arr.insert(0);
    arr.insert(1);
    arr.insert(1, 42);
    ASSERT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 42);
    EXPECT_EQ(arr[2], 1);
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    for (int i = 0; i < 5; ++i) {
        arr.insert(i);
    }
    arr.remove(2);
    ASSERT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

TEST(ArrayTest, Iterator) {
    Array<int> arr;
    for (int i = 0; i < 5; ++i) {
        arr.insert(i + 1);
    }
    Array<int>::Iterator it = arr.iterator();
    int expected = 1;
    while (it.hasNext()) {
        EXPECT_EQ(it.get(), expected);
        it.next();
        ++expected;
    }
}

TEST(ArrayTest, ReverseIterator) {
    Array<int> arr;
    for (int i = 0; i < 5; ++i) {
        arr.insert(i + 1);
    }
    Array<int>::ReverseIterator it = arr.reverseIterator();
    int expected = 5;
    while (it.hasNext()) {
        EXPECT_EQ(it.get(), expected);
        it.next();
        --expected;
    }
}

TEST(ArrayTest, ResizeFunctionality) {
    Array<int> arr;
    for (int i = 0; i < 100; ++i) {
        arr.insert(i);
    }
    ASSERT_EQ(arr.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(arr[i], i);
    }
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.insert(i);
    }
    Array<int> copy = arr;
    ASSERT_EQ(copy.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(copy[i], i);
    }
}

TEST(ArrayTest, AssignmentOperator) {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.insert(i);
    }
    Array<int> assigned;
    assigned = arr;
    ASSERT_EQ(assigned.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(assigned[i], i);
    }
}
*/
