#include <cctype>
#include <random>

using namespace std;

int get_random(uint max)
{
	using u32    = uint_least32_t;
	using engine = std::mt19937;

	std::random_device os_seed;
	const u32 seed = os_seed();

	engine generator(seed);
	std::uniform_int_distribution<u32> distribute(1, max);

	return distribute(generator);
}
