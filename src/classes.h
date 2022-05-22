#pragma once
#include "specalgos.h"
#include <sstream>

struct date{
    int d,m,y;
    std::string info();
    void input(std::string str);
};

struct room{
    unsigned int num;
    std::string address,type;
    double price;
    std::vector<std::string> additionalFeatures;
    bool hasAdditionalFeatures();
    void displayInfo();
};

struct user{
    std::string password;
    unsigned int ID;
    std::string fName,lName,address,num;
    void displayInfo();
};

struct reservation{
    user* u;
    room* r;
    date start,end;
    void displayInfo();
};

date inputDate();
int compDate(date da, date db);
double total(reservation res);