#ifndef UTILITY_TRACES_HPP
#define UTILITY_TRACES_HPP

#include <cstdio>

#define INFO(fmt, ...) do { fprintf(stderr, fmt, __VA_ARGS__); } while (0);

#if _DEBUG
#define DEBUG(fmt, ...) do { INFO(fmt, __VA_ARGS__); } while (0);
#else
#define DEBUG(mt, ...)
#endif

#endif  // !UTILITY_TRACES_HPP
