#include "LorentzVector.h"
#include <iostream>
#include <math.h>

LorentzVector::LorentzVector() {
    t_ = 0;
    x_ = 0;
    y_ = 0;
    z_ = 0;
}
LorentzVector::LorentzVector(double T, double X, double Y, double Z) : t_(T), x_(X), y_(Y), z_(Z) {}

double LorentzVector::t() const {
    return t_;
}
double LorentzVector::x() const {
    return x_;
}
double LorentzVector::y() const {
    return y_;
}
double LorentzVector::z() const {
    return z_;
}
double LorentzVector::norm() const {
    return sqrt(fabs(-t_*t_ + x_*x_ + y_*y_ + z_*z_));
}

void LorentzVector::t(double v) {
    t_ = v;
}
void LorentzVector::x(double v) {
    x_ = v;
}
void LorentzVector::y(double v) {
    y_ = v;
}
void LorentzVector::z(double v) {
    z_ = v;
}
void LorentzVector::operator+=(const LorentzVector& b) {
    t_ += b.t_;
    x_ += b.x_;
	y_ += b.y_;
	z_ += b.z_;
}
void LorentzVector::operator-=(const LorentzVector& b) {
    t_ -= b.t_;
    x_ -= b.x_;
	y_ -= b.y_;
	z_ -= b.z_;
}
void LorentzVector::operator*=(double a) {
    t_ *= a;
    x_ *= a;
	y_ *= a;
	z_ *= a;
}
LorentzVector LorentzVector::operator+(const LorentzVector& b) const {
    double T = t_ + b.t_;
    double X = x_ + b.x_;
    double Y = y_ + b.y_;
    double Z = z_ + b.z_;
    return LorentzVector(T, X, Y, Z);
}
LorentzVector LorentzVector::operator-(const LorentzVector& b) const {
    double T = t_ - b.t_;
    double X = x_ - b.x_;
    double Y = y_ - b.y_;
    double Z = z_ - b.z_;
    return LorentzVector(T, X, Y, Z);
}
LorentzVector operator*(const LorentzVector& lv, double a) {
    double T = a*lv.t_;
    double X = a*lv.x_;
    double Y = a*lv.y_;
    double Z = a*lv.z_;
    return LorentzVector(T, X, Y, Z);
}
std::ostream& operator<<(std::ostream& out, const LorentzVector& b) {
    out << "(" << b.t() << "; " << b.x() << "; " << b.y() << "; " << b.z() << ")";
    return out;
}
void LorentzVector::zboost(double beta) {
    double G = sqrt(1 - beta*beta);
    double T = (t_ + beta*z_)/G;
    double X = x_;
    double Y = y_;
    double Z = (z_ + beta*t_)/G;
    t_ = T;
    x_ = X;
    y_ = Y;
    z_ = Z;
}
double LorentzVector::dot(const LorentzVector& other) const {
    return t_*t_ + x_*x_ + y_*y_ + z_*z_;
}
