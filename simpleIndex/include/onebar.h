#ifndef ONEBAR_H
#define ONEBAR_H
#include <string>


class OneBar {
private:
  //from data file
  unsigned id;
  std::string symbol;
  std::string date;
  std::string time;
  double open;
  double high;
  double low;
  double close;
  unsigned vol;

  //computed
  unsigned openHash{0};
  unsigned highHash{0};
  unsigned lowHash{0};
  unsigned closeHash{0};
  double maxRange{0.0};//max distance from previous close
  double trueRange{0.0};//standard TR
  unsigned pivotPocket{0};
  double change{0.0};

public:
  //Raw bar
  OneBar(unsigned id,
         std::string symbol,
         std::string date,
         std::string time,
         double open,
         double high,
         double low,
         double close,
         unsigned vol);

  //Bar with computed members
  OneBar(unsigned id,
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
     double change);

    bool operator==(const OneBar& rhs) const;
  bool operator!=(const OneBar& rhs) const; 

  unsigned getId() const;

  std::string getSymbol() const;

  std::string getDate() const;

  std::string getTime() const;

  double getOpen() const;

  double getHigh() const;

  double getLow() const;

  double getClose() const;

  unsigned getVol() const;

  unsigned getOpenHash() const;

  unsigned getHighHash() const;

  unsigned getLowHash() const;

  unsigned getCloseHash() const;

  unsigned getPivotPocket() const;

  double getTrueRange() const;

  double getMaxRange() const;

  double getChange() const;

  double getVolatility() const;

  void setMaxRange(double maxRange);

  void setOpenHash(unsigned openHash);

  void setHighHash(unsigned highHash);

  void setLowHash(unsigned lowHash);

  void setCloseHash(unsigned closeHash);

  void setHash(unsigned openHash,
               unsigned highHash,
               unsigned lowHash,
               unsigned closeHash);

  void setPivotPocket(unsigned pivotPocket);

  void setTrueRange(double trueRange);

  void setChange(double change);

  void print();
};

#endif // ONEBAR_H
