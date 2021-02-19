//
// Created by martin on 03/04/2020.
//

#ifndef SIMPLEINDEX_BINARYSEARCHTREE_H
#define SIMPLEINDEX_BINARYSEARCHTREE_H

#include <map>
#include <utility>
#include <vector>
#include <bitset>
#include "symbol.h"

struct DataIndex {
    unsigned int data;
    std::vector<std::string> wordL;
    explicit DataIndex(std::vector<std::string> wordL, unsigned int data) :
            wordL(std::move(wordL)),
            data(data)
    {}
};

struct Node {
    std::vector<DataIndex> data;
    std::vector<std::string> word;
    Node* parent;
    Node* left;
    Node* right;
    std::deque<OneBar *> *oneBars;
    explicit Node(std::vector<std::string> word, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) :
            word(std::move(word)),
            parent(parent),
            left(left),
            right(right)
    {}
};

class binarySearchTree {
private:
    int length;
    int segments;
    int cardinality;
    Node* root;

    bool insert(Node* current, unsigned int data, const std::vector<std::string>& wordU, const std::vector<std::string>& wordL,
            std::deque<OneBar *> *oneBars, std::map<double, std::string>* breakPoints, const std::vector<double>& envelopeU);
    void findNode(Node* current, std::vector<std::string> wordL, std::vector<std::string> wordU, std::vector<DataIndex>* results);
public:
    std::vector<std::string> treeName;
    explicit binarySearchTree(Node* root, int length, int segments, int cardinality);

    ~binarySearchTree() = default;

    bool insert(unsigned int data, const std::vector<std::string>& wordU, const std::vector<std::string>& wordL, std::deque<OneBar *> *oneBars,
               std::map<double, std::string>* breakPoints, const std::vector<double>& envelopeU);
    // void update(unsigned int data,  std::deque<OneBar *> *oneBars);
    int split(Node* leaf, std::deque<OneBar *> *oneBars, std::map<double, std::string>* breakPoints, const std::vector<double>& envelopeU);
    static double getBreakPoint(std::string segment, double segmentVal, std::map<double, std::string>* breakPoints);
    void distributeData(Node* node, double breakpoint, int segment, std::vector<double>* segmentDataZ, const std::vector<double>& envelopeU) const;
    bool compareWords(const std::vector<std::string>& word1, const std::vector<std::string>& word2);
    void printPreOrder(Node* current);
    std::vector<double> meanAndSd(Node* leaf, std::deque<OneBar *> *oneBars);
    Node *getRoot() const;
    std::vector<DataIndex> findNode(std::vector<std::string> wordL, std::vector<std::string> wordU);
};


#endif //SIMPLEINDEX_BINARYSEARCHTREE_H
