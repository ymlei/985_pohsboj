#include <iostream>
#include "jobshop.h"
#include "jobshop_io.h"
#include "jobshop_ga.h"

int main(int argc, char* argv[])
{
	try {
		int count = 0;
		CHROMO champion_chromo;
		champion_chromo.time = 1 << 22;

		LAUNCH_PARAMETRE para = read_parametres_under_cmd(argc, argv);
		DVector2D<PROCEDURE> jobtable;
		read_under_cmd(jobtable, para.from_file, para.infile_name);

		clock_t t1 = clock();
		clock_t t2 = clock();
		TIME Longest = 0;
		while ((t2 = clock()) - t1 < (300 - 5/4 * Longest) * 1000) {
			CHROMO best_chromo = jobshop_GA(jobtable);
			if (champion_chromo.time > best_chromo.time)
				champion_chromo = best_chromo;
			count++;
			if (Longest < (clock() - t2)/1000) Longest = (clock() - t2)/1000;
			//std::cout << "Longest = " << Longest << "\n";
			#ifdef DEBUG
				std::cout << "timecost = " << double(t2 - t1) / 1000 << '\n';
				std::cout << "time = " << best_chromo.time << std::endl;
				std::cout << "pass = " << (clock() - t1) / 1000 << "from" << (t2 - t1) / 1000 << "s" << std::endl;
			#endif	
		}
		#ifdef DEBUG
			std::cout << "final " << champion_chromo.time << "by " << count;
		#endif
		
		DVector2D<MACHINE_TASK> result_table = get_result_table(jobtable, champion_chromo);
		print_under_cmd(result_table, para.to_file, para.outfile_name,
						champion_chromo.chromo, static_cast<double>(clock() - t1) / 1000, jobtable);

	}
	catch (DException a) {
		a.print();
	}
	catch (...) {
		std::cout << "UNKNOWN ERROR\n";
	}
	#ifdef DEBUG
	system("pause");
	#endif
	return EXIT_SUCCESS;
}