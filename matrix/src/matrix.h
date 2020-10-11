#pragma once

#include <iostream>
#include <vector>


namespace task {

    const double EPS = 1e-6;


    class OutOfBoundsException : public std::exception {};
    class SizeMismatchException : public std::exception {};


    class Matrix {
    public:
        Matrix();

        Matrix(size_t rows, size_t cols);

        ~Matrix();

        class ProxyArr {
        public:
            explicit ProxyArr(double *row) : row(row) {}

            const double &operator[](size_t m) const {
                double &temp = row[m];
                //delete this;
                return temp;
            }

            double &operator[](size_t m) {
                double &temp = row[m];
                //delete this;
                return temp;
            }

        private:
            double *row;
        };

        ProxyArr operator[](size_t n) const;

        size_t getRow() const;

        size_t getCol() const;

        double &get(size_t row, size_t col);

        const double &get(size_t row, size_t col) const;

        void set(size_t row, size_t col, const double &value);

        void resize(size_t n, size_t m);

        Matrix &operator+=(const Matrix &a);

        Matrix &operator-=(const Matrix &a);

        Matrix &operator*=(const Matrix &a);

        Matrix &operator*=(const double &number);


        Matrix operator+(const Matrix &a) const;

        Matrix operator-(const Matrix &a) const;

        Matrix operator*(const Matrix &a) const;

        Matrix operator*(const double &a) const;

        Matrix operator-() const;

        Matrix operator+() const;

        bool operator==(const Matrix &a) const;

        bool operator!=(const Matrix &a) const;

        double det() const;

        void transpose();

        Matrix transposed() const;

        double trace() const;

        std::vector<double> getRow(size_t row);

        std::vector<double> getColumn(size_t column);

        Matrix(const Matrix &copy);

        Matrix &operator=(const Matrix &a);

    private:
        double **arr = nullptr;
        size_t row, col;

        void allocateMemory();

        void markWithOnes();

        size_t getMin(size_t a, size_t b);

        void checkMismatch(size_t n, size_t m) const;

        void checkMismatch() const;

        static double abs(double a);

        static bool areClose(double a, double b);
    };

    task::Matrix operator*(const double &a, const Matrix &b);

    std::ostream &operator<<(std::ostream &output, const Matrix &matrix);

    std::istream &operator>>(std::istream &input, Matrix &matrix);

}// namespace task