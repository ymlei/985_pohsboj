/***************************************************************/
//Name: DVector.h
//By: Zhang Kaishun
//Last Modified: 2018/5/28
//Known Issues:
//	  1. exception chaos
/***************************************************************/

#pragma once
#include <cstdlib>
#include <memory.h>
#include <string>
#include "DTLHead.h"
#include "DAlgorithm.h"

#include <iostream>

// Iterator: TODO
template <typename T> class DVector {
protected:
	/****** data members ******/
	_SIZE __size;
	_SIZE __capacity;
	T* __data;
	bool RESERVED;
	/****** func members ******/
	inline void realloc();
	void copy(const DVector<T>& SourceDVector, _SIZE lopos, _SIZE hipos);
	//  protected
public:
	/****** constructors ******/
	// Too lazy. Do not support std::vector & array
	DVector();
	DVector(_SIZE Size);
	DVector(_SIZE Size, const T& InitValue);
	DVector(const DVector<T>& SourceDVector);
	DVector(const DVector<T>& SourceDVector, _SIZE Begin, _SIZE End);
	/****** destructor ******/
	~DVector();
	/*** common operators ***/
	DVector<T>& operator= (const DVector<T>& T2);
	/******* R, CONST *******/
	bool empty() const;
	_SIZE size() const;
	int inOrder() const; // -1(downOrder), 1(upOrder), 0(disorder)
	_SIZE searchFirst(const T& target) const;
	_SIZE searchFirst(const T& target, _SIZE Begin, _SIZE End) const;
	_SIZE searchLast(const T& target) const;
	_SIZE searchLast(const T& target, _SIZE Begin, _SIZE End) const;
	/******* capacity & size *******/
	void reserve(_SIZE toSize);
	void shrinkToFit();
	void resize(_SIZE toSize);
	void resize(_SIZE toSize, const T& ValFilled);
	/****** data access ******/
	inline T& operator[] (_SIZE position) const;
	inline T& front() const;
	inline T& back() const;
	inline void push_back(const T& data);
	inline void pop_back();
	void insert(_SIZE InsertPos, const T& data);
	void erase(_SIZE ErasePos);
	void erase(_SIZE Begin, _SIZE End);
	void swap(_SIZE Pos1, _SIZE Pos2);
	DVector<T> shuffle();
	DVector<T> shuffle(_SIZE Begin, _SIZE End);
	void sort(_SIZE lopos, _SIZE hipos, int posForAscend_negForDescend = 1);
	_SIZE getmax(_SIZE lopos, _SIZE hipos);
	_SIZE getmin(_SIZE lopos, _SIZE hipos);
	void clear();
}; // DVector template

   /********************** defination ***********************/

   /********************** protected **********************/
template <typename T>
void DVector<T>::realloc()
{
	_SIZE ncap = -1;
	if (__size >= __capacity - 1) { // full
		ncap = RESERVE_INDEX * __size;
		RESERVED = false;
	}
	else if (!RESERVED && DEFAULTSIZE < __size && __size < __capacity * SHRINK_TRIGGER) // spare
		ncap = __capacity * SHIRNK_INDEX;
	else if (!RESERVED && __capacity < DEFAULTSIZE) // capa too small
		ncap = RESERVE_INDEX * DEFAULTSIZE;
	else if (__data == nullptr)
		ncap = __capacity;
	else return;

	T* ndat = new T[ncap];
	//std::cout << "//new_realloc// = " << ncap << '\n';

	if (__data != nullptr) {
		for (_SIZE i = 0; i < __size; ++i) {
			ndat[i] = __data[i];
		}
		//std::cout << "//delete_realloc//\n";
		delete[] __data;
	}
	__capacity = ncap;
	__data = ndat;
} // realloc

template <typename T>
void DVector<T>::copy(const DVector<T>& src, _SIZE lo, _SIZE hi)
{
	if (lo > hi) {
		std::cout << "lo,hi = " << lo << ' ' << hi << '\n'; throw UNDEFINED_BORDER;
	}
	__size = hi - lo;
	__capacity = DEFAULTSIZE;
	if (__data != nullptr) {
		delete[] __data;
		__data = nullptr;
	}
	realloc();
	for (_SIZE i = lo; i < hi; ++i)
		__data[i - lo] = src.__data[i];
} // copy

  /********************** public **********************/

  /************* constructors **************/
template <typename T>
DVector<T>::DVector()
{
	__size = 0;
	__capacity = DEFAULTSIZE;
	__data = new T[__capacity];
	RESERVED = false;
} // DVector()

template <typename T>
DVector<T>::DVector(_SIZE recsize)
{
	__size = recsize;
	if (__size < DEFAULTSIZE) __capacity = DEFAULTSIZE;
	else __capacity = RESERVE_INDEX * __size;
	RESERVED = false;
	__data = new T[__capacity];
} // DVector()

template <typename T>
DVector<T>::DVector(_SIZE recsize, const T& initv)
{
	__size = recsize;
	if (__size < DEFAULTSIZE) __capacity = DEFAULTSIZE;
	else __capacity = RESERVE_INDEX * __size;
	RESERVED = false;
	__data = new T[__capacity];
	for (_SIZE i = 0; i < __size; ++i)
		__data[i] = initv;
} // DVector()

template <typename T>
DVector<T>::DVector(const DVector<T>& srcdvec)
{
	if (srcdvec.size() == 0) {
		__size = 0;
		__capacity = DEFAULTSIZE;
		__data = new T[__capacity];
		RESERVED = false;
	}
	else {
		__size = 0;
		__capacity = DEFAULTSIZE;
		__data = nullptr;
		copy(srcdvec, 0, srcdvec.size());
		RESERVED = false;
	}
} // DVector()

template <typename T>
DVector<T>::DVector(const DVector<T>& srcdvec, _SIZE beg, _SIZE end)
{
	if (srcdvec.size() == 0) {
		__size = 0;
		__capacity = DEFAULTSIZE;
		__data = new T[__capacity];
		RESERVED = false;
	}
	else {
		__size = 0;
		__capacity = DEFAULTSIZE;
		__data = nullptr;
		copy(srcdvec, beg, end);
		RESERVED = false;
	}
} // DVector()

  /************* destructor **************/
template <typename T>
DVector<T>::~DVector()
{
	delete[] __data;
	////std::cout << "//delete//\n";
} // ~DVector()

  /********** common operators **********/
template <typename T>
DVector<T>& DVector<T>::operator= (const DVector<T>& srcdvec)
{
	copy(srcdvec, 0, srcdvec.size());
	RESERVED = false;
	return *this;
} // operator=

  /************* R, CONST **************/
template <typename T>
bool DVector<T>::empty() const
{
	return __size == 0;
} // empty

template <typename T>
_SIZE DVector<T>::size() const
{
	return __size;
} // size

template <typename T>
int DVector<T>::inOrder() const
{
	if (__size == 1) return 1;
	int flag = __data[0] < __data[1] ? 1 : -1;
	for (_SIZE i = 0; i < __size - 1; ++i) {
		if (flag == 1 && __data[i] > __data[i + 1]) return 0;
		if (flag == -1 && __data[i] < __data[i + 1]) return 0;
	} return flag;
} // inOrder

template <typename T>
_SIZE DVector<T>::searchFirst(const T& t) const
{
	return DVector<T>::searchFirst(t, 0, __size - 1);
} // searchFirst

template <typename T>
_SIZE DVector<T>::searchFirst(const T& t, _SIZE beg, _SIZE end) const
{
	T temp = __data[end - 1];
	__data[end - 1] = t;
	_SIZE i = beg; while (__data[i] != t) ++i;
	__data[end - 1] = temp;
	return (i == end - 1 && temp != t) ? -1 : i;
} // searchFirst

template <typename T>
_SIZE DVector<T>::searchLast(const T& t) const
{
	return DVector<T>::searchLast(t, 0, __size);
} // searchLast

template <typename T>
_SIZE DVector<T>::searchLast(const T& t, _SIZE beg, _SIZE end) const
{
	T temp = __data[beg];
	__data[beg] = t;
	_SIZE i = end - 1; while (__data[i] != t) --i;
	__data[beg] = temp;
	return (i == beg && temp != t) ? -1 : i;
} // searchLast

  /********** capacity & size ***********/
template <typename T>
void DVector<T>::reserve(_SIZE toSize)
{
	T* ndat = new T[toSize];
	//std::cout << "//new_reserve// = " << toSize << '\n';
	_SIZE tsize = __size < toSize ? __size : toSize;
	for (_SIZE i = 0; i < tsize; ++i)
		ndat[i] = __data[i];
	delete[] __data;
	//std::cout << "//delete//\n";
	__data = ndat;
	__capacity = toSize;
	RESERVED = true;
} // reserve

template <typename T>
void DVector<T>::shrinkToFit()
{
	DVector<T>::reserve(__size);
	RESERVED = false;
} // shrinkToFit

template <typename T>
void DVector<T>::resize(_SIZE toSize)
{
	if (toSize < __size) __size = toSize;
	else if (toSize > __size) {
		__size = toSize; realloc();
	}
} // resize

template <typename T>
void DVector<T>::resize(_SIZE toSize, const T& vf)
{
	if (toSize < __size) __size = toSize;
	else if (toSize > __size) {
		_SIZE sp = __size; __size = toSize; realloc();
		for (_SIZE i = sp; i < __size; ++i)
			__data[i] = vf;
	}
	else {
		for (int i = 0; i < __size; ++i)
			__data[i] = vf;
	}
} // resize

  /********** data access **********/

template <typename T>
T& DVector<T>::operator[] (_SIZE pos) const
{
	if (pos < 0 || pos > __size - 1) {
		std::cout << "pos,__size = " << pos << ' ' << __size << '\n';
		throw MEMOVERFLOW;
	}
	return __data[pos];
} // []

template <typename T>
T& DVector<T>::front() const
{
	if (__size == 0) throw UNDEFINED_EMPTY;
	return __data[0];
} // front

template <typename T>
T& DVector<T>::back() const
{
	if (__size == 0) throw UNDEFINED_EMPTY;
	return __data[__size - 1];
} // back

template <typename T>
void DVector<T>::push_back(const T& nd)
{
	++__size;
	realloc();
	__data[__size - 1] = nd;
} // push_back

template <typename T>
void DVector<T>::pop_back()
{
	if (__size == 0) throw UNDEFINED_EMPTY;
	--__size;
	realloc();
} // pop_back

template <typename T>
void DVector<T>::insert(_SIZE inspos, const T& nd)
{
	if (inspos < 0 || __size - 1 < inspos) throw MEMOVERFLOW;
	++__size;
	realloc();
	for (_SIZE i = __size - 1; i > inspos; --i)
		__data[i] = __data[i - 1];
	__data[inspos] = nd;
} // insert

template <typename T>
void DVector<T>::erase(_SIZE erapos)
{
	if (erapos < 0 || __size - 1 < erapos) throw MEMOVERFLOW;
	for (_SIZE i = erapos; i < __size - 1; ++i)
		__data[i] = __data[i + 1];
	--__size;
	realloc();
} // erase

template <typename T>
void DVector<T>::erase(_SIZE beg, _SIZE end)
{
	if (beg > end) throw UNDEFINED_ERASE;
	if (!(0 <= beg && end <= __size)) throw MEMOVERFLOW;
	for (_SIZE i = end; i < __size; ++i)
		__data[beg + i - end] = __data[i];
	__size -= end - beg;
	realloc();
} // erase

template <typename T>
void DVector<T>::swap(_SIZE p1, _SIZE p2)
{
	T tem;
	if (p1 < 0 || __size - 1 < p1 || p2 < 0 || __size - 1 < p2) throw MEMOVERFLOW;
	tem = __data[p2]; __data[p2] = __data[p1]; __data[p1] = tem;
} // swap

template <typename T>
DVector<T> DVector<T>::shuffle()
{
	DVector<T> a(*this);
	for (_SIZE i = 0; i < __size - 1; ++i) {
		a.swap(i, i + dtl::xorshiftRand() % (__size - 1 - i) + 1);
	}
	return a;
} // shuffle

template <typename T>
DVector<T> DVector<T>::shuffle(_SIZE beg, _SIZE end)
{
	DVector<T> a(*this, beg, end);
	for (_SIZE i = beg; i < end - 1; ++i) {
		a.swap(i, i + dtl::dtl::xorshiftRand() % (end - 1 - i) + 1);
	}
	return a;
} // shuffle

template <typename T>
void DVector<T>::sort(_SIZE lo, _SIZE hi, int flag)
{
	// TODO
} // sort

template <typename T>
_SIZE DVector<T>::getmax(_SIZE lo, _SIZE hi)
{
	_SIZE maxPos = lo;
	T maxData = __data[lo];
	for (_SIZE i = lo + 1; i < hi; ++i) {
		if (__data[i] > maxData) {
			maxData = __data[i];
			maxPos = i;
		}
	}
	return maxPos;
} // getMaxData

template <typename T>
_SIZE DVector<T>::getmin(_SIZE lo, _SIZE hi)
{
	_SIZE minPos = lo;
	T minData = __data[lo];
	for (_SIZE i = lo + 1; i < hi; ++i) {
		if (__data[i] < minData) {
			minData = __data[i];
			minPos = i;
		}
	}
	return minPos;
} // getMinData

template <typename T>
void DVector<T>::clear()
{
	__size = 0;
	realloc();
	RESERVED = false;
} // swap
