#include "ZGE/Vector.hpp"

using namespace zge;

Vector::Vector(double argX, double argY) :
x(argX),
y(argY)
{
}

double Vector::radToDeg(double argRad)
{
    return argRad * (180.f / pi);
}

double Vector::degToRad(double argDeg)
{
    return argDeg * (pi / 180.f);
}

Vector Vector::degToVector(double deg)
{
    return radToVector(degToRad(deg));
}

Vector Vector::radToVector(double rad)
{
    return zge::Vector(std::sin(rad), -std::cos(rad));
}

Vector& Vector::operator=(const Vector& argVec)
{
    x = argVec.x;
    y = argVec.y;
    return *this;
}

Vector Vector::operator+(const Vector& argVec)
{
    Vector vec(x + argVec.x, y + argVec.y);
    return vec;
}

Vector& Vector::operator+=(const Vector& argVec)
{
    *this = *this + argVec;
    return *this;
}

Vector Vector::operator-(const Vector& argVec)
{
    Vector vec(x - argVec.x, y - argVec.y);
    return vec;
}

Vector& Vector::operator-=(const Vector& argVec)
{
    *this = *this - argVec;
    return *this;
}

Vector Vector::operator*(const Vector& argVec)
{
    Vector vec(x * argVec.x, y * argVec.y);
    return vec;
}

Vector& Vector::operator*=(const Vector& argVec)
{
    *this = *this * argVec;
    return *this;
}

Vector Vector::operator/(const Vector& argVec)
{
    Vector vec(x / argVec.x, y / argVec.y);
    return vec;
}

Vector& Vector::operator/=(const Vector& argVec)
{
    *this = *this / argVec;
    return *this;
}

Vector Vector::operator+(double argScalar)
{
    Vector vec(x + argScalar, y + argScalar);
    return vec;
}

Vector& Vector::operator+=(double argScalar)
{
    *this = *this + argScalar;
    return *this;
}

Vector Vector::operator-(double argScalar)
{
    Vector vec(x - argScalar, y - argScalar);
    return vec;
}

Vector& Vector::operator-=(double argScalar)
{
    *this = *this - argScalar;
    return *this;
}

Vector Vector::operator*(double argScalar)
{
    Vector vec(x * argScalar, y * argScalar);
    return vec;
}

Vector& Vector::operator*=(double argScalar)
{
    *this = *this * argScalar;
    return *this;
}

Vector Vector::operator/(double argScalar)
{
    Vector vec(x / argScalar, y / argScalar);
    return vec;
}

Vector& Vector::operator/=(double argScalar)
{
    *this = *this / argScalar;
    return *this;
}

double Vector::dot(Vector argVec)
{
    return (x * argVec.x) + (y * argVec.y);
}

double Vector::length()
{
    return std::sqrt(x * x + y * y);
}

double Vector::lengthSquared()
{
    return x * x + y * y;
}

void Vector::normalize()
{
    if (this->length() != 0)
    {
        *this /= this->length();
    }
}

Vector Vector::normalized()
{
    if (this->lengthSquared() == 0) return Vector(0, 0);
    Vector vec = *this / this->length();
    return vec;
}

void Vector::turnLeft()
{
    this->x = -(this->x);
}

Vector Vector::turnedLeft()
{
    Vector vec(y, -x);
    return vec;
}

void Vector::turnRight()
{
    this->y = -(this->y);
}

Vector Vector::turnedRight()
{
    Vector vec(-y, x);
    return vec;
}

void Vector::rotateWithDeg(double argDeg)
{
    argDeg = zge::Vector::degToRad(argDeg);

    //we use them both twice so store them, sin and cos are expensive calls.
    double sinResult = std::sin(argDeg);
    double cosResult = std::cos(argDeg);

    this->x = (this->x * cosResult) - (this->y * sinResult);
    this->y = (this->x * sinResult) + (this->y * cosResult);
}

Vector Vector::rotatedWithDeg(double argDeg)
{
    argDeg = degToRad(argDeg);

    //we use them both twice so store them, sin and cos are expensive calls.
    double sinResult = std::sin(argDeg);
    double cosResult = std::cos(argDeg);

    Vector vec((this->x * cosResult) - (this->y * sinResult), (this->x * sinResult) + (this->y * cosResult));

    return vec;
}

void Vector::rotateWithRad(double argRad)
{
    //we use them both twice so store them, sin and cos are expensive calls.
    double sinResult = std::sin(argRad);
    double cosResult = std::cos(argRad);

    this->x = (this->x * cosResult) - (this->y * sinResult);
    this->y = (this->x * sinResult) + (this->y * cosResult);
}

Vector Vector::rotatedWithRad(double argRad)
{
    //we use them both twice so store them, sin and cos are expensive calls.
    double sinResult = std::sin(argRad);
    double cosResult = std::cos(argRad);

    Vector vec((this->x * cosResult) - (this->y * sinResult), (this->x * sinResult) + (this->y * cosResult));

    return vec;
}

double Vector::degrees()
{
    return std::atan2(x, -y) * (180.f / pi);
}

double Vector::radians()
{
    return std::atan2(x, -y);
}
