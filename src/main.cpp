#include "entry.hpp"

#include <stdlib.h>

int main(int argc, const char* argv[])
{
    aoc::entry(aoc::parse_args(argc, argv));

#if _WIN32
    system("pause");
#endif
    return 0;
}
