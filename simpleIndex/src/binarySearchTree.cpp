//
// Created by martin on 03/04/2020.
//

#include "binarySearchTree.h"
#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <vector>
#include "onebar.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include "breakpoints.h"

binarySearchTree::binarySearchTree(Node* root, int length, int segments, int cardinality) : root(root), length(length),
segments(segments), cardinality(cardinality) {}

std::string decToBinaryStr(int n, int stringLength) {
    std::string number;
    for (int i = stringLength - 1; i >= 0; i--) {
        int num;
        int k = n >> i;
        num = k & 1 ? 1 : 0;
        number += (std::to_string(num));
    }
    return number;
}

bool binarySearchTree::compareWords(const std::vector<std::string>& word1, const std::vector<std::string>& word2) {
    for (int i = 0; i < word1.size(); i++) {
        unsigned int minLength = word1.at(i).size() > word2.at(i).size() ? word2.at(i).size() : word1.at(i).size();
        std::string sub1 = word1.at(i).substr(0, minLength);
        std::string sub2 = word2.at(i).substr(0, minLength);
        if (sub1 != sub2) {
            return false;
        }
    }
    return true;
}

std::vector<double> binarySearchTree::meanAndSd(Node* leaf, std::deque<OneBar *> *oneBars) {
    double mean;
    double sdBody = 0;
    std::vector<double> values;
    std::vector<double> zNormValues;
    for (auto vectorData: leaf->data) {
        for (int i = 0; i < length; i++) {
                values.push_back(oneBars->at(vectorData.data + i)->getHigh());
        }
    }
//    for (int j = 0; j < leaf->data.size(); j++ ) {
//        for (int i = 0; i < length; i++) {
//            values.push_back(oneBars->at(i)->getHigh());
//        }
//    }
    mean = (std::accumulate(values.begin(), values.end(), 0.0)) / values.size();
    for (double el: values) {
        sdBody += pow(el  - mean, 2);
    }
    double sd = pow((sdBody/values.size()), 0.5);
    zNormValues.reserve(values.size());
    for (double v: values) {
        zNormValues.push_back((v - mean)/sd);
    }
    return zNormValues;
}

bool binarySearchTree::insert(Node* current, unsigned int data, const std::vector<std::string>& wordU,
        const std::vector<std::string>& wordL, std::deque<OneBar *> *oneBars, std::map<double, std::string>* breakPoints,
                              const std::vector<double>& envelopeU) {
    if (!current->left && !current->right && current->data.size() < 500) {
        auto* tempData = new DataIndex(wordL, data);
        current->data.push_back(*tempData);
        // delete tempData;
        return true;
    }
    else if (current->left && compareWords(wordU, current->left->word)) {
            return insert(current->left, data, wordU, wordL, oneBars, breakPoints, envelopeU);
    } else if (current->right && compareWords(wordU, current->right->word)) {
        return insert(current->right, data, wordU, wordL, oneBars, breakPoints, envelopeU);
    } else {
        //insert(current, data, word, oneBars, breakPoints);
        split(current, oneBars, breakPoints, envelopeU);
        return false;
    }
}

void binarySearchTree::distributeData(Node* node, double breakpoint, int segment, std::vector<double>* segmentDataZ,
        const std::vector<double>& envelopeU) const {
    unsigned int o = 0;
    for (const auto& index: node->data) {
        std::vector<double> values;
        for (unsigned int j = o + segment*length/segments; j <= o + segment*length/segments + length/segments - 1;
        j++) {
            values.push_back(segmentDataZ->at(j));
        }

        double meanSegment = (std::accumulate(values.begin(), values.end(), 0.0)) / values.size();
        if (meanSegment < breakpoint) {
            node->left->data.push_back(index);
        } else {
            node->right->data.push_back(index);
        }
        o += length;
    }
    node->data.clear();
}

bool binarySearchTree::insert(unsigned int data, const std::vector<std::string>& wordU, const std::vector<std::string>& wordL,
         std::deque<OneBar *> *oneBars, std::map<double, std::string>* breakPoints, const std::vector<double>& envelopeU) {
    return insert(root, data, std::move(wordU), wordL, oneBars, breakPoints, envelopeU);
}

int binarySearchTree::split(Node* leaf, std::deque<OneBar *> *oneBars, std::map<double, std::string>* breakPoints,
                            const std::vector<double>& envelopeU) {
    int segmentToSplit = 0;
    double distance = std::numeric_limits<double>::max();
    double finalBreakpoint = -std::numeric_limits<double>::max();
    std::vector<double> segmentDataZFinal;
    std::vector<double> zNormalizedWord = meanAndSd(leaf, oneBars);

    for (int i = 0; i < segments; i++) {
        std::vector<double> values;
        double sdBody = 0.0;
        unsigned int o = 0;
        for (auto vectorData: leaf->data) {
            for (unsigned int j = o + i*length/segments; j <= o + i*length/segments + length/segments - 1; j++) {
                values.push_back(zNormalizedWord.at(j));
            }
            o += length;
        }
        double meanSegment = (std::accumulate(values.begin(), values.end(), 0.0)) / values.size();
        double meanSegment2 = envelopeU[i];
        for (double el: values) {
            double pom = pow(el  - meanSegment, 2);
            pom = round(pom * 1000);
            sdBody += pom / 1000;
        }
        double sd = pow((sdBody/values.size()), 0.5);

        double b = getBreakPoint(leaf->word.at(i), meanSegment, breakPoints);

        if ((meanSegment + 3 * sd) > b && b > (meanSegment - 3 * sd)) {
            if (distance > std::abs(b - meanSegment)) {
                distance = std::abs(b - meanSegment);
                segmentToSplit = i;
                finalBreakpoint = b;
            }
        } else if (std::abs(b - meanSegment) < std::abs(finalBreakpoint - meanSegment)) {
            finalBreakpoint = b;
        }
    }
    std::vector<std::string> oldWord = leaf->word;
    std::vector<std::string> wordLeft = oldWord;
    std::vector<std::string> wordRight = oldWord;

    wordLeft.at(segmentToSplit) = wordLeft.at(segmentToSplit) += "0";
    wordRight.at(segmentToSplit) = wordRight.at(segmentToSplit) += "1";

    leaf->left = new Node(wordLeft, nullptr, nullptr, nullptr);
    leaf->right = new Node(wordRight, nullptr, nullptr, nullptr);

    distributeData(leaf, finalBreakpoint, segmentToSplit, &zNormalizedWord, envelopeU);
    int newCardinality = (int)pow(2, wordLeft.at(segmentToSplit).size());

    auto newBreakpoints = Breakpoints::generateBreakpointsDynamic(newCardinality);
    if (newBreakpoints.size() > breakPoints->size()) {
        cardinality = newCardinality;
        breakPoints->clear();
        int i = 0;
        for (double breakpoint: newBreakpoints) {
            breakPoints->insert(std::pair<double, std::string>(breakpoint,
                    decToBinaryStr(i, (int)log2((double)newCardinality))));
            i++;
        }
    }
}

double binarySearchTree::getBreakPoint(std::string segment, double segmentVal,
        std::map<double, std::string>* breakPoints) {
    std::vector<double> keys;
    for(auto breakPoint : *breakPoints) {
        keys.push_back(breakPoint.first);
    }
    auto newBreakpoints = Breakpoints::generateBreakpointsDynamic(pow(2, segment.size() + 1));
    double resultingBreakpoint;
    double distance = std::numeric_limits<double>::max();
    for (double newBreakpoint: newBreakpoints) {
        if (std::find(keys.begin(), keys.end(), newBreakpoint) == keys.end() &&
        distance > std::abs(newBreakpoint - segmentVal)) {
            resultingBreakpoint = newBreakpoint;
            distance = std::abs(newBreakpoint - segmentVal);
        }
    }
    return resultingBreakpoint;
}

void binarySearchTree::printPreOrder(Node* current) {
    if(current){
        for (std::string symbol: current->word) {
            std::cout << symbol << " ";
        }
        for (auto d: current->data) {
            std::cout << d.data << ", " ;
        }
        std::cout << "-" << std::endl;
        printPreOrder(current->left);
        printPreOrder(current->right);
    }
    std::cout << "------" << std::endl;
}

void binarySearchTree::findNode(Node* current, std::vector<std::string> wordU,
        std::vector<std::string> wordL, std::vector<DataIndex>* results) {
    if (current) {
        if (!current->left && !current->right && compareWords(wordU, current->word)) {
            auto currentData = current->data;
            std::vector<unsigned int> result;
            std::vector<unsigned int> result2;
            results->insert(results->end(), currentData.begin(), currentData.end());
        }
        findNode(current->left, wordU, wordL, results);
        findNode(current->right, wordU, wordL, results);
    }
}

std::vector<DataIndex> binarySearchTree::findNode(std::vector<std::string> wordU, std::vector<std::string> wordL) {
    std::vector<DataIndex> results;
    findNode(root, wordU, wordL, &results);
    return results;
}

Node *binarySearchTree::getRoot() const {
    return root;
}

