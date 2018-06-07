/***************************************************************/
//Name: jobshop_ga.h
//By: Liu Xiangyu & Lei Yiming
//Last Modified: 2018/5/28
/***************************************************************/

#pragma once
#include "jobshop.h"

/**********module global vals ***********/
extern int product_count;
extern int proced_count;
extern int chromo_len;
extern int machine_count;

/**********public funcs***********/
CHROMO jobshop_GA(const DVector2D<PROCEDURE>& jobtable);

void init_population(DVector<CHROMO>& population, const DVector2D<PROCEDURE>& jobtable);
void communication(DVector<CHROMO>* pop);
void print_chormo(DVector<CHROMO>& pop);

void crossover(const DVector2D<PROCEDURE>& jobtable, DVector<CHROMO>& population);

void selfing(const DVector2D<PROCEDURE>& jobtable, DVector<CHROMO>& population);
void selfing_doubleseg(const DVector2D<PROCEDURE>& jobtable, DVector<CHROMO>& population);
void selfing_multi(const DVector2D<PROCEDURE>& jobtable, DVector<CHROMO>& population);
void selfing_multi_pickbysort(const DVector2D<PROCEDURE>& jobtable, DVector<CHROMO>& population);

void filter(DVector<CHROMO>& population);
void filter_by_sort(DVector<CHROMO>& population);
void filter_roulette(DVector<CHROMO>& population);
void filter_tournament(DVector<CHROMO>& population);

void mutate(DVector<CHROMO>& population);
void mutate_all(const DVector2D<PROCEDURE>& jobtable, DVector<CHROMO>& population);
void mutate_six(const DVector2D<PROCEDURE>& jobtable, DVector<CHROMO>& population);

/**********private funcs**********/
TIME chromo_time(const DVector2D<PROCEDURE>& jobtable, const DVector<int>& chromo, int flag);
DVector2D<MACHINE_TASK> get_result_table(const DVector2D<PROCEDURE>& jobtable, const CHROMO& CHROMO);
void print_result_table(const DVector2D<MACHINE_TASK>& result_table);
// QSort
int partition(DVector<CHROMO>& population, int lo, int hi);
void qsort(DVector<CHROMO>& population, int lo, int hi);
