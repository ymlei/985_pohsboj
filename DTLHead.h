/*******************************/
// Name: DTLHead.h
// Created By: DOG
// Last Modified: 2018/5/18
// The universal head of DTL.
// Including:
//     1. typedefs
//	   2. constants
//     3. memory alloc indices
//     4. exceptions
/*******************************/

#pragma once
#include <iostream>
#include <string>

typedef long long _LL;

typedef long _SIZE;
static const _SIZE DEFAULTSIZE = 1 << 9;
static const float RESERVE_INDEX = 2.0;
static const float SHRINK_TRIGGER = 1.0 / 16;
static const float SHIRNK_INDEX = 1.0 / 4;

/******** exception ********/
class DException {
private:
	std::string damn;
public:
	DException(std::string d) : damn(d) {}
	~DException() {}
	void print() { std::cout << damn << std::endl; }
};
const DException MEMOVERFLOW("MemAccessOutOfBound");
const DException UNDEFINED_EMPTY("UndefinedHandle_ContainerEmpty");
const DException UNDEFINED_ERASE("UndefinedHandle_EraseFault");
const DException UNDEFINED_BORDER("UndefinedHandle_BorderConfict");