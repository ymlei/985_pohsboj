#pragma once
#include "DAlgorithm.h"

const unsigned long dtl::xorshiftRANDMAX = 4294967295;

unsigned long dtl::xorshiftRand()
{
	static unsigned long x = time(0);
	x ^= x >> 12; x ^= x << 25; x ^= x >> 27;
	return x * 0x2545F4914F6CDD1D;
}