#pragma once
#include <functional>
#include <vector>
#include <string>

class CmdParser {

	public:

		struct Arg {
			std::string cmd;
			std::string arg;
			std::string var;

			Arg(const std::string &cmd, const std::string &arg, const std::string &var) :
				cmd(cmd), arg(arg), var(var) {}
		};

		struct Handler {
			std::vector<std::string> args;
			std::function<void(const CmdParser::Arg &arg)> cmd =
				[](const CmdParser::Arg &arg) {};
			bool needs_var = false;
		};

		CmdParser(
			const std::vector<std::string>& args,
			const std::vector<CmdParser::Handler>& handlers
		);

		CmdParser(int argc, char *argv[],
			const std::vector<CmdParser::Handler>& handlers);

	private:

		struct ArgHandler {
			int index;
			std::string arg;
			std::string var;
			bool needs_var;

			ArgHandler() : index(-1), arg(""), var(""), needs_var(false) {}
		};

		std::string _cmd;
		std::vector<std::string> _args;
		std::vector<CmdParser::Handler> _handlers;

	public:

		inline std::string cmd(void) { return this -> _cmd; }
		inline std::vector<std::string> args(void) { return this -> _args; }
		inline std::vector<CmdParser::Handler> handlers(void) { return this -> _handlers; }

		void parse(void);
};
