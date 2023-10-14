#include <string>
#include <iostream>
#include "xml.h"
#include "vsqx.h"
#include "version.h"
#include "display.h"

void ensure_windows_utf8() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
}

int main(int argc, char** argv)
{
    ensure_windows_utf8();
    const static unsigned int REQUIRED_ARGUMENTS = 1;

    if (argc == 2 && (std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version")) {
        std::cout << PROGRAM_NAME   << " " << VERSION_STRING << std::endl;
        std::cout << COPYRIGHT_TEXT << std::endl;
        std::cout << BUILD_INFO     << std::endl;
        return 0;
    }

    if ((argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) || argc < REQUIRED_ARGUMENTS + 1) {
        std::cout << COPYRIGHT_TEXT << std::endl;
        std::cout << "     Usage: " << PROGRAM_NAME << " <vsqx_file>" << std::endl;
        std::cout << "            " << PROGRAM_NAME << " -v | --version" << std::endl;
        std::cout << "            " << PROGRAM_NAME << " -h | --help"    << std::endl;
        return 0;
    }

    if (argc < 2) {
        std::cout << "Usage: noteblade <vsqx_file>" << std::endl;
        return -2;
    }
    auto vsqx_file = std::string(argv[1]);
    auto vsqx_reader = NoteBlade::VSQXReader(vsqx_file);
    vsqx_reader.project().display();

    return 0;
}
