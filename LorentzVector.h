#include <iostream>

class LorentzVector {
private:
    double t_;
    double x_;
    double y_;
    double z_;
public:
    LorentzVector();
    LorentzVector(double, double, double, double);

    double t() const;
    double x() const;
    double y() const;
    double z() const;
    double norm() const;

    void t(double v);
    void x(double v);
    void y(double v);
    void z(double v);

    void operator+=(const LorentzVector& other);
    void operator-=(const LorentzVector& other);
    void operator*=(double a);
    LorentzVector operator+(const LorentzVector& other) const;
    LorentzVector operator-(const LorentzVector& other) const;
    friend LorentzVector operator*(const LorentzVector& lv, double a);
    friend std::ostream& operator << (std::ostream& out, const LorentzVector& b);
    void zboost(double beta);
    double dot(const LorentzVector& other) const;
};

std::ostream& operator<< (std::ostream &out, const LorentzVector &b);
