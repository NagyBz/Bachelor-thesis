#include "onebar.h"
#include <iostream>
#include <cmath>

//OneBar::OneBar(unsigned id,
//               std::string symbol,
//               std::string date,
//               std::string time,
//	       double open,
//	       double high,
//	       double low,
//	       double close,
//	       unsigned vol) :
//  id(id),
//  symbol(symbol),
//  date(date),
//  time(time),
//  open(open),
//  high(high),
//  low(low),
//  close(close),
//  vol(vol) {};

//Bar with computed members
OneBar::OneBar(unsigned id,
   std::string symbol,
   std::string date,
   std::string time,
   double open,
   double high,
   double low,
   double close,
   unsigned vol,
   unsigned openHash,
   unsigned highHash,
   unsigned lowHash,
   unsigned closeHash,
   double maxRange,
   double trueRange,
   unsigned pivotPocket,
   double change):
    id(id),
    symbol(symbol),
    date(date),
    time(time),
    open(open),
    high(high),
    low(low),
    close(close),
    vol(vol),
    openHash(openHash),
    highHash(highHash),
    lowHash(lowHash),
    closeHash(closeHash),
    maxRange(maxRange),
    trueRange(trueRange),
    pivotPocket(pivotPocket),
    change(change)
    {}

bool OneBar::operator==(const OneBar& rhs) const {
  //(priblizne) rovnaky bar ma rovnaky hash
  //(priblizne) rovnaky max range vratane smeru

  const int delta = 1; //pre level, +/- delta, 1 alebo 2
  const double deltaMaxRange = 0.02; //v %
  
  const OneBar lhs = *this;

  int openHashDiff = std::abs((int) lhs.getOpenHash() - (int) rhs.getOpenHash());
  int highHashDiff =  std::abs((int) lhs.getHighHash() - (int) rhs.getHighHash());
  int lowHashDiff =  std::abs((int) lhs.getLowHash() - (int) rhs.getLowHash());
  int closeHashDiff =  std::abs((int) lhs.getCloseHash() - (int) rhs.getCloseHash());

  const double maxRangeDiff = std::abs(lhs.getMaxRange() - rhs.getMaxRange());

    return openHashDiff <= delta &&
           highHashDiff <= delta &&
           lowHashDiff <= delta &&
           closeHashDiff <= delta &&
           maxRangeDiff <= deltaMaxRange;
}

bool OneBar::operator!=(const OneBar& rhs) const {
  return !(*this==rhs);
}

unsigned OneBar::getId() const {
  return id;
}

std::string OneBar::getSymbol() const {
  return symbol;
}

std::string OneBar::getDate() const {
  return date;
}

std::string OneBar::getTime() const {
  return time;
}

double OneBar::getOpen() const {
  return open;
}

double OneBar::getHigh() const {
  return high;
}

double OneBar::getLow() const {
  return low;
}

double OneBar::getClose() const {
  return close;
}

unsigned OneBar::getVol() const {
  return vol;
}

double OneBar::getMaxRange() const {
  return maxRange;
}

void OneBar::setMaxRange(double maxRange) {
  this->maxRange = maxRange;
}

unsigned OneBar::getOpenHash() const {
  return openHash;
}

void OneBar::setOpenHash(unsigned openHash) {
  this->openHash = openHash;
}

unsigned OneBar::getHighHash() const {
  return highHash;
}

void OneBar::setHighHash(unsigned highHash) {
  this->highHash = highHash;
}

unsigned OneBar::getLowHash() const {
  return lowHash;
}

void OneBar::setLowHash(unsigned lowHash) {
  this->lowHash = lowHash;
}

unsigned OneBar::getCloseHash() const {
  return closeHash;
}

void OneBar::setCloseHash(unsigned closeHash) {
  this->closeHash = closeHash;
}

void OneBar::setHash(unsigned openHash,
             unsigned highHash,
             unsigned lowHash,
             unsigned closeHash) {
  this->openHash = openHash;
  this->highHash = highHash;
  this->lowHash = lowHash;
  this->closeHash = closeHash;
}

unsigned OneBar::getPivotPocket() const {
  return pivotPocket;
}

void OneBar::setPivotPocket(unsigned pivotPocket) {
  this->pivotPocket = pivotPocket;
}

double OneBar::getTrueRange() const {
  return trueRange;
}

void OneBar::setTrueRange(double trueRange) {
  this->trueRange = trueRange;
}

double OneBar::getChange() const {
  return change;
}

void OneBar::setChange(double change) {
  this->change = change;
}

void OneBar::print() {
  std::cout << id << ", "
            << symbol << ", "
	    << date << ", "
	    << time << ", "
	    << open << ", "
	    << high << ", "
	    << low << ", "
	    << close << ", "
	    << vol << ", "
	    << openHash << ", "
	    << highHash << ", "
	    << lowHash << ", "
	    << closeHash << ", "
	    << maxRange << ", "
	    << trueRange << ", "
	    << pivotPocket << ", "
	    << change;

  std::cout << std::endl;
}

OneBar::OneBar(unsigned int id, std::string symbol, std::string date, std::string time, double open, double high,
               double low, double close, unsigned int vol):
        id(id),
        symbol(symbol),
        date(date),
        time(time),
        open(open),
        high(high),
        low(low),
        close(close),
        vol(vol){

}
