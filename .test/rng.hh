#include <utility>
#include <cmath>


class Rng {
private:
    uint32_t state;

    uint32_t random() {
        return (this->state = 1103515245*this->state + 12345);
    }

public:
    Rng(uint32_t seed) : state(seed) {}

    double uniform() {
        return double(this->random())/0x100000000;
    }
    
    std::pair<double, double> normal() {
        double phi = 2.0*M_PI*this->uniform();
        double r = -log(0.5*(1.0 - this->uniform()));
        return std::make_pair(r*cos(phi), r*sin(phi));
    }

};
