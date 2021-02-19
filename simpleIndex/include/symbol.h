#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include <deque>
#include <vector>
#include <set>

class OneBar;
class Region;
class Symbol {
private:
  std::string symbol;
  std::deque <OneBar*>* symbolList;

public:
  Symbol(std::string symbol);
  ~Symbol();

  auto size();

  void add(OneBar* oneBar);

  void print() ;

  [[nodiscard]] std::string getSymbol() const;

  [[nodiscard]] std::deque <OneBar*>* getList() const;

  bool computePivotPocket(unsigned period = 10,
			  double multiplier = 1.3);

  void computeMaxRange();

  void computeHash(int levels);
};

#endif // SYMBOL_H
