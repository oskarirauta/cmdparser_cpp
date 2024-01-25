#include "cmdparser.hpp"

CmdParser::CmdParser(const std::vector<std::string>& args,
			const std::vector<CmdParser::Handler>& handlers) {

	int c = 0;
	for ( std::string arg : args )
		if ( c++ == 0 ) this -> _cmd = arg;
		else this -> _args.push_back(arg);

	this -> _handlers = handlers;
}

CmdParser::CmdParser(int argc, char *argv[],
			const std::vector<CmdParser::Handler>& handlers) {

	std::vector<std::string> args(argv, argv + argc);
	int c = 0;
	for ( std::string arg : args )
		if ( c++ == 0 ) this -> _cmd = arg;
		else this -> _args.push_back(arg);

	this -> _handlers = handlers;
}

void CmdParser::parse(void) {

	CmdParser::ArgHandler p_handler;

	for ( std::string arg : this -> _args ) {

		int i = 0;
		bool unlisted = true;

		if ( p_handler.needs_var ) {
			p_handler.var = arg;

			this -> _handlers[p_handler.index].cmd(
				CmdParser::Arg(this -> _cmd, p_handler.arg, p_handler.var));
			p_handler = CmdParser::ArgHandler();
			continue;
		}

		for ( CmdParser::Handler handler : this -> _handlers ) {

			for ( std::string h_arg : handler.args )
				if ( h_arg == arg ) {

					unlisted = false;

					p_handler.index = i;
					p_handler.arg = arg;
					p_handler.needs_var = handler.needs_var;

					if ( p_handler.needs_var )
						break;

					this -> _handlers[p_handler.index].cmd(
						CmdParser::Arg(this -> _cmd, p_handler.arg,
							p_handler.var));

					p_handler = CmdParser::ArgHandler();
					break;
				}
			i++;
		}

		if ( !unlisted )
			continue;

		// unlisted

		i = 0;

		for ( CmdParser::Handler handler : this -> _handlers ) {
			if ( handler.args.size() == 1 && handler.args[0].empty()) {

				p_handler.index = i;
				p_handler.arg = arg;

				this -> _handlers[p_handler.index].cmd(
					CmdParser::Arg(this -> _cmd, p_handler.arg,
						p_handler.var));

				p_handler = CmdParser::ArgHandler();
				break;
			}
			i++;
		}
	}

	if ( p_handler.needs_var && p_handler.index >= 0 ) {

		this -> _handlers[p_handler.index].cmd(
			CmdParser::Arg(this -> _cmd, p_handler.arg, p_handler.var));

		p_handler = CmdParser::ArgHandler();
	}
}
