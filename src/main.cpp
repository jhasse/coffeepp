#include "file.hpp"

#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

int main(int argc, char** argv) {
	try {
		using namespace boost::program_options;

		std::vector<std::string> input;

		// Declare the supported options.
		options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("compile", value<int>(), "set compression level")
			("input", value(&input), "input files")
		;

		positional_options_description p;
		p.add("input", -1);

		variables_map vm;
		store(command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
		notify(vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}

		for (const auto& filename : input) {
			std::ifstream tmp{filename};
			File file(tmp);
			std::cout << file.getNewBuf() << std::endl;
		}
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
}