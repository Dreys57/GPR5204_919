#pragma once

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
#include <iostream>
#include <type_traits>

namespace maths {

template<typename T>
class UniquePointer {

public:

//default constructor
UniquePointer() : pointer_(nullptr) {}

//constructor binding to nullptr
UniquePointer(std::nullptr_t) : pointer_(nullptr) {}

//explicit constructor
explicit UniquePointer(T* p) noexcept : pointer_(p) {}
	
//copy constructor (makes sure it cannot be copied)
UniquePointer(const UniquePointer& p) = delete;

//move constructor
UniquePointer(UniquePointer&& p) noexcept : pointer_(std::move(p.pointer())) { p.pointer_ = nullptr; }

//destructor
~UniquePointer() { delete pointer_; }

//copy assignment (makes sure it cannot be copied)
UniquePointer& operator= (const UniquePointer& p) = delete;
	
//move assignment
UniquePointer& operator= (UniquePointer&& p) noexcept {

	std::swap(pointer_, p);
	return *this;
}

//nullptr assignment
UniquePointer& operator= (std::nullptr_t) {

	Reset();
	return *this;
}

T* operator ->() const { return pointer_; }

T& operator *() const { return *pointer_; }

T* pointer() const noexcept { return pointer_; }

//This function swaps the pointer with a temporary pointer (nullptr)
// and returns the temporary pointer.
T* Release() noexcept {

	T* tmp = nullptr;
	std::swap(tmp, pointer_);
	return tmp;
}

//This function calls Release to change the pointer to nullptr
//and then deletes the temporary pointer.
void Reset() {

	T* tmp = Release();
	delete tmp;
}

private:

T* pointer_;

};

template<class T, class...Args>
std::enable_if_t<!std::is_array<T>::value, UniquePointer<T>>
MakeUnique(Args&&...args) {
	return UniquePointer<T>(new T(std::forward<Args>(args)...));
}
	
}//namespace maths
