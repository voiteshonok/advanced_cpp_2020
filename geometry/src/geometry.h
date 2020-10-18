#pragma once

#include <iostream>
#include <vector>
#include <cmath>

struct Point {

    Point(double, double);

    ~Point() = default;

    Point(const Point &);

    Point &operator=(const Point &);

    double x, y;

    bool operator==(const Point &) const;

    bool operator!=(const Point &) const;
};

class Line {
public:
    double a, b;

    Line(const Point &, const Point &);

    Line(double, double);

    Line(const Point &, double);

    ~Line() = default;

    Line(const Line &);

    Line &operator=(const Line &);

    bool operator==(const Line &) const;

    bool operator!=(const Line &) const;
};

class Shape {
public:
    virtual double perimeter() const = 0;

    virtual double area() const = 0;

    virtual bool operator==(const Shape &) const = 0;

    virtual void rotate(Point, double) = 0;

    virtual void reflex(Point) = 0;

    virtual void reflex(Line) = 0;

    virtual void scale(Point, double) = 0;

    virtual ~Shape() = 0;
};

class Ellipse : public Shape {
protected:
    Point F1, F2;
    double sum;

    static double ellipticFunc(double, double);

public:
    Ellipse(const Point &, const Point &, double);

    ~Ellipse() override;

    Ellipse(const Ellipse &);

    Ellipse &operator=(const Ellipse &);

    virtual bool operator==(const Ellipse &) const;

    virtual bool operator!=(const Ellipse &) const;

    bool operator==(const Shape &) const override;

    virtual bool operator!=(const Shape &) const;

    double perimeter() const override;

    double area() const override;

    void rotate(Point, double) override;

    void reflex(Point) override;

    void reflex(Line) override;

    void scale(Point, double) override;

    std::pair<Point, Point> focuses() const;

    Point center() const;

    double eccentricity() const;
};

class Circle : public Ellipse {
public:
    Circle(const Point &, double);

    ~Circle() override;

    Circle(const Circle &);

    Circle &operator=(const Circle &);

    /*bool operator==(const Circle &) const;

    bool operator!=(const Circle &) const;*/

    bool operator==(const Ellipse &) const override;

    bool operator!=(const Ellipse &) const override;

    bool operator==(const Shape &) const override;

    bool operator!=(const Shape &) const override;

    double radius();

    void scale(Point, double) override;
};

class Polygon : public Shape {
protected:
    std::vector<Point> vertices;

    static double getDistance(const Point &, const Point &);

    static double DegToRad(double);

public:
    int verticesCount() const;

    std::vector<Point> getVertices() const;

    explicit Polygon(std::vector<Point>);

    ~Polygon() override;

    Polygon(const Polygon &);

    Polygon &operator=(const Polygon &);

    virtual bool operator==(const Polygon &) const;

    virtual bool operator!=(const Polygon &) const;

    bool operator==(const Shape &) const override;

    virtual bool operator!=(const Shape &) const;

    double perimeter() const override;

    double area() const override;

    void rotate(Point, double) override;

    void reflex(Point) override;

    void reflex(Line) override;

    void scale(Point, double) override;
};

class Triangle : public Polygon {
public:
    explicit Triangle(const Point &, const Point &, const Point &);

    ~Triangle() override;

    Point centroid() const;

    Point orthocenter() const;

    Circle inscribedCircle() const;

    Circle circumscribedCircle() const;

    Line EulerLine() const;

    Circle ninePointsCircle() const;
};

class Rectangle : public Polygon {
protected:
    std::vector<Point> makePolygon(Point, Point, double);

public:
    Point center() const;

    std::pair<Line, Line> diagonals() const;

    explicit Rectangle(Point, Point, double);
};

class Square : public Rectangle {
public:
    Square(Point, Point);

    Circle circumscribedCircle() const;

    Circle inscribedCircle() const;
};

bool areClose(double a, double b) {
    return fabs(a - b) <= 1e-6;
}

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point(const Point &point) {
    x = point.x;
    y = point.y;
}

Point &Point::operator=(const Point &point) {
    if (this != &point) {
        x = point.x;
        y = point.y;
    }
    return *this;
}

bool Point::operator==(const Point &point) const {
    return (areClose(x, point.x) && areClose(y, point.y));
}

bool Point::operator!=(const Point &point) const {
    return !(*this == point);
}

Line::Line(double a, double b) : a(a), b(b) {}

Line::Line(const Point &firstPoint, const Point &secondPoint) {
    a = (firstPoint.y - secondPoint.y) / (firstPoint.x - secondPoint.x);
    b = firstPoint.y - firstPoint.x * a;
}

Line::Line(const Point &point, double a) : a(a) {
    b = point.y - a * point.x;
}

Line::Line(const Line &line) {
    a = line.a;
    b = line.b;
}

Line &Line::operator=(const Line &line) {
    if (this != &line) {
        a = line.a;
        b = line.b;
    }
    return *this;
}

bool Line::operator==(const Line &line) const {
    return (areClose(a, line.a) && areClose(b, line.b));
}

bool Line::operator!=(const Line &line) const {
    return !(*this == line);
}

Shape::~Shape() = default;

Ellipse::Ellipse(const Point &F1, const Point &F2, double sum) : F1(F1), F2(F2), sum(sum) {}

Ellipse::~Ellipse() = default;

Ellipse::Ellipse(const Ellipse &ellipse) : F1(ellipse.F1), F2(ellipse.F2), sum(ellipse.sum) {}

Ellipse &Ellipse::operator=(const Ellipse &ellipse) {
    if (this != &ellipse) {
        F1 = ellipse.F1;
        F2 = ellipse.F2;
        sum = ellipse.sum;
    }
    return *this;
}

bool Ellipse::operator==(const Ellipse &ellipse) const {
    return (ellipse.F1 == F1 && ellipse.F2 == F2 && areClose(sum, ellipse.sum));
}

bool Ellipse::operator!=(const Ellipse &ellipse) const {
    return !(*this == ellipse);
}

bool Ellipse::operator==(const Shape &shape) const {
    return false;
}

bool Ellipse::operator!=(const Shape &shape) const {
    return !(*this == shape);
}

double Ellipse::ellipticFunc(double x, double e) {
    return sqrt(1 - e * e * sin(x) * sin(x));
}

double Ellipse::perimeter() const {
    long double a = 0.0, b = acos(-1) / 2;
    long long N = 1e8;
    long double s = 0, e = eccentricity();
    long double h = (b - a) / N;
    for (long long i = 0; i < N; ++i) {
        long double x = a + h * i;
        s += ellipticFunc(x, e) * ((i == 0 || i == N) ? 1 : ((i & 1) == 0 ? 2 : 4));
    }
    s *= h / 3;
    return s * sum * 2;
}

double Ellipse::area() const {
    double a = sum / 2;
    double c = sqrt((F1.x - F2.x) * (F1.x - F2.x) + (F1.y - F2.y) * (F1.y - F2.y)) / 2,
            b = a * sqrt(1 - (c / a) * (c / a));
    return acos(-1) * a * b;
}

void Ellipse::rotate(Point, double) {
    std::cout << "Unable to rotate ellipse in these coordinates\n";
}

void Ellipse::reflex(Point) {
    std::cout << "Unable to rotate ellipse in these coordinates\n";
}

void Ellipse::reflex(Line) {
    std::cout << "Unable to reflex ellipse in these coordinates\n";
}

void Ellipse::scale(Point point, double coefficient) {
    sum *= coefficient;
    double vectorX = (point.x - (F1.x + F2.x) / 2), vectorY = (point.y - (F1.y + F2.y) / 2);
    F1.x = F1.x - point.x + vectorX * coefficient;
    F1.y = F1.y - point.y + vectorY * coefficient;
    F2.x = F2.x - point.x + vectorX * coefficient;
    F2.y = F2.y - point.y + vectorY * coefficient;
}

std::pair<Point, Point> Ellipse::focuses() const {
    return {F1, F2};
}

Point Ellipse::center() const {
    return Point((F1.x + F2.x) / 2, (F1.y + F2.y) / 2);
}

double Ellipse::eccentricity() const {
    double a = sum / 2;
    double c = sqrt((F1.x - F2.x) * (F1.x - F2.x) + (F1.y - F2.y) * (F1.y - F2.y)) / 2;
    return c / a;
}

Circle::Circle(const Point &center, double radius) : Ellipse(center, center, 2 * radius) {}

Circle::~Circle() = default;

Circle::Circle(const Circle &circle) : Ellipse(circle.F1, circle.F2, circle.sum) {}

Circle &Circle::operator=(const Circle &circle) {
    if (this != &circle) {
        F1 = circle.F1;
        F2 = circle.F2;
        sum = circle.sum;
    }
    return *this;
}

bool Circle::operator==(const Ellipse &ellipse) const {
    return Ellipse::operator==(ellipse);
}

bool Circle::operator!=(const Ellipse &ellipse) const {
    return !(*this == ellipse);
}

bool Circle::operator==(const Shape &) const {
    return false;
}

bool Circle::operator!=(const Shape &shape) const {
    return !(*this == shape);
}
/*
bool operator==(const Ellipse &ellipse, const Circle &circle) {
    return circle == ellipse;
}*/

bool operator!=(const Ellipse &ellipse, const Circle &circle) {
    return circle != ellipse;
}

double Circle::radius() {
    return sum / 2;
}

void Circle::scale(Point point, double coefficient) {
    sum *= coefficient;
    F1.x = point.x - (point.x - F1.x) * coefficient;
    F1.y = point.y - (point.y - F1.y) * coefficient;
    F2 = F1;
}


Polygon::Polygon(std::vector<Point> vertices) : vertices(vertices) {}

Polygon::~Polygon() = default;

Polygon::Polygon(const Polygon &polygon) : vertices(polygon.vertices) {}

Polygon &Polygon::operator=(const Polygon &polygon) {
    if (this != &polygon) {
        vertices = polygon.vertices;
    }
    return *this;
}

int Polygon::verticesCount() const {
    return vertices.size();
}

std::vector<Point> Polygon::getVertices() const {
    const std::vector<Point> temp = vertices;
    return temp;
}

bool Polygon::operator==(const Polygon &polygon) const {
    if (verticesCount() != polygon.verticesCount())return false;
    if (verticesCount() == 0)return false;
    int i = 0;
    for (; i < polygon.vertices.size(); ++i) {
        if (vertices[0] == polygon.vertices[i])break;
    }
    if (i == polygon.vertices.size())return false;
    int step = 0;
    if (vertices[1] == polygon.vertices[(i + 1) % polygon.vertices.size()]) {
        step = 1;
    } else if (vertices[1] == polygon.vertices[((i - 1) % polygon.vertices.size() + polygon.vertices.size()) %
                                               polygon.vertices.size()]) {
        step = -1;
    } else {
        return false;
    }
    for (int j = 0, k = i;
         j < verticesCount(); ++j, k = ((k + step) % verticesCount() + verticesCount()) % verticesCount()) {
        if (vertices[j] != polygon.vertices[k])return false;
    }
    return true;
}

bool Polygon::operator!=(const Polygon &polygon) const {
    return !(*this == polygon);
}

bool Polygon::operator==(const Shape &) const {
    return false;
}

bool Polygon::operator!=(const Shape &shape) const {
    return !(*this == shape);
}

double Polygon::getDistance(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double Polygon::perimeter() const {
    double perimeter = 0;
    for (int i = 0; i < verticesCount(); ++i) {
        perimeter += getDistance(vertices[i], vertices[(i + 1) % verticesCount()]);
    }
    return perimeter;
}

double Polygon::area() const {
    double area = 0;
    for (int i = 0; i < verticesCount(); ++i) {
        area += (vertices[i].y + vertices[(i + 1) % verticesCount()].y) / 2 *
                (vertices[(i + 1) % verticesCount()].x - vertices[i].x);
    }
    return fabs(area);
}

double Polygon::DegToRad(double x) {
    return x / 180 * acos(-1);
}

void Polygon::rotate(Point point, double angle) {
    for (int i = 0; i < verticesCount(); ++i) {
        double radius = getDistance(point, vertices[i]),
                del = atan((vertices[i].y - point.y) / (vertices[i].x - point.x));
        if (vertices[i].x < point.x) {
            del += acos(-1);
        }
        vertices[i].x = point.x + radius * cos(del + DegToRad(angle));
        vertices[i].y = point.y + radius * sin(del + DegToRad(angle));
    }
}

void Polygon::reflex(Point point) {
    rotate(point, 180);
}

void Polygon::reflex(Line line) {
    for (int i = 0; i < verticesCount(); ++i) {
        if (line.a == 0) {
            vertices[i].y *= -1;
        } else {
            double a2 = -1 / line.a, b2 = vertices[i].y + vertices[i].x / line.a;
            double x = (b2 - line.b) / (line.a - a2), y = a2 * x + b2;
            vertices[i].x += x - vertices[i].x;
            vertices[i].y += y - vertices[i].y;
        }
    }
}

void Polygon::scale(Point point, double coefficient) {
    for (int i = 0; i < verticesCount(); ++i) {
        double x = point.x - vertices[i].x, y = point.y - vertices[i].y;
        vertices[i].x = point.x + coefficient * x;
        vertices[i].y = point.y + coefficient * y;
    }
}

Triangle::Triangle(const Point &a, const Point &b, const Point &c) : Polygon({a, b, c}) {}

Triangle::~Triangle() = default;

Point Triangle::centroid() const {
    double x = (vertices[0].x + vertices[1].x) / 2,
            y = (vertices[0].y + vertices[1].y) / 2,
            vectx = (x - vertices[2].x) * 2 / 3,
            vecty = (y - vertices[2].y) * 2 / 3;
    return Point(vertices[2].x + vectx, vertices[2].y + vecty);
}

Point Triangle::orthocenter() const {
    double vect =
            getDistance(vertices[0], Point((vertices[1].x + vertices[2].x) / 2, (vertices[1].y + vertices[2].y) / 2)) *
            2 / 3;
    return Point(vertices[0].x + vect, vertices[0].y + vect);
}

Circle Triangle::inscribedCircle() const {
    double a = getDistance(vertices[1], vertices[2]), b = getDistance(vertices[0], vertices[2]),
            c = getDistance(vertices[0], vertices[1]),
            x = (a * vertices[0].x + b * vertices[1].x + c * vertices[2].x) / (a + b + c),
            y = (a * vertices[0].y + b * vertices[1].y + c * vertices[2].y) / (a + b + c);
    return Circle(Point(x, y), area() / perimeter() * 2);
}

Circle Triangle::circumscribedCircle() const {
    double a1 = (vertices[1].x - vertices[0].x) / (vertices[0].y - vertices[1].y),
            b1 = (vertices[1].y + vertices[0].y) / 2 - a1 * (vertices[1].x + vertices[0].x) / 2,
            a2 = (vertices[0].x - vertices[2].x) / (vertices[2].y - vertices[0].y),
            b2 = (vertices[0].y + vertices[2].y) / 2 - a2 * (vertices[0].x + vertices[2].x) / 2,
            x = (b2 - b1) / (a1 - a2), y = a1 * x + b1;
    double a = getDistance(vertices[1], vertices[2]), b = getDistance(vertices[0], vertices[2]),
            c = getDistance(vertices[0], vertices[1]);
    return Circle(Point(x, y), a * b * c / 4 / area());
}

Line Triangle::EulerLine() const {
    return Line(ninePointsCircle().center(), centroid());
}

Circle Triangle::ninePointsCircle() const {
    return Circle(Point((orthocenter().x + circumscribedCircle().center().x) / 2,
                        (orthocenter().y + circumscribedCircle().center().y) / 2), circumscribedCircle().radius() / 2);
}

Point Rectangle::center() const {
    return Point((vertices[0].x + vertices[2].x) / 2, (vertices[0].y + vertices[2].y) / 2);
}

std::pair<Line, Line> Rectangle::diagonals() const {
    double a = (vertices[2].y - vertices[0].y) / (vertices[2].x - vertices[0].x);
    Line line1(a, vertices[2].y - a * vertices[2].x);
    a = (vertices[3].y - vertices[1].y) / (vertices[3].x - vertices[1].x);
    Line line2(a, vertices[3].y - a * vertices[3].x);
    return {line1, line2};
}

Rectangle::Rectangle(Point a, Point b, double coefficient) : Polygon(makePolygon(a, b, coefficient)) {}

std::vector<Point> Rectangle::makePolygon(Point a, Point b, double coefficient) {
    if (b.y < a.y)std::swap(a, b);
    double left = getDistance(a, b) / sqrt(1 + coefficient * coefficient), right = left * coefficient;
    if (left < right)std::swap(left, right);
    double vectorX = b.x - a.x, vectorY = b.y - a.y, tg = atan(-vectorX / vectorY);
    return {a, Point(a.x + cos(tg) * left, a.y + sin(tg) * left), b, Point(b.x - cos(tg) * left, b.y * cos(tg))};
}

Square::Square(Point a, Point b) : Rectangle(a, b, 1) {}

Circle Square::circumscribedCircle() const {
    return Circle(center(), getDistance(vertices[1], vertices[2]) * sqrt(2));
}

Circle Square::inscribedCircle() const {
    return Circle(center(), getDistance(vertices[1], vertices[2]));
}
