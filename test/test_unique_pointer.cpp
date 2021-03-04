/*
MIT License

Copyright (c) 2021 SAE Institute Geneva

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gtest/gtest.h>
#include "maths/unique_pointer.h"
namespace maths {
	
TEST(Maths, Unique_Pointer_Constructors) {

	//test default constructor
	UniquePointer<int> a;
	int* b = nullptr;
	EXPECT_EQ(a.pointer(), b);

	//test move constructor
	UniquePointer<int> e = MakeUnique<int>(2);
	UniquePointer<int> c (std::move(e));	
	EXPECT_EQ(*c, 2);

	//test nullptr constructor
	UniquePointer<int> f (nullptr);
	int* g = nullptr;
	EXPECT_EQ(f.pointer(), g);
}
TEST(Maths, Pointer_Assignments) {

	UniquePointer<int> a = MakeUnique<int>(2);
	UniquePointer<int> b = std::move(a);

	//test move assignment
	EXPECT_EQ(*b, 2);

	//test nullptr assignment
	b = nullptr;
	int* c = nullptr;
	EXPECT_EQ(b.pointer(), c);
}
TEST(Maths, Make_Unique) {

	UniquePointer<int> a = MakeUnique<int>(2);

	//test MakeUnique
	EXPECT_EQ(*a, 2);
}
	
}//namespace maths