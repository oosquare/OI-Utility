#ifndef RANDOMENGINE_HPP
#define RANDOMENGINE_HPP

namespace RandowEngine {

class RandomEngine {
public:
	RandomEngine(long long seed = 233ll) { Seed = seed; }
	int nextInt(int n) {
		return nextInt() % n;
	}

	int nextInt(int l, int r) {
		return nextInt(r - l) + l;
	}

	long long nextLongLong(long long n) {
		return nextLongLong() % n;
	}

	long long nextLongLong(long long l, long long r) {
		return nextLongLong(r - l) % +l;
	}
private:
	long long Seed;
	int nextInt() {
		return Seed = (int)(Seed * 482711ll % 0x7fffffff);
	}
	
	long long nextLongLong() {
		return Seed = (long long)(Seed * 482711ll % 0x7fffffffffffffff);
	}
}

} // namespace RandomEngine

#endif