#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <utility>

#include <cstdlib>
#include <cmath>

#include "rng.hh"
#include "color.hh"

#include <LorentzVector.h>

using namespace std;

#define EPS 1e-8

static const int N_TRIES = 16; 

inline double sqr(double v) {
    return v*v;
}

bool f_eq(double a, double b, double eps=EPS) {
    return fabs(a - b) < eps;
}

bool lv_eq(LorentzVector a, LorentzVector b, double eps=EPS) {
    return
        f_eq(a.t(), b.t(), eps) &&
        f_eq(a.x(), b.x(), eps) &&
        f_eq(a.y(), b.y(), eps) &&
        f_eq(a.z(), b.z(), eps);
}

LorentzVector lv_random(Rng *rng) {
    pair<double, double> tx = rng->normal(), yz = rng->normal();
    double t = tx.first, x = tx.second, y = yz.first, z = yz.second;
    return LorentzVector(t, x, y, z);
}

void replace_other(string *str, const char *srcs, char dst) {
    for (int i = 0; i < str->size(); ++i) {
        bool found = false;
        for (int j = 0; srcs[j] != '\0'; ++j) {
            if ((*str)[i] == srcs[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            (*str)[i] = dst;
        }
    }
}

vector<double> parse(string str) {
    vector<double> nums;
    int b = -1;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] != ' ') {
            if (b < 0) {
                b = i;
            }
        } else {
            if (b >= 0) {
                nums.push_back(atof(str.substr(b, i - b).c_str()));
                b = -1;
            }
        }
    }
    if (b >= 0) {
        nums.push_back(atof(str.substr(b, str.size() - b).c_str()));
    }
    return nums;
}

int main() {
    vector<pair<string, function<bool(Rng*)>>> tests = {

        make_pair(string("constructor_default"), [](Rng *rng) -> bool {
            LorentzVector lv = LorentzVector();
            return 
                f_eq(lv.t(), 0.0) &&
                f_eq(lv.x(), 0.0) &&
                f_eq(lv.y(), 0.0) &&
                f_eq(lv.z(), 0.0);
        }),

        make_pair(string("constructor_component_wise"), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                pair<double, double> tx = rng->normal(), yz = rng->normal();
                double t = tx.first, x = tx.second, y = yz.first, z = yz.second;
                LorentzVector lv = LorentzVector(t, x, y, z);
                if (!( 
                    f_eq(lv.t(), t) &&
                    f_eq(lv.x(), x) &&
                    f_eq(lv.y(), y) &&
                    f_eq(lv.z(), z)
                )) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("setters"), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lvo = lv_random(rng);
                LorentzVector lvm = lvo;
                double v = rng->normal().first;
                bool res;
                switch (k % 4) {
                    case 0:
                        lvm.t(v);
                        res = (
                            f_eq(lvm.t(), v) &&
                            f_eq(lvm.x(), lvo.x()) &&
                            f_eq(lvm.y(), lvo.y()) &&
                            f_eq(lvm.z(), lvo.z())
                        );
                    break;
                    case 1:
                        lvm.x(v);
                        res = (
                            f_eq(lvm.t(), lvo.t()) &&
                            f_eq(lvm.x(), v) &&
                            f_eq(lvm.y(), lvo.y()) &&
                            f_eq(lvm.z(), lvo.z())
                        );
                    break;
                    case 2:
                        lvm.y(v);
                        res = (
                            f_eq(lvm.t(), lvo.t()) &&
                            f_eq(lvm.x(), lvo.x()) &&
                            f_eq(lvm.y(), v) &&
                            f_eq(lvm.z(), lvo.z())
                        );
                    break;
                    case 3:
                        lvm.z(v);
                        res = (
                            f_eq(lvm.t(), lvo.t()) &&
                            f_eq(lvm.x(), lvo.x()) &&
                            f_eq(lvm.y(), lvo.y()) &&
                            f_eq(lvm.z(), v)
                        );
                    break;

                }
                if (!res) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("norm"), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv = lv_random(rng);
                double norm2 = fabs(sqr(lv.t()) - sqr(lv.x()) - sqr(lv.y()) - sqr(lv.z()));
                if (!f_eq(sqr(lv.norm()), norm2)) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("operator+"), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv0 = lv_random(rng), lv1 = lv_random(rng);
                LorentzVector lvs = lv0 + lv1;
                if (!(
                    f_eq(lv0.t() + lv1.t(), lvs.t()) &&
                    f_eq(lv0.x() + lv1.x(), lvs.x()) &&
                    f_eq(lv0.y() + lv1.y(), lvs.y()) &&
                    f_eq(lv0.z() + lv1.z(), lvs.z())
                )) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("operator-"), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv0 = lv_random(rng), lv1 = lv_random(rng);
                LorentzVector lvs = lv0 - lv1;
                if (!(
                    f_eq(lv0.t() - lv1.t(), lvs.t()) &&
                    f_eq(lv0.x() - lv1.x(), lvs.x()) &&
                    f_eq(lv0.y() - lv1.y(), lvs.y()) &&
                    f_eq(lv0.z() - lv1.z(), lvs.z())
                )) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("operator*"), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv = lv_random(rng);
                double f = rng->normal().first;
                LorentzVector lvs = lv*f;
                if (!(
                    f_eq(lv.t()*f, lvs.t()) &&
                    f_eq(lv.x()*f, lvs.x()) &&
                    f_eq(lv.y()*f, lvs.y()) &&
                    f_eq(lv.z()*f, lvs.z())
                )) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("operator+="), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv0 = lv_random(rng), lv1 = lv_random(rng);
                LorentzVector lvs = lv0;
                lvs += lv1;
                if (!(
                    f_eq(lv0.t() + lv1.t(), lvs.t()) &&
                    f_eq(lv0.x() + lv1.x(), lvs.x()) &&
                    f_eq(lv0.y() + lv1.y(), lvs.y()) &&
                    f_eq(lv0.z() + lv1.z(), lvs.z())
                )) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("operator-="), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv0 = lv_random(rng), lv1 = lv_random(rng);
                LorentzVector lvs = lv0;
                lvs -= lv1;
                if (!(
                    f_eq(lv0.t() - lv1.t(), lvs.t()) &&
                    f_eq(lv0.x() - lv1.x(), lvs.x()) &&
                    f_eq(lv0.y() - lv1.y(), lvs.y()) &&
                    f_eq(lv0.z() - lv1.z(), lvs.z())
                )) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("operator*="), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv = lv_random(rng);
                double f = rng->normal().first;
                LorentzVector lvs = lv;
                lvs *= f;
                if (!(
                    f_eq(lv.t()*f, lvs.t()) &&
                    f_eq(lv.x()*f, lvs.x()) &&
                    f_eq(lv.y()*f, lvs.y()) &&
                    f_eq(lv.z()*f, lvs.z())
                )) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("zboost"), [](Rng *rng) -> bool {
            for (int k = 0; k < N_TRIES; ++k) {
                // Check zboost transformation doesn't change the metric
                LorentzVector lv0 = lv_random(rng), lv1 = lv_random(rng);
                double norm = (lv0 + lv1).norm();
                double beta = (1.0 - EPS)*2.0*(rng->uniform() - 0.5);
                lv0.zboost(beta);
                lv1.zboost(beta);
                if (!f_eq((lv0 + lv1).norm(), norm)) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("dot"), [](Rng *rng) -> bool {
            bool sign_match = true;
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv0 = lv_random(rng), lv1 = lv_random(rng);
                double dot = lv0.dot(lv1);
                double ref_dot = 
                    lv0.t()*lv1.t() +
                    -lv0.x()*lv1.x() +
                    -lv0.y()*lv1.y() +
                    -lv0.z()*lv1.z();

                bool match = (dot >= 0.0) == (ref_dot >= 0.0);
                if (k != 0 && match != sign_match) {
                    return false;
                }
                sign_match = match;

                if (!f_eq(fabs(dot), fabs(ref_dot))) {
                    return false;
                }

                // Check dot product is Lorentz-invariant
                double beta = (1.0 - EPS)*2.0*(rng->uniform() - 0.5);
                lv0.zboost(beta);
                lv1.zboost(beta);
                if (!f_eq(lv0.dot(lv1), dot)) {
                    return false;
                }
            }
            return true;
        }),

        make_pair(string("operator<<"), [](Rng *rng) -> bool {
            ostringstream strout;

            bool res = true;
            for (int k = 0; k < N_TRIES; ++k) {
                LorentzVector lv = lv_random(rng)*100.0;
                strout << lv << endl;
                strout.flush();

                string str = strout.str();
                replace_other(&str, "0123456789.eE+-", ' ');
                vector<double> nums = parse(str);
                strout.str(string());

                if (nums.size() != 4 || !(
                    f_eq(nums[0], lv.t(), 1.0) &&
                    f_eq(nums[1], lv.x(), 1.0) &&
                    f_eq(nums[2], lv.y(), 1.0) &&
                    f_eq(nums[3], lv.z(), 1.0)
                )) {
                    res = false;
                    break;
                }
            }

            return res;
        }),
    };

    Rng rng(0xDEADBEEF);

    Colored<const char *> ok = green("ok"), fail = red("fail");

    int total = tests.size();
    int failed = 0;
    int counter = 0;

    for (pair<string, function<bool(Rng*)>> &pair : tests) {
        if (pair.second(&rng)) {
            cout << "[" << ok << "]";
        } else {
            failed += 1;
            cout << "[" << fail << "]";
        }
        cout << " (" << counter << "/" << total << ") ";
        cout << pair.first << endl;
        counter += 1;
    }

    int ret = 0;
    cout << "result: ";
    if (failed > 0) {
        cout << fail;
        ret = 1;
    } else {
        cout << ok;
    }
    cout << ". " << total - failed << " passed, " << failed << " failed." << endl;
    
    return ret;
}
