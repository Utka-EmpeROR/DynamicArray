#include "pch.h"
#include "../DynamicArrayLibrary/Array.h"

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
