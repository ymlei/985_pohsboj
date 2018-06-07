/***************************************************************/
//Name: jobshop_io.cpp
//By: Zhang Kaishun
//Last Modified: 2018/5/25
/***************************************************************/

#include "jobshop_io.h"
#include "jobshop_ga.h"

LAUNCH_PARAMETRE read_parametres_under_cmd(int argc, char* argv[])
{
	// XXX.exe -f %filename% -o %file%
	bool from_file = false;
	bool to_file = false;
	std::string infile_name("");
	std::string outfile_name("");

	int f_pos = -1;
	int o_pos = -1;
	std::string parametre_state("");
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-f") == 0) {
			f_pos = i + 1;
			from_file = true;
		}
		else if (strcmp(argv[i], "-o") == 0) {
			o_pos = i + 1;
			to_file = true;
		}
		else if (from_file && f_pos != -1) {
			infile_name.assign(argv[f_pos]);
			f_pos = -1;
		}
		else if (to_file && o_pos != -1) {
			outfile_name.assign(argv[o_pos]);
			o_pos = -1;
		}
	}
	if ((from_file && infile_name == "") || (to_file && outfile_name == "")) {
		throw jsException("ERROR: Parametres Missing Filename");
	}
	return { from_file, to_file, infile_name, outfile_name };
} // LAUNCH_PARAMETRE read_parametres_under_cmd(...)


void read_under_cmd(DVector2D<PROCEDURE>& table, bool from_file, std::string infile_name)
{
	/******************** FILE ********************/
	std::ifstream fin;
	if (!from_file) std::cout << "Please input the data:" << std::endl;
	else {
		fin.open(infile_name, std::ios_base::in);
		if (!fin.is_open()) {
			std::cout << "name: " << infile_name << '\n';
			throw jsException("ERROR: Input File Open Failed!");
		}
		std::cin.clear();
		std::cin.rdbuf(fin.rdbuf());
	}

	/******************** INPUT *******************/
	int product_count = 0;
	int machine_count = 0;
	std::cin >> product_count >> machine_count;
	// table resize for products
	table.resize(product_count);
	for (int i = 0; i < product_count; ++i) {
		table[i].resize(machine_count);
	}

	for (int i = 0; i < product_count; ++i) {
		for (int j = 0; j < machine_count; ++j) {
			std::cin >> table[i][j].machine >> table[i][j].duration;
		}
	}
	// alternative input
		//for (int i = 0; i < product_count; ++i) {
		//	for (int j = 0; j < machine_count; ++j) {
		//		std::cin >> table[i][j].duration;
		//	}
		//}
		//for (int i = 0; i < product_count; ++i) {
		//	for (int j = 0; j < machine_count; ++j) {
		//		std::cin >> table[i][j].machine;
		//	}
		//}
	fin.close();
} // void read_under_cmd(...)


void print_under_cmd(const DVector2D<MACHINE_TASK>& res_table,
	bool to_file, std::string outfile_name, const DVector<int>& best, double time, const DVector2D<PROCEDURE>& jobtable)
{
	std::string output("");
	for (int i = 0; i < res_table.size(); ++i) {
		output += ("M" + std::to_string(i));
		for (int j = 0; j < res_table[i].size(); ++j) {
			output += (" ("
				+ std::to_string(res_table[i][j].start) + ","
				+ std::to_string(res_table[i][j].product) + "-"
				+ std::to_string(res_table[i][j].proced) + ","
				+ std::to_string(res_table[i][j].end)
				+ ")"
				);
		}
		output += '\n';
	}


	output += ("Time Used: " + std::to_string(time) + '\n'
		+ "End Time: " + std::to_string(chromo_time(jobtable, best, 1)) + '\n');
	//std::cout << "Time Used: " <<  << std::endl;
	//std::cout << "End Time: " << chromo_time(jobtable, champion_chromo.chromo, 1) << std::endl;


	std::cout << output;

	if (to_file) {
		std::ofstream fout;
		fout.open(outfile_name, std::ios_base::out);
		if (!fout.is_open()) {
			throw jsException("ERROR: Output File Open Failed!");
		}
		fout << output;
	}
} // void print_under_cmd(...)             
