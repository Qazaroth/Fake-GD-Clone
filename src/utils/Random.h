#pragma once

#include <random>

inline static int randomInt(int min, int max)
{
	return min + (std::rand() % (max - min + 1));
}