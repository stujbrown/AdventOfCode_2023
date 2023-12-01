#pragma once

namespace aoc
{

struct Args
{
    int day_to_run = -1;
};

Args parse_args(int num_args, const char* args[]);
void entry(const Args& args);

}
