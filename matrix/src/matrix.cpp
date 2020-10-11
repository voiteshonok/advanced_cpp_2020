#include "matrix.h"

Matrix::Matrix() : row(1), col(1) {
    allocateMemory();
    markWithOnes();
}

Matrix::Matrix(size_t rows, size_t cols) : row(rows), col(cols) {
    allocateMemory();
    markWithOnes();
}

Matrix::Matrix(const Matrix &copy) : row(copy.row), col(copy.col) {
    allocateMemory();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            arr[i][j] = copy[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < row; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}


Matrix::ProxyArr Matrix::operator[](size_t n) const {
    return ProxyArr(arr[n]);
}

Matrix &Matrix::operator=(const Matrix &a) {
    if (&a == this) {
        return *this;
    }
    delete this;
    row = a.getRow();
    col = a.getCol();
    allocateMemory();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            arr[i][j] = a[i][j];
        }
    }
    return *this;
}

size_t Matrix::getRow() const {
    return row;
}

size_t Matrix::Matrix::getCol() const {
    return col;
}

double &Matrix::get(size_t n, size_t m) {
    if (n >= row || n < 0 || m >= col || m < 0) {
        throw OutOfBoundsException();
    }
    return arr[n][m];
}

const double &Matrix::get(size_t n, size_t m) const {
    if (n >= row || n < 0 || m >= col || m < 0) {
        throw OutOfBoundsException();
    }
    return arr[n][m];
}

void Matrix::set(size_t n, size_t m, const double &value) {
    if (n >= row || n < 0 || m >= col || m < 0) {
        throw OutOfBoundsException();
    }
    arr[n][m] = value;
}

void Matrix::resize(size_t n, size_t m) {
    auto *temp = new Matrix(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            temp->arr[i][j] = 0;
        }
    }
    for (int i = 0; i < getMin(n, row); ++i) {
        for (int j = 0; j < getMin(m, col); ++j) {
            temp->arr[i][j] = arr[i][j];
        }
    }
    delete this;
    arr = temp->arr;
    col = temp->getCol();
    row = temp->getRow();
}

void Matrix::allocateMemory() {
    arr = new double *[row];
    for (int i = 0; i < row; ++i) {
        arr[i] = new double[col];
    }
}

void Matrix::markWithOnes() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            arr[i][j] = (i == j ? 1 : 0);
        }
    }
}

int Matrix::getMin(int a, int b) {
    return (a > b ? b : a);
}

void Matrix::checkMismatch(int n, int m) const {
    if (n != row || m != col) {
        throw SizeMismatchException();
    }
}

void Matrix::checkMismatch() const {
    if (row != col) {
        throw SizeMismatchException();
    }
}

Matrix &Matrix::operator+=(const Matrix &a) {
    checkMismatch(a.row, a.col);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            arr[i][j] += a[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &a) const {
    Matrix temp = *this;
    return temp += a;
}

Matrix &Matrix::operator-=(const Matrix &a) {
    return *this += -a;
}

Matrix Matrix::operator-(const Matrix &a) const {
    Matrix temp = *this;
    return temp -= a;
}

Matrix operator*(const double &a, const Matrix &b) {
    Matrix temp = b;
    for (int i = 0; i < temp.getRow(); ++i) {
        for (int j = 0; j < temp.getCol(); ++j) {
            temp[i][j] *= a;
        }
    }
    return temp;
}

Matrix Matrix::operator-() const {
    Matrix temp = *this;
    return -1 * temp;
}

Matrix Matrix::operator+() const {
    Matrix temp = *this;
    return temp;
}

Matrix &Matrix::operator*=(const double &number) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            arr[i][j] *= number;
        }
    }
    return *this;
}

Matrix Matrix::operator*(const double &number) const {
    Matrix temp = *this;
    return temp *= number;
}

Matrix &Matrix::operator*=(const Matrix &a) {
    if (col != a.getRow()) {
        throw SizeMismatchException();
    }
    Matrix temp(row, a.getCol());
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < temp.getCol(); ++j) {
            double s = 0;
            for (int k = 0; k < col; ++k) {
                s += arr[i][k] * a[k][j];
            }
            temp[i][j] = s;
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &a) const {
    Matrix temp = *this;
    return temp *= a;
}

bool Matrix::operator==(const Matrix &a) const {
    checkMismatch();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (!areClose(arr[i][j], a[i][j])) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &a) const {
    return !(a == *this);
}

bool Matrix::areClose(double a, double b) {
    return abs(a - b) <= EPS;
}

double Matrix::abs(double a) {
    return (a > 0 ? a : -a);
}

std::vector<double> Matrix::getRow(size_t row) {
    std::vector<double> vec(getRow());
    for (int i = 0; i < getRow(); ++i) {
        vec[i] = arr[row][i];
    }
    return vec;
}

std::vector<double> Matrix::getColumn(size_t column) {
    std::vector<double> vec(getCol());
    for (int i = 0; i < getCol(); ++i) {
        vec[i] = arr[i][column];
    }
    return vec;
}

std::ostream &operator<<(std::ostream &output, const Matrix &matrix) {
    for (int i = 0; i < matrix.getRow(); ++i) {
        for (int j = 0; j < matrix.getCol(); ++j) {
            output << matrix[i][j];
        }
    }
    return output;
}

std::istream &operator>>(std::istream &input, Matrix &matrix) {
    int n, m;
    input >> n >> m;
    matrix.resize(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            input >> matrix[i][j];
        }
    }
    return input;
}

double Matrix::det() const {
    checkMismatch();
    Matrix arr = *this;
    for (int i = 0; i < arr.getRow() - 1; ++i) {
        for (int j = i + 1; j < arr.getCol(); ++j) {
            double coef = double(arr[j][i]) / arr[i][i];
            for (int k = i; k < arr.getRow(); ++k) {
                arr[j][k] -= arr[i][k] * coef;
            }
        }
    }
    double d = 1;
    for (int i = 0; i < arr.getRow(); ++i) {
        d *= arr[i][i];
    }
    return d;
}

double Matrix::trace() const {
    checkMismatch();
    double s = 0;
    for (int i = 0; i < getRow(); ++i) {
        s += arr[i][i];
    }
    return s;
}

Matrix Matrix::transposed() const {
    Matrix temp(getCol(), getRow());
    for (int i = 0; i < getRow(); ++i) {
        for (int j = 0; j < getCol(); ++j) {
            temp[j][i] = arr[i][j];
        }
    }
    return temp;
}

void Matrix::transpose() {
    *this = this->transposed();
}