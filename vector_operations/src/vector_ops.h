#pragma once

#include <iostream>
#include <vector>


namespace task {

    double abs(const double &a) {
        return (a >= 0 ? a : -a);
    }

    bool AreClose(const double &a, const double &b) {
        return abs(a - b) <= 1e-7;
    }

    std::vector<double> &operator+=(std::vector<double> &a, const std::vector<double> &b) {
        for (int i = 0; i < a.size(); ++i) {
            a[i] += b[i];
        }
        return a;
    }

    std::vector<double> operator+(const std::vector<double> &a, const std::vector<double> &b) {
        /*std::vector<double> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = a[i] + b[i];
        }*/
        std::vector<double> c = a;
        c += b;

        return c;
    }

    std::vector<double> operator+(const std::vector<double> &a) {
        std::vector<double> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = a[i];
        }

        return c;
    }

    std::vector<double> operator-(const std::vector<double> &a) {
        std::vector<double> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = -a[i];
        }

        return c;
    }

    std::vector<double> operator-(const std::vector<double> &a, const std::vector<double> &b) {
        std::vector<double> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = a[i] - b[i];
        }

        return c;
    }

    std::vector<double> &operator-=(std::vector<double> &a, const std::vector<double> &b) {
        for (int i = 0; i < a.size(); ++i) {
            a[i] -= b[i];
        }
        return a;
    }

    double operator*(const std::vector<double> &a, const std::vector<double> &b) {
        double c = 0;

        for (int i = 0; i < a.size(); ++i) {
            c += a[i] * b[i];
        }

        return c;
    }

    std::vector<double> operator%(const std::vector<double> &a, const std::vector<double> &b) {
        std::vector<double> c(3);

        c[0] = a[1] * b[2] - a[2] * b[1];
        c[1] = a[2] * b[0] - a[0] * b[2];
        c[2] = a[0] * b[1] - a[1] * b[0];

        return c;
    }

    bool operator||(const std::vector<double> &a, const std::vector<double> &b) {
        double coef;
        int i = 0;
        for (; i < a.size() && AreClose(a[i] + b[i], 0); ++i) {}
        if (i == a.size()) {
            return true;
        } else {
            coef = a[i] / b[i];
        }

        for (; i < a.size(); ++i) {
            /*if (!AreClose(coef, a[i] / b[i])) {
                return false;
            }*/
            if (b[i] != 0) {
                if (!AreClose(coef, a[i] / b[i])) {
                    return false;
                }
            } else if (a[i] != 0) {
                if (!AreClose(1 / coef, b[i] / a[i])) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator&&(const std::vector<double> &a, const std::vector<double> &b) {
        if (!(a || b)) return false;

        for (int i = 0; i < a.size(); ++i) {
            if (a[i] * b[i] < 0) {
                return false;
            }
        }

        return true;
    }

    void reverse(std::vector<double> &a) {
        for (int i = 0; i < a.size() / 2; ++i) {
            /*double temp = a[i];
            a[i] = a[a.size() - i - 1];
            a[a.size() - 1 - i] = temp;*/
            std::swap(a[i], a[a.size() - i - 1]);
        }
    }

    std::vector<int> operator|(const std::vector<int> &a, const std::vector<int> &b) {
        std::vector<int> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = a[i] | b[i];
        }

        return c;
    }

    std::vector<int> operator&(const std::vector<int> &a, const std::vector<int> &b) {
        std::vector<int> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = a[i] & b[i];
        }

        return c;
    }

    std::istream &operator>>(std::istream &stream, std::vector<double> &a) {
        int n;
        stream >> n;
        a = std::vector<double>(n);
        for (int i = 0; i < n; ++i) {
            stream >> a[i];
        }
        return stream;
    }

    std::ostream &operator<<(std::ostream &cout, const std::vector<double> &a) {
        for (int i = 0; i < a.size(); ++i) {
            cout << a[i] << " ";
        }
        cout << std::endl;
        return cout;
    }

}// namespace task
