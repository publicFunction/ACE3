/*
 * ace_vd.cpp
 *
 *
 */

#include "shared.hpp"
#include "model_collection.hpp"
#include "controller.hpp"

static char version[] = "1.0";

extern "C" {
    __declspec (dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
};


std::string get_command(const std::string & input) {
    size_t cmd_end;
    std::string command;

    cmd_end = input.find(':');
    if (cmd_end < 1) {
        return "";
    }

    return input.substr(0, cmd_end);
}


void __stdcall RVExtension(char *output, int outputSize, const char *function) {
    // Get the command, then the command args
    std::string input = function;

    std::string command = get_command(input);
    std::string argument_str;
    if (command.length() > 1 && input.length() > command.length()+1) {
        argument_str = input.substr(command.length() + 1, (input.length() + 1 - command.length()));
    }
    std::vector<std::string> arguments;

    std::string result = "-1";

    if (argument_str.length() > 0 && argument_str.find(",") != argument_str.npos) {
        arguments = ace::split(argument_str, ',');
    } else {
        arguments.push_back(argument_str);
    }
    if (command.size() < 1) {
        output[0] = 0x00;
        return;
    }
    if (command == "version") {
        result = version;
    }
    if (command == "echo") {
        result = function;
    }

    /*************************/
    // Real functionality goes here
    if (!ace::model_collection::get().ready()) {
        if (command == "init") {                                                            // init:
            ace::model_collection::get().init();
            result = "0";
            return;
        }
    } else {
        if (command == "load_model") {                                                      // load_model:path\path\asdf.p3d
            if (arguments.size() > 0) {
                if (ace::model_collection::get().load_model(arguments[0])) {
                    result = "0";
                } else {
                    result = "-1";
                }
            }
        } else if (command == "reset") {                                                    // reset:
            ace::model_collection::get().reset();
        } else if (command == "hit") {
            if (!ace::vehicledamage::controller::get().handle_hit(arguments, result)) {
                result = "-1";
            }
        }
    }
    if (result.length() > 0) {
        sprintf_s(output, outputSize, "%s", result.c_str());
    }
}
