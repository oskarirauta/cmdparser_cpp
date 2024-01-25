#include <iostream>
#include <string>
#include "cmdparser.hpp"

const std::string APP_NAME = "cmdParser";
const std::string APP_VERSION = "1.0.0";

static void version_header(void) {

	std::cout << APP_NAME << " version " << APP_VERSION << "\n"
		"author: Oskari Rauta" << std::endl;
}

static void usage(const CmdParser::Arg &arg) {

	std::cout << "\nusage: " << arg.cmd << " [args]" << "\n" << std::endl;
	std::cout << "options:\n" <<
		" -h, --h               usage\n" <<
		" -v, --v               version\n" <<
		" -n name, --n name     name argument with name variable\n" <<
		std::endl;
}

static void show_version(const CmdParser::Arg &arg) {

	version_header();
	exit(0);
}

static void show_name(const CmdParser::Arg &arg) {

	std::cout << "executed " << arg.cmd << " with name arg (" << arg.arg <<
		") where variable is " << arg.var << std::endl;
}

int main(int argc, char *argv[]) {

//	CmdParser cmdparser(std::vector<std::string>(argv, argv + argc),
	CmdParser cmdparser(argc, argv,
		{
			{{ "-h", "--h", "-help", "--help" }, [](const CmdParser::Arg &arg) {
					version_header();
					usage(arg);
					exit(0);
				}, false },
			{{ "-v", "--v", "-version", "--version" }, show_version },
			{{ "-n", "--n", "-name", "--name" }, show_name, true },
			{{ "" }, [](const CmdParser::Arg &arg) {
					std::cout << "unknown argument " << arg.arg << "\n" <<
						"Try executing " << arg.cmd << " --h for usage" <<
						std::endl;
				}
			}
		});

	cmdparser.parse();

	if ( argc == 1 )
		std::cout << argv[0] << ": try program with some arguments, such as --h for help" << std::endl;

	return 0;
}
