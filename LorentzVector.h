class LorentzVector {
public:
    LorentzVector();
    LorentzVector(double, double, double, double);

    double t() const;
    double x() const;
    double y() const;
    double z() const;
    double norm() const;

    void t(double x);
    void x(double x);
    void y(double x);
    void z(double x);

    void operator+=(const LorentzVector& other);
    void operator-=(const LorentzVector& other);
    void operator*=(double a);
    LorentzVector operator+(const LorentzVector& other) const;
    LorentzVector operator-(const LorentzVector& other) const;
    friend LorentzVector operator*(const LorentzVector& lv, double a);
    friend std::ostream& operator << (std::ostream&, const LorentzVector&);
    void zboost(double beta);
    double dot(const LorentzVector& other) const;
};

std::ostream& operator << (std::ostream&, const LorentzVector&);
