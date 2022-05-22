#include "dbops.h"
#include "globalvariables.h"
#include <fstream>
using namespace std;

size_t fileSize(string file){
    size_t s=0;
    string line;
    fin.open(file);
    while(getline(fin,line))s++;
    fin.close();
    return s;
}

size_t max(string file){
    size_t s=fileSize(file);
    if (!s) return 0;
    string temp;
    fin.open(file);
    for(size_t i=1;i<s;i++) getline(fin,temp);
    getline(fin,temp,',');
    fin.close();
    return stoi(temp);
}

room* findRoom(unsigned int rnum){
    for(auto& a:rVec){
        room* p=&a;
        if(p->num==rnum)return p;
    }
    return nullptr;
}

user* findUID(unsigned int uID){
    for(auto& a:uVec){
        user* p=&a;
        if(p->ID==uID)return p;
    }
    return nullptr;
}

user* findEmail(string email){
    for(auto& a:uVec){
        user* p=&a;
        if(!p->address.compare(email)) return p;
    }
    return nullptr;
}

reservation* findRes(unsigned int uID,unsigned int rNum){
    for(auto& a:resVec){
        reservation* p=&a;
        if(p->u->ID==uID && p->r->num==rNum) return p;
    }
    return nullptr;
}

int findString(string* arr,size_t s,string target){
    for(size_t i=0;i<s;i++){
        if(!arr[i].compare(target)) return i;
    }
    return -1;
}

void vectorizeString(string line,vector<string>& vec){
    stringstream s(line);
    string temp;
    while(getline(s,temp,',')) {
        bool exists=0;
        for(auto a:vec) if(!a.compare(temp)) exists=1;
        if(exists)continue;
        vec.push_back(temp);
    }
}

void addToVector(vector<string>& vec){
    cout<<"Enter elements separated by ','\n>>";
    string line;
    getline(cin,line);
    vectorizeString(line,vec);
}

void assignFeatures(room* r){
    listVector(features);
    addToVector(r->additionalFeatures);
    if(validateVector(r->additionalFeatures,features)) cout<<"Features added successfully.\n";
    else{
        cout<<"Invalid feature detected!\n"; 
        assignFeatures(r);
    }
}

void sortRooms(){
    size_t s=rVec.size();
    double* prices=new double[s];
    for(size_t i=0;i<s;i++){
        prices[i]=rVec[i].price;
    }
    compSort(prices,s);
    for(size_t i=0;i<s;i++) swapT(rVec[i],rVec[findT(prices, s, rVec[i].price)]);
    delete [] prices;
}

void sortRes(){
    size_t s=resVec.size();
    double* prices=new double[s];
    for(size_t i=0;i<s;i++){
        prices[i]=resVec[i].r->price;
    }
    compSort(prices,s);
    for(size_t i=0;i<s;i++) swapT(resVec[i],resVec[findT(prices,s,resVec[i].r->price)]);
    delete [] prices;
}

//----------Add entry----------

void addRoom(){
    room r;
    bool exists;
    cout<<"Room Number\n";
    do{
        exists=0;
        validate(r.num);
        for(size_t i=0;i<rVec.size();i++){
            if(r.num==rVec[i].num){
                exists=1;
                cout<<"Room taken!\n";
            }
        }
    }while(exists);
    exists=0;
    cout<<"Location\n";
    r.address=locations[selectChoice(&locations[0],locations.size())-1];
    cout<<"Type\n";
    r.type=types[selectChoice(&types[0],types.size())-1];
    cout<<"Price\n";
    validate(r.price);
    if(features.size()){
        cout<<"Do you want to assign additional features to the room?";
        if(yN()){
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            assignFeatures(&r);
        }
    }
    rVec.push_back(r);
    cout<<"Room added successfully.\n";
}

void addUser(){
    cout<<"\nAccount Creation\n";
    user u;
    size_t s=fileSize("data/user.csv");
    u.ID=(s)?max("data/user.csv")+1:1;
    cout<<"First Name\n";
    u.fName=validateName();
    cout<<"Last Name\n";
    u.lName=validateName();
    bool exists;
    cout<<"Email Address\n";
    do{
        exists=0;
        u.address=validateEmail();
        for(auto v:uVec){
            if(u.address.compare(v.address)==0){
                exists=1;
                cout<<"Email Address taken!\n";
                break;
            }
        }
    }while(exists);
    cout<<"Phone number\n";
    do{
        exists=0;
        u.num=validatePhone();
        for(auto v:uVec){
            if(u.num.compare(v.num)==0){
                exists=1;
                cout<<"Phone number taken!\n";
                break;
            }
        }
    }while(exists);
    cout<<"Password\n";
    u.password=getPass();
    uVec.push_back(u);
    cout<<"User created successfully.\n";
}

void addReservation(user* u){
    cout<<"Enter dates between which you want a room reserved.\n";
    cout<<"Date 1\n";
    date da=inputDate();
    cout<<"Date 2\n";
    date db=inputDate();
    date s=(compDate(da,db)==-1)?da:db;
    date e=(compDate(da,db)==1)?da:db;
    vector<unsigned int> rNums;
    for(auto r:rVec){
        bool available=1;
        for(auto res:resVec){
            if(!(res.r->num==r.num))continue;
            if(compDate(s,res.start)>=0 && compDate(s,res.end)<=0 || compDate(e,res.start)>=0 && compDate(e,res.end)<=0) {
                available=0;
                break;
            }
        }
        if(available){
            rNums.push_back(r.num);
            r.displayInfo();
            cout<<"\n";
        }
    }
    if(!rNums.size()) return;
    cout<<"Do you wish to continue? ";
    if(!yN()) return;
    room* r;
    do{
        cout<<"Room number\n";
        unsigned int rnum;
        validate(rnum);
        r=findRoom(rnum);
        if(!r) {
            cout<<"Room doesn't exist!\n";
            r=nullptr;
        }
        else if(findT(&rNums[0],rNums.size(),r->num)==-1){
            cout<<"Room unavailable!\n";
            r=nullptr;
        }
    }while(!r);
    if(findRes(u->ID,r->num)){
        cout<<"Room already reserved!\n";
        return;
    }
    resVec.push_back({u,r,s,e});
    cout<<"Room reserved successfully.\n";
}

//----------Pull from files----------

void pullToSVec(string file,vector<string>& vec){
    size_t s=fileSize(file);
    if(!s)return;
    fin.open(file);
    string line;
    while(getline(fin,line)) vec.push_back(line);
    fin.ignore();
    fin.close();
}

void pullRooms(){
    size_t s=fileSize("data/room.csv");
    if(!s)return;
    fin.open("data/room.csv");
    string temp;
    while(getline(fin,temp)){
        stringstream s(temp);
        room r;
        getline(s,temp,',');
        r.num=stoi(temp);
        getline(s,r.address,',');
        getline(s,r.type,',');
        getline(s,temp,',');
        r.price=stod(temp.substr(0,temp.length()-1));
        if(getline(s,temp,'\n'))vectorizeString(temp,r.additionalFeatures);;
        rVec.push_back(r);
    }
    fin.ignore();
    fin.close();
}

void pullUsers(){
    size_t s=fileSize("data/user.csv");
    if(!s)return;
    fin.open("data/user.csv");
    for(size_t i=0;i<s;i++){
        string temp;
        user u;
        getline(fin,temp,',');
        u.ID=stoi(temp);
        getline(fin,u.fName,',');
        getline(fin,u.lName,',');
        getline(fin,u.password,',');
        getline(fin,u.address,',');
        getline(fin,u.num,'\n');
        uVec.push_back(u);
    }
    fin.ignore();
    fin.close();
}

void pullReservations(){
    size_t s=fileSize("data/reservation.csv");
    if(!s)return;
    fin.open("data/reservation.csv");
    for(size_t i=0;i<s;i++){
        string temp;
        getline(fin,temp,',');
        room* rp=findRoom(stoi(temp));
        getline(fin,temp,',');
        user* up=findUID(stoi(temp));
        reservation res;
        res.r=rp,res.u=up;
        getline(fin,temp,',');
        res.start.input(temp);
        getline(fin,temp);
        res.end.input(temp);
        resVec.push_back(res);
    }
    fin.ignore();
    fin.close();
}

void pullAll(){
    pullToSVec("data/features.csv",features);
    pullToSVec("data/locations.csv",locations);
    pullToSVec("data/types.csv", types);
    pullRooms();
    pullUsers();
    pullReservations();
}

//----------Push to files----------

void pushFromVec(string file,vector<string> vec){
    fout.open(file);
    for(auto a:vec) fout<<a<<"\n";
    fout.close();
}

void pushRooms(){
    if(!rVec.size())return;
    sortRooms();
    fout.open("data/room.csv");
    for(auto r:rVec){
        fout<<r.num<<","<<r.address<<","<<r.type<<","<<r.price<<"$";
        if(r.hasAdditionalFeatures()){
            for(auto a:r.additionalFeatures)fout<<","<<a;
        }
        fout<<"\n";
    }
    fout.close();
}

void pushUsers(){
    fout.open("data/user.csv");
    for(auto u:uVec){
        fout<<u.ID<<","<<u.fName<<","<<u.lName<<","<<u.password<<","<<u.address<<","<<u.num<<"\n";
    }
    fout.close();
}

void pushReservations(){
    if(!resVec.size())return;
    sortRes();
    fout.open("data/reservation.csv");
    for(auto res:resVec){
        fout<<res.r->num<<","<<res.u->ID<<","<<res.start.info()<<","<<res.end.info()<<"\n";
    }
    fout.close();
}

void pushAll(){
    pushFromVec("data/features.csv",features);
    pushFromVec("data/locations.csv",locations);
    pushFromVec("data/types.csv",types);
    pushRooms();
    pushUsers();
    pushReservations();
}

void sync(){
    for(auto u:uVec)u.displayInfo();
    pushAll();
    features.clear();
    locations.clear();
    types.clear();
    rVec.clear();
    uVec.clear();
    resVec.clear();
    pullAll();
}

//----------Delete entries----------

void removeFromVector(vector<string> vec){
    vector<string> temp;
    addToVector(temp);
    if(!validateVector(temp,vec)){
        cout<<"Invalid feature detected!\n";
        return;
    }
    for(auto t:temp){
        swapT(t,vec[vec.size()-1]);
        vec.pop_back();
    }
    cout<<"Elements removed successfully.\n";
}

void cancelReservation(user* u){
    cout<<"Room Number\n";
    unsigned int rnum;
    validate(rnum);
    if(!findRoom(rnum)){
        cout<<"Room not found!\n";
        return;
    }
    reservation* res=findRes(u->ID,rnum);
    if(!res){
        cout<<"Reservation not found!\n";
        return;
    }
    swapT(*res,resVec[resVec.size()-1]);
    resVec.pop_back();
    cout<<"Reservation canceled successfully.\n";
}

void deleteRoom(){
    cout<<"Room Number\n";
    unsigned int rnum;
    validate(rnum);
    room* r=findRoom(rnum);
    if(!r){
        cout<<"Room not found!\n";
        return;
    }
    for(auto& u:uVec){
        reservation* res=findRes(u.ID,rnum);
        if(!res) continue;
        swapT(*res,resVec[resVec.size()-1]);
        resVec.pop_back();
    }
    swapT(*r,rVec[rVec.size()-1]);
    rVec.pop_back();
    cout<<"Room deleted successfully.\n";
}

//----------Edit entries----------

void editRoom(room* r){
    r->additionalFeatures.clear();
    cout<<"Type\n";
    r->type=types[selectChoice(&types[0],types.size())-1];
    cout<<"Price\n";
    validate(r->price);
    if(features.size()){
        cout<<"Do you want to assign additional features to the room?";
        if(yN()){
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            assignFeatures(r);
        }
    }
    cout<<"Room info edited successfully.\n";
}
