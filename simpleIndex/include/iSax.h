//
// Created by martin on 22/03/2020.
//

#ifndef SIMPLEINDEX_ISAX_H
#define SIMPLEINDEX_ISAX_H

#include <map>
#include "binarySearchTree.h"
#include "symbol.h"


class iSax {
private:
    std::map<std::vector<unsigned int>, std::vector<unsigned int>> iSaxWords;
    std::vector<binarySearchTree*> trees{};
    int segments;
    int length;
    int cardinality;
    std::map<double, std::string> breakPoints;
public:
    iSax(int segments, int cardinality, int length);
    void generateiSax(const std::vector<double>& envelopeU, const std::vector<double>& envelopeL, int index,
            std::deque<OneBar *> *oneBars);
    void printPreOrder();

    [[nodiscard]] std::vector<std::string> generateWord(const std::vector<double> &envelope) const;

    std::vector<unsigned int> findData(const std::vector<double>& U, const std::vector<double>& L);
};


#endif //SIMPLEINDEX_ISAX_H
