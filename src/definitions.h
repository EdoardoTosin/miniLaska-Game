#define DIM (7)
#define HEIGHT (3)
#define ROW (65)
#define EASY (1)
#define NORMAL (2)
#define HARD (4)

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#ifdef _WIN32
#include <Windows.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif
