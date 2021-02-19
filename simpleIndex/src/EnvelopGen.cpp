//
// Created by nagy on 7. 11. 2019.
//

#include <symbol.h>
#include <limits>
#include <onebar.h>
#include <iSax.h>
#include <cmath>
#include <mysql.h>
#include <numeric>
#include <chrono>
#include "EnvelopGen.h"


EnvelopGen::~EnvelopGen() = default;

EnvelopGen::EnvelopGen(int length, int points, int lmin, int lmax, int gama, int slide) :
        length(length),
        points(points),
        lmin(lmin), lmax(lmax),
        gama(gama),
        slide(slide),
        w(int(lmax / points)),
        isax(w, 2, length) {
}
double compute_average(std::vector<double> &v, int m, int n) {
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<double> vec(first, last);

    auto mean = std::accumulate(std::begin(vec), std::end(vec), 0.0) / vec.size();

    return mean;
}

std::vector<double> zNorm(std::deque<OneBar *> *oneBars) {
    std::vector<double> values;
    double sdBody = 0;
    std::vector<double> zNormValues;
    for (auto & oneBar : *oneBars) {
        values.push_back(oneBar->getHigh());
    }
    double mean = (std::accumulate(values.begin(), values.end(), 0.0)) / values.size();
    for (double el: values) {
        sdBody += pow(el  - mean, 2);
    }
    double sd = sqrt(sdBody/values.size());
    for (double v: values) {
        zNormValues.push_back((v - mean)/sd);
    }
    return zNormValues;
}

std::vector<double> EnvelopGen::genPaa(const std::vector<double>& zNormValues) {
    double minDouble = -std::numeric_limits<double>::max();
    std::vector<double> PAA(w, minDouble);
    for (int i = 0; i < zNormValues.size() / (length / w); i++) {
        double sum = 0;
        for (int j = i * (length / w); j <= i * (length / w) + (length / w) - 1; j++) {
            sum += zNormValues.at(j);
        }
        PAA[i] = sum / (length / w);
    }
    return PAA;
}

std::vector<unsigned int> EnvelopGen::findEnvelope(std::deque<OneBar *> *oneBars) {
    double maxDouble = std::numeric_limits<double>::max();
    double minDouble = -std::numeric_limits<double>::max();
    std::vector<int> segUpdateList(w, 0);
    std::vector<double> U(w, minDouble);
    std::vector<double> L(w, maxDouble);
    std::vector<double> PAAs(lmax + gama - (points - 1) - 1, 0);
    computeZnormalized(oneBars, 0, U, L, PAAs);
    // auto PAA = genPaa(zNorm(oneBars));
    std::vector<unsigned int> data = isax.findData(U, L);

    return data;
}

void EnvelopGen::genEnvelopZnorm(Symbol *oneSymbol) {
    std::deque<OneBar *> *oneBars = oneSymbol->getList();
    double maxDouble = std::numeric_limits<double>::max();
    double minDouble = -std::numeric_limits<double>::max();
    int envelopeTime = 0;
    int indexingTime = 0;
    std::chrono::steady_clock::time_point start, end;
    for (int j = 0; j < oneBars->size() - length; j += length) {
        std::vector<int> segUpdateList(w, 0);
        std::vector<double> U(w, minDouble);
        std::vector<double> L(w, maxDouble);
        std::vector<double> PAAs(lmax + gama - (points - 1) - 1, 0);
        start = std::chrono::steady_clock::now();
        computeZnormalized(oneBars, j, U, L, PAAs);
        end = std::chrono::steady_clock::now();
        envelopeTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        start = std::chrono::steady_clock::now();
        isax.generateiSax(U, L, j, oneBars);
        end = std::chrono::steady_clock::now();
        indexingTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
    std::cout << "Envelope building time " << envelopeTime << std::endl;
    std::cout << "Indexing time " << indexingTime << std::endl;
    // isax.printPreOrder();
}

void
EnvelopGen::computeZnormalized(std::deque<OneBar *> *oneBars, int j, std::vector<double> &U, std::vector<double> &L,
                               std::vector<double> &PAAs) const {
    if (length - (slide - 1) >= lmin) {
        int nSeg = 0;
        double accSum = 0;
        double accSqSum = 0;
        for (int i = slide; i < std::min(int(oneBars->size()) + 1, slide + lmax + gama - 1); i++) {
            if ((i - slide) >= points) {
                nSeg++;
                PAAs[nSeg] = PAAs[nSeg - 1] - oneBars->at(j + i - points)->getHigh();
            }
            PAAs[nSeg] += oneBars->at(j + i - 1)->getHigh();
            accSum += oneBars->at(j + i - 1)->getHigh();
            accSqSum += pow(oneBars->at(j + i - 1)->getHigh(), 2);
            if (i - (slide - 1) >= lmin) {
                double acSAc = accSum;
                double acSQSAc = accSqSum;
                int nMse = std::min(gama + 1, (i - (slide - 1) - lmin) + 1);
                for (int z = 1; z <= nMse; z++) {
                    int wSubSeq = i - (slide - 1) - (z - 1);
                    if (wSubSeq <= lmax) {
                        double ro = acSAc/wSubSeq;
                        double sigmaBody = (acSQSAc/wSubSeq) - ro*ro;
                        double sigma = 0;
                        if (sigmaBody > 0) {
                            sigma = sqrt((acSQSAc / wSubSeq) - ro * ro);
                        }
                        unsigned int nSegUL = wSubSeq / points;
                        for (int k = 1; k <= nSegUL; k++) {
                            unsigned int index = z + ((k - 1) * points) - 1;
                            double a = PAAs[index];
                            double b = points * ro;
                            double paaNorm = 0;
                            if (sigma != 0) {
                                paaNorm = ((a - b)/sigma) / points;
                            }
                            U.at(k - 1) = std::max(paaNorm, U.at(k - 1));
                            L.at(k - 1) = std::min(paaNorm, L.at(k - 1));
                        }
                    }
                    acSAc -= oneBars->at(j + z)->getHigh();
                    acSQSAc -= pow(oneBars->at(j + z)->getHigh(), 2);
                }

            }
        }
    }
}


void EnvelopGen::createEnvelop(Symbol *oneSymbol) {
    auto *isax = new iSax(w, 2, length);
    std::deque<OneBar *> *oneBars = oneSymbol->getList();
    double maxDouble = std::numeric_limits<double>::max();
    double minDouble = -std::numeric_limits<double>::max();

    for (int j = 0; j < oneBars->size() - length; j += length) {

        std::vector<int> segUpdateList(w, 0);
        std::vector<double> U(w, minDouble);
        std::vector<double> L(w, maxDouble);

        // ComputeEnvelop(oneBars, j, segUpdateList, U, L);
        // UEnvelop[j] = isax->generateiSax(U, j, oneBars);
        // LEnvelop[j] = iSax->generateiSax(L, j);
    }
    isax->printPreOrder();
    std::cout << "Done" << std::endl;
    //auto *const mySQL = new MySQL();


    //mySQL->insertLEnvelop(LEnvelop, w);
    //mySQL->insertUEnvelop(UEnvelop, w);


    //delete mySQL;
}

// void EnvelopGen::ComputeEnvelop(std::deque<OneBar *> *oneBars, int j, std::vector<int> &segUpdateList,
//                                 std::vector<double> &U, std::vector<double> &L) const {
//     if (length - (slide - 1) >= lmin) {
//
//         double paaRSum = 0;
//
//         for (int i = slide; i <= std::min(length, slide + lmax + gama); i++) {
// 
//             OneBar *oneBar = oneBars->at(j + i);
//             paaRSum = paaRSum + oneBar->getZNormMax();
// 
//             if ((i - slide) > points) {
//                 OneBar *oneBar1 = oneBars->at(j + i - points);
//                 paaRSum = paaRSum - oneBar1->getZNormMax();
//             }
//             UpdateEnvelopSegment(segUpdateList, U, L, paaRSum, i);
//         }
//    }
//
//}

void
EnvelopGen::UpdateEnvelopSegment(std::vector<int> &segUpdateList, std::vector<double> &U, std::vector<double> &L,
                                 double paaRSum, int i) const {
    for (int z = 0; z < std::min(w, (i - (slide - 1)) / points); z++) {
        if (segUpdateList.at(z) <= gama) {
            segUpdateList.at(z)++;
            double paa = paaRSum / points;
            U.at(z) = std::max(paa, U.at(z));
            L.at(z) = std::min(paa, L.at(z));

        }
    }
};


std::vector<int> EnvelopGen::SearchEnvelop(MySQL *const mySql, std::deque<OneBar *> *oneBars) {

    double maxDouble = std::numeric_limits<double>::max();
    double minDouble = -std::numeric_limits<double>::max();
    std::vector<int> segUpdateList(w, 0);
    std::vector<double> U(w, minDouble);
    std::vector<double> L(w, maxDouble);

    // ComputeEnvelop(oneBars, 0, segUpdateList, U, L);


    //std::vector<int> indexes = mySql->findEnvelop(U, L);
    //for (int index : indexes) {
    //    std::cout << index << std::endl;

    //}
}

//// PSEODU CODE

//int w ← b` max /sc ;
//int segUpdateList[S] ← {0,...,0};
//float U [w] ← {−∞, ..., −∞}, L[w] ← {∞, ..., ∞};

//if |D| − (i − 1) ≥ ` min then
//float paaRSum ← 0;
//// iterate the master series.
//for i ← a to min(|D|,a + ` max + γ) do
//// running sum of paa segment
//paaRSum ← paaRSum + D[i];
//if (j-a) > s then
//paaRSum ← paaRSum - D[i-s];
//for z ← 1 to min(b[i-(a-1)] / sc,w) do
//if segUpdatedList[z] ≤ γ then
//segUpdateList[z] ++;
//float paa ← (paaRSum / s);
//L[z] ← min(paa, L[z]);
//U [z] ← max(paa, U [z]);
//uENV ← [iSAX(L),iSAX(U )];
//else
//uENV ← ∅;
