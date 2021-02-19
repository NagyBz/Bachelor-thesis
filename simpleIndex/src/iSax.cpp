//
// Created by martin on 22/03/2020.
//

#include <vector>
#include <bitset>
#include <iostream>
#include "onebar.h"
#include <map>
#include <cmath>
#include <breakpoints.h>
#include <limits>
#include "iSax.h"

std::vector<std::string> decToBinary(int n, int seg) {
    std::vector<std::string> number;
    for (int i = seg - 1; i >= 0; i--) {
        int num;
        int k = n >> i;
        num = k & 1 ? 1 : 0;
        number.push_back(std::to_string(num));
    }
    return number;
}

bool compareSegments(const std::string& segment1, const std::string& segment2) {
    unsigned int minLength = segment1.size() > segment2.size() ? segment2.size() : segment1.size();
    std::string sub1 = segment1.substr(0, minLength);
    std::string sub2 = segment2.substr(0, minLength);
    return !(sub1 != sub2);
}

std::string decToBinaryString(int n, int stringLength) {
    std::string number;
    for (int i = stringLength - 1; i >= 0; i--) {
        int num;
        int k = n >> i;
        num = k & 1 ? 1 : 0;
        number += (std::to_string(num));
    }
    return number;
}

iSax::iSax(int segment, int card, int length) : segments(segment), cardinality(card), length(length) {
    breakPoints.insert(std::pair<double, std::string>(0,"0"));
    for (int i = 0; i < pow(cardinality, segments); i++) {
        auto saxWord = decToBinary(i, segments);
        Node* node = new Node(saxWord, nullptr, nullptr, nullptr);
        auto tree = new binarySearchTree(node, length, segment, cardinality);
        tree->treeName = saxWord;
        trees.push_back(tree);
    }
}

std::vector<unsigned int> iSax::findData(const std::vector<double>& U, const std::vector<double>& L) {
    std::vector<std::string> wordU = generateWord(U);
    std::vector<DataIndex> nodeData;
    std::vector<std::string> wordL = generateWord(L);
    for (binarySearchTree* tree : trees) {
        if (tree->compareWords(tree->treeName, wordU)) {
            auto tempData = tree->findNode(wordU, wordL);
            nodeData.insert(nodeData.begin(), tempData.begin(), tempData.end());
        }
    }
    std::map<double, unsigned int> distances;
    unsigned int in = 0;
    std::vector<double> tempSum;
    for (const auto& index: nodeData) {
        int i = 0;
        double temp = 0;
        for (const auto& segment: index.wordL) {
            for (const auto& x: breakPoints) {
                if (compareSegments(x.second, segment) && L.at(i) != std::numeric_limits<double>::max()) {
                    temp += pow(x.first - L.at(i), 2);
                    i++;
                    break;
                }
            }
        }
        distances[sqrt(temp)] = index.data;
    }
    std::vector<unsigned int> result;
    auto iter = distances.begin();
    result.push_back(iter->second);
    iter++;
    result.push_back(iter->second);
    iter++;
    result.push_back(iter->second);
    return result;
}

void iSax::generateiSax(const std::vector<double>& envelopeU, const std::vector<double>& envelopeL,
        int index, std::deque<OneBar *> *oneBars) {
    /// generate words from U and L vectors
    std::vector<std::string> wordU = generateWord(envelopeU);
    std::vector<std::string> wordL = generateWord(envelopeL);
    /// inserting index of data and words to targeted tree
    for (binarySearchTree* tree : trees) {
        if (tree->compareWords(tree->treeName, wordU)) {
            if (!tree->insert(index, wordU, wordL, oneBars, &breakPoints, envelopeU)) {
                generateiSax(envelopeU, envelopeL, index, oneBars);
            }
            break;
        }
    }
}

std::vector<std::string> iSax::generateWord(const std::vector<double> &envelope) const {
    std::vector<std::string> word;
    for (double x: envelope) {
        if (x == -std::numeric_limits<double>::max() || x == std::numeric_limits<double>::max()) {
            word.emplace_back("");
        } else {
            /// lower_bounds to find the breakpoint for value from Envelope and generate a number for whole word from it
            auto mapPosition = breakPoints.lower_bound(x);
            /// lower_bound return .end() pointer of the targeted map if didn't find any bound
            if (mapPosition == breakPoints.end()) {
                /// if value is not from breakpoints then it the biggest one, and number will be generated as
                /// highest possible for that cardinality
                word.push_back(decToBinaryString(breakPoints.size(), breakPoints.begin()->second.size()));
            } else {
                word.emplace_back(mapPosition->second);
            }
        }
    }
    return word;
}

void iSax::printPreOrder(){
    for (binarySearchTree* tree: trees) {
        tree->printPreOrder(tree->getRoot());
    }
}



