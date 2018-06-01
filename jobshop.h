//1¡¢aaaa 2¡¢out time
#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "DVector.h"

//#define DEBUG

/************** global vals **************/
const double CROSSOVER_RATE = 1;
const double MUTATION_RATE = 1;
const double MUTATION_RATE_BAD = 1;
const int POPULATION_SIZE = 50;
const int ITERATION_COUNT = 1000;
const int POP_NUM = 5;
const int COMMUNACATION_CYCLE = 100;

/**************** typedef ****************/
typedef int TIME;
template <typename T>
using DVector2D = DVector<DVector<T>>;

/************* class & struct ************/
typedef struct {
public:
	bool from_file;
	bool to_file;
	std::string infile_name;
	std::string outfile_name;
} LAUNCH_PARAMETRE;

typedef struct {
public:
	DVector<int> chromo;
	TIME time;
} CHROMO;

typedef struct {
public:
	int machine;
	TIME duration;
} PROCEDURE;

typedef struct {
public:
	TIME start;
	TIME end;
	unsigned int product;
	unsigned int proced;
} MACHINE_TASK;

class jsException {
private:
	std::string a;
public:
	jsException(std::string e) : a(e) {}
	~jsException() {}
	void print() { std::cout << a << std::endl; }
};
