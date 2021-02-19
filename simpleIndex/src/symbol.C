#include "symbol.h"
#include "onebar.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <chrono>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::deque;

Symbol::Symbol(string symbol) : symbol(symbol) {
    symbolList = new deque<OneBar *>;
}

Symbol::~Symbol() {
    for (auto oneBar: *symbolList) {
        delete oneBar;
    }

    delete symbolList;
}

auto Symbol::size() {
    return symbolList->size();
}

void Symbol::add(OneBar *oneBar) {
    symbolList->push_back(oneBar);
}

void Symbol::print() {
    for (auto &oneBar: *symbolList) {
        oneBar->print();
    }
}

std::string Symbol::getSymbol() const {
    return symbol;
}

std::deque<OneBar *> *Symbol::getList() const {
    return symbolList;
}

bool Symbol::computePivotPocket(unsigned period, double multiplier) {
    auto start0 = symbolList->begin();
    auto start = symbolList->begin();
    auto end = symbolList->end();
    decltype(start) maxVol;
    OneBar *currentBar;

    double vol;
    double maxDownVol;
    double high;
    double low;
    double close;

    advance(start, period);

    if (start > end) {
        return false;
    }

    while (start != end) {
        maxVol = max_element(start0,
                             start,
                             [](OneBar *&a, OneBar *&b) -> bool {//lambda comparator
                                 return a->getVol() < b->getVol() &&
                                        b->getChange() < 0.0;//side effect
                             });

        currentBar = *start;

        if ((*maxVol)->getChange() >= 0.0) {//first item for comparison not checked
            currentBar->setPivotPocket(0);

        } else {
            vol = currentBar->getVol();
            high = currentBar->getHigh();
            low = currentBar->getLow();
            close = currentBar->getClose();

            maxDownVol = (*maxVol)->getVol();

            //pivot pocket criteria
            if (vol > multiplier * maxDownVol && //volume greater than down volume (by multiplier)
                currentBar->getChange() > 0.0 && //positive action
                (high + low) / 2.0 > close) { //positive close

                currentBar->setPivotPocket(1);

            } else {//not pivot pocket
                currentBar->setPivotPocket(0);
            }
        }

        ++start0;
        ++start;
    }

    return true;
}

//maxRange je pohyb od prevClose k high alebo low, ktory ja vacsi
//ak je pohyb od prevClose smerom nadol je maxRange zaporny, inac je kladny
void Symbol::computeMaxRange() {
    auto start = symbolList->begin();
    auto end = symbolList->end();
    auto prev = start;

    ++start; //start from 2nd position
    OneBar *currentBar;

    double maxRange;
    double prevClose;

    double highRange;
    double lowRange;

    while (start != end) {
        prevClose = (*prev)->getClose();
        currentBar = *start;

        highRange = std::abs(prevClose - currentBar->getHigh());
        lowRange = std::abs(prevClose - currentBar->getLow());

        if (lowRange > highRange) {
            maxRange = -std::max(highRange, lowRange);
        } else {
            maxRange = std::max(highRange, lowRange);
        }

        currentBar->setMaxRange(maxRange / prevClose * 100.0);

        prev = start;
        ++start;
    }
}

void Symbol::computeHash(int levels) {
    auto start = symbolList->begin();
    auto end = symbolList->end();
    auto prev = start;
    ++start; //start from 2nd position
    OneBar *currentBar;

    double prevClose;
    double open;
    double high;
    double low;
    double close;

    double level;
    double trueRange;
    double openDiff;
    double highDiff;
    double lowDiff;
    double closeDiff;

    while (start != end) {
        prevClose = (*prev)->getClose();
        currentBar = *start;
        open = currentBar->getOpen();
        high = currentBar->getHigh();
        low = currentBar->getLow();
        close = currentBar->getClose();

        if (prevClose > high) {//down day
            trueRange = prevClose - low;

            openDiff = prevClose - open;
            highDiff = prevClose - high;
            lowDiff = prevClose - low;
            closeDiff = prevClose - close;

        } else if (prevClose < low) {//up day
            trueRange = high - prevClose;

            openDiff = open - prevClose;
            highDiff = high - prevClose;
            lowDiff = low - prevClose;
            closeDiff = close - prevClose;

        } else {//prevClose between high and low
            trueRange = high - low;

            openDiff = open - low;
            highDiff = high - low;
            lowDiff = 0.0;
            closeDiff = close - low;
        }

        currentBar->setTrueRange(trueRange);

        //aby bol level pri celych hodnotach o 1 vyssie
        trueRange += 0.00001;

        //trueRange sa rozdeli na konstantny pocet level-ov
        level = trueRange / levels;

        currentBar->setHash((unsigned) (openDiff / level),
                            (unsigned) (highDiff / level),
                            (unsigned) (lowDiff / level),
                            (unsigned) (closeDiff / level)
        );

        currentBar->setChange(close - prevClose);
        prev = start;
        ++start;
    }
}
