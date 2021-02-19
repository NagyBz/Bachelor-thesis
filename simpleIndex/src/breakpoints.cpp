//
// Created by martin & balazs  on 10/04/2020.
//
#include "breakpoints.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>


const std::map<unsigned int, std::vector<double>> &Breakpoints::getForCardinality() const {
    return forCardinality;
}

double RationalApproximation(double t) {
    // Abramowitz and Stegun formula 26.2.23.
    // The absolute value of the error should be less than 4.5 e-4.
    double c[] = {2.515517, 0.802853, 0.010328};
    double d[] = {1.432788, 0.189269, 0.001308};
    return t - ((c[2]*t + c[1])*t + c[0]) /
               (((d[2]*t + d[1])*t + d[0])*t + 1.0);
}

double NormalCDFInverse(double p) {
    if (p <= 0.0 || p >= 1.0) {
        std::stringstream os;
        os << "Invalid input argument (" << p
           << "); must be larger than 0 but less than 1.";
        throw std::invalid_argument( os.str() );
    }

    // See article above for explanation of this section.
    if (p < 0.5) {
        // F^-1(p) = - G^-1(p)
        return -RationalApproximation( sqrt(-2.0*log(p)) );
    }
    else {
        // F^-1(p) = G^-1(1-p)
        return RationalApproximation( sqrt(-2.0*log(1-p)) );
    }
}

std::vector<double> LinearSpacedArray(double a, double b, std::size_t N) {
    double h = (b - a) / static_cast<double>(N-1);
    std::vector<double> xs(N);
    std::vector<double>::iterator x;
    double val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h) {
        *x = val;
    }
    return xs;
}

std::vector<double> Breakpoints::generateBreakpointsDynamic(double cardinality) {
    std::vector<double> result;
    // Show that the NormalCDFInverse function is accurate at
    // 0.05, 0.15, 0.25, ..., 0.95 and at a few extreme values.
    auto p = LinearSpacedArray(0,1,cardinality + 1);
    int numValues = p.size();
    for (int i = 1; i < numValues - 1; i++) {
        double computed = NormalCDFInverse(p[i]);
        if (p[i] == 0.5) {
            computed = 0;
        }
        result.push_back(computed);
    }
    return result;
}
