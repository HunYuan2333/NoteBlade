#ifndef VERSION_H
#define VERSION_H

#include <string>

const static std::string  PROGRAM_NAME   = "noteblade";
const static unsigned int VERSION_MAJOR  = 0;
const static unsigned int VERSION_MINOR  = 1;
const static unsigned int VERSION_PATCH  = 0;
const static std::string  VERSION_STRING = std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) + "." + std::to_string(VERSION_PATCH);
const static std::string  COPYRIGHT_TEXT = "Copyright (c) 2023 FeatherP & TCP, All rights reserved";


#ifdef  _MSC_VER
#define BUILD_COMPILER    "MSVC "  << _MSC_FULL_VER
#endif
#ifdef  __clang__
#define BUILD_COMPILER    "Clang " << __clang_version__
#endif
#ifndef BUILD_COMPILER
#define BUILD_COMPILER    "Unknown"
#endif

#ifdef _WIN32
#define BUILD_PLATFORM    "Windows_NT/" << _WIN32_WINNT
#endif
#ifdef  XMAKE_PLATFORM
#define BUILD_PLATFORM    XMAKE_PLATFORM
#endif
#ifndef BUILD_PLATFORM
#define BUILD_PLATFORM    "Unknown_OS"
#endif

#ifdef _MSVC_LANG
#define CXX_VERSION       _MSVC_LANG
#endif
#ifdef __clang__
#define CXX_VERSION       __cplusplus
#endif
#ifndef CXX_VERSION
#define CXX_VERSION       "??"
#endif

#ifndef BUILD_TIME
#define BUILD_TIME        ""
#endif

#ifndef BUILD_HOSTNAME
#define BUILD_HOSTNAME    "none"
#endif

#ifdef  DEBUG
#define BUILD_MODE       "Debug"
#endif
#ifdef  RELEASE
#define BUILD_MODE       "Release"
#endif
#ifndef BUILD_MODE
#define BUILD_MODE       "Internal_Version"
#endif

#define BUILD_INFO       BUILD_MODE << " C++ " << CXX_VERSION << " [" << BUILD_COMPILER << "] " << BUILD_TIME << " " << BUILD_PLATFORM << " " << BUILD_HOSTNAME

#endif
