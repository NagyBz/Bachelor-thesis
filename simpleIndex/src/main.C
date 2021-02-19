#include "mysql.h"
#include "symbol.h"
#include "onebar.h"
#include <chrono>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <random>
#include <iostream>
#include <math.h>

#include "EnvelopGen.h"
#include "syntheticData.h"

using namespace std;

void printTime(const string&& msg, auto time) {
    cout << msg << " " << std::chrono::duration_cast<std::chrono::seconds>(time).count() <<       "s" << endl;
}

int main(int argc, char *argv[]) {
    MySQL* const mySQL = new MySQL();
    Symbol* const oneSymbol = new Symbol("IBM");


//    // Generate synthetic data
//    // standard deviation affects the dispersion of generated values from the mean
//    std::normal_distribution<> d{0,1};
//    std::vector<int> vec;
//    vec.push_back(0);
//    std::deque<SyntheticData> newData;
//    std::string time = "00:00:00";
//    std::string date = "";
//    unsigned int day = 0;
//    unsigned int month = 1;
//    unsigned int year = 1000;
//    std::map<int, int> hist{};
//    for(int n=1; n<40000001; ++n) {
//        if (day < 30) {
//            day++;
//        } else {
//            day = 1;
//            if (month < 12) {
//                month++;
//            } else {
//                month = 1;
//                year++;
//            }
//        }
//        std::string sDay = "";
//        std::string sMonth = "";
//        if (day < 10) {
//            sDay = "0" + to_string(day);
//        } else {
//            sDay = to_string(day);
//        }
//        if (month < 10) {
//            sMonth = "0" + to_string(month);
//        } else {
//            sMonth = to_string(month);
//        }
//        date = to_string(year) + "-" + sMonth + "-" + sDay;
//        auto x = d(gen);
//        auto y = x + vec.at(n - 1);
//        vec.push_back(y);
//        auto* data = new SyntheticData(n - 1, "Synthetic 1", date, time, y);
//        newData.push_back(*data);
//        ++hist[vec.at(n)];
//    }
//    std::cout << newData.size() << std::endl;
//    mySQL->insertSynthetic(newData);

    mySQL->selectSynthetic(oneSymbol, 500000);
    //mySQL->selectAll(oneSymbol);

    auto *envelopGen = new EnvelopGen(12,3,3,12,2,1);
    std::cout << "Test for 40 gamma" << std::endl;

    envelopGen->genEnvelopZnorm(oneSymbol);


    delete envelopGen;

    delete oneSymbol;
    delete mySQL;
    return 0;
}
