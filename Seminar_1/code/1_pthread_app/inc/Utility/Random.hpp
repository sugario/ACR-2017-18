#ifndef UTILITY_RANDOM_HPP
#define UTILITY_RANDOM_HPP

#include <cstdint>
#include <random>

class Random
{
public:
	Random();
	explicit Random(uint32_t seed);

	int32_t Next() const;
	int32_t Next(int32_t ceiling) const;
	int32_t Next(int32_t floor, int32_t ceiling) const;

	double NextDouble() const;
	float NextFloat() const;

private:
	std::default_random_engine& globalURNG() const;
	void Randomize() const;
	void Randomize(uint32_t seed) const;
};

#endif  // !UTILITY_RANDOM_HPP
