#include <iostream>
#include "algos.hpp"
using namespace std;

int selectNum(int lBound,int hBound){
    cout<<"["<<lBound<<"-"<<hBound<<"]\n";
    int n;
    do{
        validate(n);
        if(n<lBound or n>hBound) cout<<"Invalid option!\n";
    }while(n<lBound or n>hBound);
    cin.ignore();
    return n;
}

bool validateVector(vector<string> vec1,vector<string> vec2){
    for(auto a:vec1){
        bool valid=0;
        for(auto b:vec2) if(!a.compare(b)) valid =1;
        if(!valid) return 0;
    }
    return 1;
}

void listVector(vector<string> vec){
    cout<<"\n";
    for(auto a:vec) cout<<"# "<<a<<"\n";
}

bool yN(){
    char c;
    cout<<"[y/N]\n"<<">>";
    cin>>c;
    c=tolower(c);
    if(c=='y') return 1;
    if(c=='n') return 0;
    cin.clear();
    cin.ignore(INT_MAX,'\n');
    cout<<"Invalid option!\n";
    return yN();
}