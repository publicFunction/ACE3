/*
 * ace_vd.cpp
 *
 *
 */

#include "ace_common.h"

#include "model_collection.hpp"

static char version[] = "1.0";

INITIALIZE_EASYLOGGINGPP

extern "C" {
    __declspec (dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
};

std::vector<std::string> split_args(const std::string & input) {
    std::istringstream ss(input);
    std::string token;

    std::vector<std::string> output;
    while (std::getline(ss, token, ',')) {
        output.push_back(token);
    }

    return output;
}

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

    std::string result;

    if (argument_str.length() > 0 && argument_str.find(",") != argument_str.npos) {
        arguments = split_args(argument_str);
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
    if (command == "init") {
        ace::model_collection::get().init();
        result = "OK";
        return;
    } else {
        if (!ace::model_collection::get().ready())
            return;
    }
    if (command == "load_model") {
        if (arguments.size() > 0) {
            if (ace::model_collection::get().load_model(arguments[0])) {
                result = "OK";
            } else {
                result = "ERR";
            }
        }
    }
    if (command == "reset") {
        ace::model_collection::get().reset();
    }

    if (result.length() > 0) {
        sprintf_s(output, outputSize, "%s", result.c_str());
    }
}
