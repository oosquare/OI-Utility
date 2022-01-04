#ifndef RANDOMENGINE_HPP
#define RANDOMENGINE_HPP

namespace RandowEngine {

class RandomEngine {
public:
	RandomEngine(long long in = 233ll) { seed = in; }
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
	long long seed;
	int nextInt() {
		return seed = (int)(seed * 482711ll % 0x7fffffff);
	}
	
	long long nextLongLong() {
		return seed = (long long)(seed * 482711ll % 0x7fffffffffffffff);
	}
}

} // namespace RandomEngine

#endif