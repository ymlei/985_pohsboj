#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include "jobshop.h"

LAUNCH_PARAMETRE
read_parametres_under_cmd(int argc, char* argv[]);

void
read_under_cmd(DVector2D<PROCEDURE>& table, bool from_file, std::string infile_name);

void
print_under_cmd(const DVector2D<MACHINE_TASK>& res_table, bool to_file, std::string outfile_name, const DVector<int>& best, double time, const DVector2D<PROCEDURE>& jobtable);
