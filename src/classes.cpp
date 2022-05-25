#include "specalgos.h"
#include "classes.h"
using namespace std;

string date::info(){
        string s=to_string(d)+"-"+to_string(m)+"-"+to_string(y);
        return s;
    }
void date::input(string str){
    stringstream s(str);
    string temp;
    getline(s,temp,'-');
    d=stoi(temp);
    getline(s,temp,'-');
    m=stoi(temp);
    getline(s,temp);
    y=stoi(temp);
}
bool room::hasAdditionalFeatures(){
        return (additionalFeatures.size()!=0);
    }
void room::displayInfo(){
    cout<<"\nRoom Number: "<<num;
    cout<<"\nAddress: "<<address;
    cout<<"\nType: "<<type;
    cout<<"\nPrice: "<<price<<"$";
    if(hasAdditionalFeatures()){
        cout<<"\nAdditional features:";
        listVector(additionalFeatures);
    }
    cout<<"\n";
}

void user::displayInfo(){
        cout<<"\nID: "<<ID;
        cout<<"\nName: "<<fName<<" "<<lName;
        cout<<"\nEmail: "<<address;
        cout<<"\nPhone: "<<num;
    }
void reservation::displayInfo(){
    cout<<"Room no: "<<r->num<<"\n";
    cout<<start.info()<<" - "<<end.info()<<"\n";
}

date inputDate(){
    date dat;
    cout<<"Year\n";
    do{
        validate(dat.y);
    }while(dat.y<2022);
    cout<<"Month\n";
    dat.m=selectNum(1,12);
    int febMax=(!dat.y%4)?29:28;
    if(dat.m%2){
        dat.d=selectNum(1,31);
    }
    else{
        dat.d=(dat.m==2)?selectNum(1,febMax):selectNum(1,30);
    }
    return dat;
}

int compDate(date da, date db){
    if(da.y>db.y) return 1;
    if(da.y<db.y) return -1;

    if(da.m>db.m) return 1;
    if(da.m<db.m) return -1;

    if(da.d>db.d) return 1;
    if(da.d<db.d) return -1;

    return 0;
}

double total(reservation res){
    const float tva=0.11;
    date s=res.start,e=res.end;
    int days=(e.y-s.y)*365.25+(e.m-s.m)*30.43+(e.d-s.d);
    double total=days*res.r->price;
    return total + total*tva;
}