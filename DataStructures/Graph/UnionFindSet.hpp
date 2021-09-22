#ifndef UNIONFINDSET_HPP
#define UNIONFINDSET_HPP

namespace UnionFindSet {

template <int size>
class UnionFindSet {
public:
	void clear(int n) {
		for (int i = 0; i <= n; i++) {
			father[i] = i;
		}
	}

	void query(int x) {
		if (x == father[x]) {
			return x;
		} else {
			return father[x] = query(father[x]);
		}
	}

	void merge(int x, int y) {
		x = query(x);
		y = query(y);
		if (x != y) {
			father[y] = x;
		}
	}
private:
	int father[size];
};

} // namespace UnionFindSet

#endif