//
// Created by martin & balazs on 04/05/2020.
//

#include "syntheticData.h"
#include <string>

SyntheticData::SyntheticData(unsigned int id, std::string symbol, std::string date, std::string time, double value):
    id(id),
    symbol(symbol),
    date(date),
    time(time),
    value(value){
}

unsigned SyntheticData::getId() const {
    return id;
}

std::string SyntheticData::getDate() const {
    return date;
}

std::string SyntheticData::getTime() const {
    return time;
}

double SyntheticData::getValue() const {
    return value;
}

void SyntheticData::setDate(std::string date) {
    this->date = date;
}

void SyntheticData::setTime(std::string time) {
    this->time = time;
}

void SyntheticData::setValue(double value) {
    this->value = value;
}

std::string SyntheticData::getSymbol() const {
    return symbol;
}
void SyntheticData::setSymbol(std::string symbol) {
    this->symbol = symbol;
}

SyntheticData::~SyntheticData() = default;

