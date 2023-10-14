#ifndef ERROR_H
#define ERROR_H

#include <string>

#define ERR_XML_FILE_NOT_FOUND    1
#define ERR_XML_READ_VALUE        2
#define ERR_SINGER_NOT_FOUND      3
#define ERR_TRACK_NOT_FOUND       4

#define ERR_STRING_FORMAT_MESSAGE(name, i)      name + "(" + std::to_string(i) + ")"
#define ERR_NUMBER_FORMAT_MESSAGE(i)            ERR_STRING_FORMAT_MESSAGE(ERROR_STRING[i], i)

namespace NoteBlade {
    const static std::string ERROR_STRING[] = {
        "XML_FILE_NOT_FOUND",
        "XML_READ_VALUE",
        "SINGER_NOT_FOUND",
        "TRACK_NOT_FOUND",
    };
}

#endif
