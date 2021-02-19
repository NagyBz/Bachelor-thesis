//
// Created by martin on 04/05/2020.
//

#ifndef SIMPLEINDEX_SYNTHETICDATA_H
#define SIMPLEINDEX_SYNTHETICDATA_H
#include <string>


class SyntheticData {
private:
    unsigned id;
    std::string symbol;
    std::string date;
    std::string time;
    double value;

public:
    virtual ~SyntheticData();

    SyntheticData(unsigned id, std::string symbol, std::string date,
                  std::string time, double value);
    unsigned getId() const;

    std::string getSymbol() const;

    std::string getDate() const;

    std::string getTime() const;

    double getValue() const;

    void setSymbol(std::string symbol);

    void setDate(std::string date);

    void setTime(std::string time);

    void setValue(double value);
};


#endif //SIMPLEINDEX_SYNTHETICDATA_H
