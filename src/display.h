#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef _WIN32
#include <Windows.h>
#define DISPLAY_ADDRESS(x) "0x" << x
#endif

#ifndef _WIN32
#define DISPLAY_ADDRESS(x) x
#endif

#endif
