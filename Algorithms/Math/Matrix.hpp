template <typename T>
class Matrix {
public:
    Matrix(bool v) : vaild(v), mod(1) {}

    Matrix(int r = 0, int c = 0, T m = 1) : row(r), column(c), mod(m) {
        memset(data, 0, sizeof(data));
        vaild = m != 0;
    }

    T* operator[](int x) {
        return data[x];
    }

    Matrix<T> operator+(const Matrix<T>& r) {
        if (!vaild || !r.vaild || row != r.row && column != r.column)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, column, mod);
        for (int i = 0; i <= row; ++i) {
            for (int j = 0; j <= column; ++j) {
                res[i][j] = (data[i][j] + r.data[i][j]) % mod;
            }
        }
        return res;
    }

    Matrix<T> operator-(const Matrix<T>& r) {
        if (!vaild || !r.vaild || row != r.row && column != r.column)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, column, mod);
        for (int i = 0; i <= row; ++i) {
            for (int j = 0; j <= column; ++j) {
                res = (data[i][j] - r.data[i][j] + mod) % mod;
            }
        }
        return res;
    }

    Matrix<T> operator*(const Matrix<T>& r) {
        if (!vaild || !r.vaild || column != r.row)
            return Matrix<T>(false);
        Matrix<T> res = Matrix<T>(row, r.column, mod);
        for (int i = 0; i <= row; ++i) {
            for (int j = 0; j <= r.column; ++j) {
                for (int k = 0; k <= column; ++k) {
                    res[i][j] = (res[i][j] + data[i][k] * r.data[k][j]) % mod;
                }
            }
        }
        return res;
    }

    Matrix<T> operator^(T k) {
        if (row != column || !vaild)
            return Matrix<T>(false);
        Matrix<T> self = *this;
        Matrix<T> res = Matrix<T>(row, column, mod);
        for (int i = 0; i <= row; ++i)
            res[i][i] = 1;
        while (k) {
            if (k % 2 == 1)
                res = res * self;
            self = self * self;
            k /= 2;
        }
        return res;
    }
private:
    T data[105][105], mod;
    int row, column;
    bool vaild;
};