#ifndef BINARYINDEXEDTREE_HPP
#define BINARYINDEXEDTREE_HPP

namespace BinaryIndexedTree {

template <typename T, int size> class BinaryIndexedTree {
public:
	BinaryIndexedTree(int n): len(n) {}
	int size() {
		return len;
	}
	void modify(int pos, T val) {
		for (; pos <= len; pos += lowbit(pos)) {
			array[pos] += val;
		}
	}
	T query(int pos) {
		T ans = T(0);
		for (; pos; pos -= lowbit(pos)) {
			ans += array[pos];
		}
		return ans;
	}
	T query(int left, int right) {
		return query(right) - query(left - 1);
	}
private:
	T array[size];
	int len;
	T lowbit(T x) {
		return x & -x;
	}
};

} // namespace BinaryIndexedTree

#endif
