#include "mysql.h"
#include "symbol.h"
#include "onebar.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <numeric>
#include <cmath>

MySQL::MySQL() {
    open();
}

MySQL::~MySQL() {
    close();
}

void MySQL::open() {
    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("localhost", "finley", "password");

    /* Connect to the MySQL test database */
    con->setSchema("bigd");

    stmt = con->createStatement();
}

void MySQL::close() {
    delete res;
    delete stmt;
    delete con;
    //delete driver;
}

void MySQL::reset() {
    delete res;
    delete stmt;
    res = nullptr;
    stmt = nullptr;
}
void printTime(const std::string&& msg, auto time) {
    std::cout << msg << " " << std::chrono::duration_cast<std::chrono::seconds>(time).count() <<       "s" << std::endl;
}

void MySQL::selectAll(Symbol *oneSymbol) {
    OneBar *oneBar;
    std::chrono::steady_clock::time_point start, end;
    start = std::chrono::steady_clock::now();
    stmt = con->createStatement();
    res = stmt->executeQuery("select * from 1m" + oneSymbol->getSymbol() + " ");

    while (res->next()) {
        oneBar = new OneBar(res->getInt(1),//id
                            res->getString(2),//symbol
                            res->getString(3),//date
                            res->getString(4),//time
                            res->getDouble(5),//open
                            res->getDouble(6),//high
                            res->getDouble(7),//low
                            res->getDouble(8),//close
                            res->getInt(9),//vol
                            res->getInt(10),//openHash
                            res->getInt(11),//highHash
                            res->getInt(12),//lowHash
                            res->getInt(13),//closeHash
                            res->getDouble(14),//maxRange
                            res->getDouble(15),//trueRange
                            res->getInt(16),//pivotPocket
                            res->getDouble(17)//change
        );
        oneSymbol->add(oneBar); //add to list
    }
    end = std::chrono::steady_clock::now();
    printTime("select  time: ", end - start );
    reset();
}

void MySQL::insertInvSax(const std::vector<int> &invSaxWords) {
    stmt = con->createStatement();
    int position = 0;
    std::string s{};
    stmt->execute("START TRANSACTION");
    s = "INSERT INTO InvSaxTest (iSax, candleId) VALUES ";
    for (int invSaxWord: invSaxWords) {
        s += "(" + std::to_string(invSaxWord) + ", " + std::to_string(position) + "),";
        position += 60;
    }
    s.back() = ';';
    stmt->executeUpdate(s);
    stmt->execute("COMMIT");

    reset();
}

void MySQL::insertSynthetic(const std::deque<SyntheticData>& newData) {
    stmt = con->createStatement();

    std::string s{};
    for (int i = 0; i < newData.size(); i += 100000) {
        stmt->execute("START TRANSACTION");
        s = "INSERT INTO generated1 (symbol, date, time, value) VALUES ";
        for (int j = i; j < i + 100000; j++) {
            s += "('" + newData.at(j).getSymbol() + "', '" + newData.at(j).getDate() +
                "', '" + newData.at(j).getTime() + "', " + std::to_string(newData.at(j).getValue()) + "),";
        }
        s.back() = ';';
        stmt->executeUpdate(s);
        stmt->execute("COMMIT");
    }

    reset();
}

void MySQL::selectSynthetic(Symbol *oneSymbol, int limit) {
    OneBar* sData;


    std::chrono::steady_clock::time_point start, end;
    start = std::chrono::steady_clock::now();
    stmt = con->createStatement();
    res = stmt->executeQuery("select * from generated1 order by id asc limit " + std::to_string(limit));

    while (res->next()) {
        sData = new OneBar(res->getInt(1),//id
                            res->getString(2),//symbol
                            res->getString(3),//date
                            res->getString(4),//time
                            res->getDouble(5),
                            res->getDouble(5),
                           res->getDouble(5),
                           res->getDouble(5),
                            res->getInt(5)
        );
        oneSymbol->add(sData); //add to list
    }
    end = std::chrono::steady_clock::now();
    printTime("select  time: " ,end - start );
    reset();
}

void MySQL::insertLEnvelop(std::map<int, std::vector<double> >  & LEnvelop,int segNum) {
    stmt = con->createStatement();
    std::string s{};
    stmt->execute("START TRANSACTION");

    CreateLEnveloptable(segNum);

    s = "INSERT INTO LEnvelops(row_id ";
    for(int i=0;i<segNum;i++){
        s+= ",env" + std::to_string(i);

    }
    s+= ") VALUES ";
    std::map<int,std::vector<double> >::iterator it;
    for (it=LEnvelop.begin();it!=LEnvelop.end();it++ ) {
        s += "(" + std::to_string(it->first);
        for(int i=0;i<segNum;i++){
            s+= "," + std::to_string(it->second.at(i));

        }
        s+="),";
    }
    s.back() = ';';
    stmt->executeUpdate(s);
    stmt->execute("COMMIT");
    reset();
}

void MySQL::CreateLEnveloptable(int segNum) const {
    std::string s1{};
    s1="drop table LEnvelops;";
    stmt->executeUpdate(s1);
    std::string s2{};
    s2=" create table LEnvelops(LEnv_id int auto_increment primary key,row_id int,";
       for(int i=0;i<segNum;i++){
           s2+="env";
           s2+=std::to_string(i);
           s2+=" double";
           if(i<segNum-1){
               s2+=",";
           }
       }
       s2+=");";
    stmt->executeUpdate(s2);
}

void MySQL::insertUEnvelop(std::map<int, std::vector<double> >  & UEnvelop,int segNum) {
    stmt = con->createStatement();

    std::string s{};
    stmt->execute("START TRANSACTION");

    CreateUEnvelopTable(segNum);

    s = "INSERT INTO UEnvelops(row_id ";
    for(int i=0;i<segNum;i++){
        s+= ",env" + std::to_string(i);

    }
    s+= ") VALUES ";

    std::map<int,std::vector<double> >::iterator it;
    for (it=UEnvelop.begin();it!=UEnvelop.end();it++ ) {
        s += "(" + std::to_string(it->first);
        for(int i=0;i<segNum;i++){
             s+= "," + std::to_string(it->second.at(i));

        }
        s+="),";


    }
    s.back() = ';';
    stmt->executeUpdate(s);
    stmt->execute("COMMIT");
    reset();
}

void MySQL::CreateUEnvelopTable(int segNum) const {
    std::string s1{};
    std::string s2{};
    s1="drop table UEnvelops;";
    stmt->executeUpdate(s1);
    s2=" create table UEnvelops(UEnv_id int auto_increment primary key,row_id int,";

    for(int i=0;i<segNum;i++){
        s2+="env";
        s2+=std::to_string(i);
        s2+=" double";
        if(i<segNum-1){
            s2+=",";

        }
    }
    s2+=");";

    stmt->executeUpdate(s2);
}

std::vector<int> MySQL::findEnvelop(std::vector<double > Lenvelop,std::vector<double > Uenvelop){
    stmt = con->createStatement();
    std:: string s{};
    std::vector<int> indexes;

    stmt->execute("START TRANSACTION");
    s = "SELECT l.row_id from UEnvelops as u join LEnvelops as l on l.row_id=u.row_id where ";
    for (int i= 0;i<Lenvelop.size();i++){
        if(i!=0){
            s+=" and ";
        }
        s+=     "u.env"+std::to_string(i)+"="+ std::to_string(Lenvelop.at(i)) ;

    }
    for (int i= 0;i<Uenvelop.size();i++){

        s+=" and ";
        s+=     "l.env"+std::to_string(i)+"="+ std::to_string(Uenvelop.at(i)) ;

    }


    res= stmt->executeQuery(s);
    stmt->execute("COMMIT");

    while (res->next()){
        indexes.push_back(res->getInt(1));
        std::cout<<res->getInt(1)<<std::endl;
    }

    reset();
    return indexes;
}


void MySQL::orderInvSax() {
    stmt = con->createStatement();
    std::string s{};

    stmt->execute("START TRANSACTION");
    s = "ALTER TABLE InvSaxTest ORDER BY iSax";

    stmt->executeUpdate(s);
    stmt->execute("COMMIT");

    reset();
}

// void MySQL::zNormalizeHigh(Symbol* oneSymbol) {
//     double sum = 0.0;
//     for (OneBar* bar: *oneSymbol->getList()) {
//         sum += bar->getHigh();
//     }
//     int size = oneSymbol->getList()->size();
//     double average = sum / size;
//     double body = 0.0;
//     for (OneBar* bar: *oneSymbol->getList()) {
//         body += pow(bar->getHigh() - average, 2);
//     }
//     double sd = pow((body/size),0.5);
//     std::cout << sum << std::endl;
//
//     for (OneBar* bar: *oneSymbol->getList()) {
//         bar->setZNormMax(((bar->getHigh() - average)/sd));
//     }
//
// }

void MySQL::update(Symbol *oneSymbol) {
    std::string s{};
    stmt = con->createStatement();
    stmt->execute("START TRANSACTION");

    for (auto i: *oneSymbol->getList()) {
        s.clear();
        s += "UPDATE 1m" + oneSymbol->getSymbol() + " SET openHash = ";

        s += std::to_string(i->getOpenHash());
        s += ", highHash = ";
        s += std::to_string(i->getHighHash());
        s += ", lowHash = ";
        s += std::to_string(i->getLowHash());
        s += ", closeHash = ";
        s += std::to_string(i->getCloseHash());
        s += ", maxRange = ";
        s += std::to_string(i->getMaxRange());
        s += ", trueRange = ";
        s += std::to_string(i->getTrueRange());
        s += ", pivotPocket = ";
        s += std::to_string(i->getPivotPocket());
        s += ", `change` = ";
        s += std::to_string(i->getChange());
        //s += ", zNormHigh = ";
        //s += std::to_string(i->getZNormMax());
        s += " WHERE id = ";
        s += std::to_string(i->getId());

        stmt->executeUpdate(s);
    }

    //tu by bolo vhodne overit, ci to je naozaj 1 transakcia
    stmt->execute("COMMIT");

    reset();
}

void MySQL::filterRows(Symbol *oneSymbol) {
    stmt = con->createStatement();
    stmt->execute("START TRANSACTION");
    stmt->executeUpdate("DELETE FROM 1m" +
                        oneSymbol->getSymbol() +
                        " WHERE time NOT BETWEEN '9:30:00' AND '15:59:00' ");
    stmt->execute("COMMIT");

    reset();
}

OneBar *MySQL::allocateBar() {
    return new OneBar(res->getInt(1),//id
                      res->getString(2),//symbol
                      res->getString(3),//date
                      res->getString(4),//time
                      res->getDouble(5),//open
                      res->getDouble(6),//high
                      res->getDouble(7),//low
                      res->getDouble(8),//close
                      res->getInt(9),//vol
                      res->getInt(10),//openHash
                      res->getInt(11),//highHash
                      res->getInt(12),//lowHash
                      res->getInt(13),//closeHash
                      res->getDouble(14),//maxRange
                      res->getDouble(15),//trueRange
                      res->getInt(16),//pivotPocket
                      res->getDouble(17)//change   stmt->executeUpdate(s2);
    );
}


