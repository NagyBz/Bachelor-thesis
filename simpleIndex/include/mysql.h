#ifndef MYSQL_H
#define MYSQL_H

#include <string>
#include <deque>
#include <set>
#include <map>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <string>
#include <vector>
#include "syntheticData.h"

class OneBar;
class Symbol;
class Region;
class SymbolSet;

class MySQL {
private:
  //sql api
  sql::Driver* driver{nullptr};
  sql::Connection* con{nullptr};
  sql::Statement* stmt{nullptr};
  sql::ResultSet* res{nullptr};

  void open();

  void close();

  void reset();

  void filterRows(Symbol* oneSymbol);

  OneBar* allocateBar();

public:
  MySQL();
  ~MySQL();

  void selectAll(Symbol* oneSymbol);
  void update(Symbol* oneSymbol);
  void insertInvSax(const std::vector<int>& invSaxWords);
  void orderInvSax();
  void insertSynthetic(const std::deque<SyntheticData>& newData);
  void selectSynthetic(Symbol *oneSymbol, int limit);


  void insertLEnvelop(std::map<int, std::vector<double> > & LEnvelop,int segNum);
  void insertUEnvelop(std::map<int, std::vector<double> > & UEnvelop,int segNum);

  // void zNormalizeHigh(Symbol* oneSymbol);

  std::vector<int> findEnvelop(std::vector<double > Lenvelop,std::vector<double > Uenvelop);


    void CreateUEnvelopTable(int segNum) const;

    void CreateLEnveloptable(int segNum) const;
};

#endif // MYSQL_H
