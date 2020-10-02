#pragma once

#include <vector>
#include <iostream>


namespace task {

    const double EPS = 1e-6;

    double abs(const double &a) {
        return (a >= 0 ? a : -a);
    }

    bool AreClose(const double &a, const double &b) {
        return abs(a - b) <= EPS;
    }

    std::vector<double> operator+(const std::vector<double> &a, const std::vector<double> &b) {
        std::vector<double> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = a[i] + b[i];
        }

        return c;
    }

    std::vector<double> &operator+=(std::vector<double> &a, const std::vector<double> &b) {
        for (int i = 0; i < a.size(); ++i) {
            a[i] += b[i];
        }
        return a;
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
            if (!AreClose(coef, a[i] / b[i])) {
                return false;
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

    std::vector<double> reverse(const std::vector<double> &a) {
        std::vector<double> c(a.size());

        for (int i = 0; i < a.size(); ++i) {
            c[i] = a[a.size() - 1 - i];
        }

        return c;
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

}  // namespace task
