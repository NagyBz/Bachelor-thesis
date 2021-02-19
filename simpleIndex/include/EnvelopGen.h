//
// Created by nagy on 7. 11. 2019.
//

#ifndef SIMPLEINDEX_ENVELOPGEN_H
#define SIMPLEINDEX_ENVELOPGEN_H
#include <map>
#include <vector>
#include "symbol.h"
#include "iSax.h"

class EnvelopGen {
private:
    std::map<int, std::vector<double> > LEnvelop;
    std::map<int, std::vector<double> > UEnvelop;

    int length,
        points,
        lmin,
        lmax,
        gama,
        slide,
        w;
    std::vector<double> genPaa(const std::vector<double>& oneBars);
public:
    iSax isax;
    EnvelopGen(int length, int points, int lmin, int lmax, int gama, int slide);
    virtual ~EnvelopGen();
    void createEnvelop(Symbol *oneSymbol);

    void UpdateEnvelopSegment(std::vector<int> &segUpdateList, std::vector<double> &U, std::vector<double> &L,
                              double paaRSum, int i) const;

    //void
    //ComputeEnvelop(std::deque<OneBar *> *oneBars, int j, std::vector<int> &segUpdateList, std::vector<double> &U,
    //               std::vector<double> &L) const;

    std::vector<int> SearchEnvelop(MySQL *const mySql,std::deque<OneBar *> *oneBars);
    void genEnvelopZnorm(Symbol *oneSymbol);

    void computeZnormalized(std::deque<OneBar *> *oneBars, int j, std::vector<double> &U, std::vector<double> &L,
                             std::vector<double> &PAAs) const;
    std::vector<unsigned int> findEnvelope(std::deque<OneBar *> *oneBars);
};


#endif //SIMPLEINDEX_ENVELOPGEN_H
