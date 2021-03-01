#pragma once

#ifdef DEBUG_ENABLE
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define DEBUG_EXPR(x) do { std::cerr << #x << ": " << x << std::endl; } while(0)
#else
#define DEBUG(...) do {} while (0)
#define DEBUG_EXPR(x) do {} while (0)
#endif
