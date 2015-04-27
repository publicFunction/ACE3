/*
 * ace_vd.cpp
 *
 *
 */

#include "ace_common.h"

static char version[] = "1.0";

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
        return command;
    }

    return input.substr(0, cmd_end);
}



void __stdcall RVExtension(char *output, int outputSize, const char *function) {
    // Get the command, then the command args
    std::string input = function;

    std::string command = get_command(input);
    std::string arguments = input.substr(command.length()+1, (input.length()+1 - command.length()));
    
    if (command.size() < 1) {
        output[0] = 0x00;
        return;
    }
    if (command == "version") {
        memcpy(output, version, strlen(version) + 1); return;
    }
    if (command == "echo") {
        memcpy(output, function, strlen(function) + 1); return;
    }

    /*************************/
    // Real functionality goes here
    if (command == "clear") {
        
    }
}
