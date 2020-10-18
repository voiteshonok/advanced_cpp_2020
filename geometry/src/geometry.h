#pragma once

#include <iostream>
#include <vector>

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
