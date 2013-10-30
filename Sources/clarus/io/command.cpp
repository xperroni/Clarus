#include "command.hpp"

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
namespace fs = boost::filesystem;

#include <sys/stat.h>
#include <sys/types.h>

#include <cstdarg>
#include <stdexcept>

Command::Command(const std::string &format, const std::string &mode) {
    std::string path = (fs::temp_directory_path() / fs::unique_path()).native();

    int status = mkfifo(path.c_str(), 0666);
    if (status != 0) {
        throw std::runtime_error("Could not create named pipe \"" + path + '"');
    }

    std::string command = (boost::format(format) % path).str();
    std::string background = (boost::format("(%s) &") % command).str();
    status = system(background.c_str());

    reset(fopen(path.c_str(), mode.c_str()), fclose);
}

InputCommand::InputCommand(const std::string &command):
    Command(command, "r")
{
    // Nothing to do.
}

bool InputCommand::operator () (std::string &line) {
    char *buffer = NULL;
    size_t size = 0;

    int length = getline(&buffer, &size, get());
    if (length <= 0) {
        return false;
    }

    line = std::string(buffer, length);
    free(buffer);
    return true;
}

OutputCommand::OutputCommand(const std::string &command, bool _autoflush):
    Command(command, "w"),
    autoflush(_autoflush)
{
    // Nothing to do.
}

void OutputCommand::operator () (const std::string &format, ...) {
    va_list args;
    va_start(args, format);

    vfprintf(get(), (format + '\n').c_str(), args);
    if (autoflush) {
        flush();
    }

    va_end(args);
}

void OutputCommand::flush() {
    fflush(get());
}

