#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <locale>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
using namespace std;

ifstream fin;
ofstream fout;

//----------Common functions/algorithms----------

template<class t>
void swapT(t& a,t& b){
    t temp=a;
    a=b;
    b=temp;
}

template<class t>
void compSort(t* arr, size_t size){
    for(size_t i=0;i<size-1;i++){
        size_t min=i;
        for(size_t j=i;j<size;j++){
            if(arr[j]<arr[min]) min=j;
        }
        if(min!=i){
            swapT(arr[i],arr[min]);
        }
    }
}

template<class t>
int findT(t* arr,size_t size,t target){
    for(size_t i=0;i<size;i++){
        if(target==arr[i]) return i;
    }
    return -1;
}

template<class t>
void validate(t& a){
  bool valid;
  do{
    valid=1;
    cout<<">>";
    cin>>a;
    if(!cin){
      valid=0;
      cout<<"Invalid input!\n";
      cin.clear();
      cin.ignore(INT_MAX,'\n');
    }
  }while(!valid);
}

int selectNum(int lBound,int hBound){
    cout<<"["<<lBound<<"-"<<hBound<<"]\n";
    int n;
    do{
        validate(n);
        if(n<lBound or n>hBound) cout<<"Invalid option!\n";
    }while(n<lBound or n>hBound);
    cin.clear();
    cin.ignore(INT_MAX,'\n');
    return n;
}

template <class t>
int selectChoice(t choices[],int size){
  t choice;
  for(size_t i=0;i<size;i++){
    cout<<"["<<i+1<<"] "<<choices[i]<<"\n";
  }
  return selectNum(1,size);
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
    for(auto a:vec) cout<<"\n-"<<a<<"\n";
}

bool yN(){
    bool b=0;
    char c;
    cout<<"[y/N]\n"<<">>";
    cin>>c;
    c=tolower(c);
    if(c=='y') return 1;
    if(c=='n') return 0;
    return 0;
    cin.clear();
    cin.ignore(INT_MAX,'\n');
}

//Password encryption

string validatePassword(size_t t){
    cout<<">>";
    string pass;
    cin>>pass;
    if(pass.length()<8 || pass.length()>t){
        cout<<"Invalid password length!\n";
        return validatePassword(t);
    }
    bool a=0,d=0,s=0;
    for (size_t i=0;i<pass.length();i++) {
        if(isalpha(pass[i])) a=1;
        else if(isdigit(pass[i]))d=1;
        else s=1;
    }
    if(!a||!d||!s){
        cout<<"Password must include letters, numbers, and special characters!\n";
        return validatePassword(t);
    }
    return pass;
}

unsigned int strSeed(string s){
    unsigned int seed=0;
    for(size_t i=0;i<s.length();i++){
        seed+=(int)s[i];
    }
    return seed;
}

string hashStr(string s,size_t t,int init){
    string str="";
    unsigned int strseed=init*strSeed(s);
    for(size_t i=0;i<s.length();i++){
        srand(strseed);
        unsigned int seed=strseed-(int)s[i];
        srand(seed);
        char c;
        switch(rand()%3){
            case 0:
                c=rand()%10+48;
                break;
            case 1:
                c=rand()%26+65;
                break;
            case 2:
                c=rand()%26+97;
        }
        str+=c;
    }
    return str;
}

void appendFillers(string& s,size_t t){
    size_t diff=t-s.length();
    if(!diff) return;
    size_t a=t/s.length();
    size_t b=0;
    while(t%(s.length()+b)!=0)b++;
    size_t pos=s.length()-b;
    string sub=s.substr(pos,b);
    sub.append(hashStr(sub,t,1));
    s.replace(pos,sub.length(),sub);
}

string encryptPassword(string s,size_t t){
    appendFillers(s,t);
    size_t blocks=t/s.length();
    string str="";
    for(size_t i=1;i<=blocks;i++){
        str.append(hashStr(s,t,i));
    }
    return str;
}

//----------Project specific functions/algorithms----------

string validateEmail(){
    string email;
    cout<<">>";
    cin>>email;
    bool valid=0;
    int atpos = email.find("@");
    if(atpos!=string::npos && atpos!=0){
        string domain=email.substr(atpos+1,email.length()-atpos-1);
        int dotpos = domain.find(".");
        if(dotpos!=string::npos && dotpos!=0 && dotpos!=domain.length()-1) valid=1;
    }
    if(valid==0){
        cout<<"Invalid Email!\n";
        return validateEmail();
    }
    return email;
}

string validatePhone(){
    string num;
    cout<<">>";
    cin>>num;
    for(size_t i=0;i<num.length()-1;i++) 
        if(!isdigit(num[i])){
            cout<<"Invalid input!\n";
            return validatePhone();
        }
    bool valid=0;
    string rc=num.substr(0,2);
    string rcs[]={"01","03","04","05","06","07","08","09","70","71","76","78","79","80","81"};
    for(size_t i=0;i<sizeof(rcs);i++){
        if(rc.compare(rcs[i])==0){
            valid=1;
            break;
        }
    }
    if(!valid){
        cout<<"Invalid Region Code!\n";
        return validatePhone();
    }
    if(num.length()!=8){
        cout<<"Invalid Phone Number!\n";
        return validatePhone();
    }
    num=rc + "-" + num.substr(2,6);
    return num;
}

string validateName(){
    string name;
    cout<<">>";
    getline(cin,name);
    for(size_t i=0;i<name.length()-1;i++){
        if(!isalpha(name[i]) && name[i]!=' '){
            cout<<"Invalid Input!\n";
            return validateName();
        }
    }
    return name;
}

string getPass(){
    string pass=validatePassword(32);
    return encryptPassword(pass, 32);
}

//----------Class definitions----------

struct date{
    int d,m,y;
    string info(){
        string s=to_string(d)+"-"+to_string(m)+"-"+to_string(y);
        return s;
    }
    void input(string str){
        stringstream s(str);
        string temp;
        getline(s,temp,'-');
        d=stoi(temp);
        getline(s,temp,'-');
        m=stoi(temp);
        getline(s,temp);
        y=stoi(temp);
    }
}nullDate={0,0,0};

vector<string> features;
vector<string> locations;
vector<string> types;

struct room{
    unsigned int num;
    string address,type;
    double price;
    vector<string> additionalFeatures;
    bool hasAdditionalFeatures(){
        return (additionalFeatures.size()!=0);
    }
    void displayInfo(){
        cout<<"\nRoom Number: "<<num;
        cout<<"\nAddress: "<<address;
        cout<<"\nType: "<<type;
        cout<<"\nPrice: "<<price;
        if(hasAdditionalFeatures()){
            cout<<"\nAdditional features:";
            listVector(additionalFeatures);
        }
    }
};

vector<room> rVec;

struct user{
    string password;
    unsigned int ID;
    string fName,lName,address,num;
    void displayInfo(){
        cout<<"\nID: "<<ID;
        cout<<"\nName: "<<fName<<" "<<lName;
        cout<<"\nEmail: "<<address;
        cout<<"\nPhone: "<<num;
    }
};

vector<user> uVec;

struct reservation{
    user* u;
    room* r;
    date start,end;
    void displayInfo(){
        cout<<"Room no: "<<r->num<<"\n";
        cout<<start.info()<<" - "<<end.info()<<"\n";
    }
};

vector<reservation> resVec;

//----------General DBops----------

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

//----------Project specific DBops----------

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
    date s=res.start,e=res.end;
    int days=(e.y-s.y)*365.25+(e.m-s.m)*30.4375+(e.d-s.d);
    return days*res.r->price;
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
    u.ID=max("data/user.csv")+1;
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
    fin.ignore();
    size_t s=fileSize(file);
    if(!s)return;
    fin.open(file);
    string line;
    while(getline(fin,line)) vec.push_back(line);
    fin.close();
}

void pullRooms(){
    fin.ignore();
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
    fin.close();
}

void pullUsers(){
    fin.ignore();
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
    fin.close();
}

void pullReservations(){
    fin.ignore();
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

template <class t>
void pushFromVec(string file,vector<t> vec){
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

//----------Cli----------

user* login(){
    cout<<"\n-----Login-----\n";
    cout<<"Email Address\n";
    string email=validateEmail();
    user* target=findEmail(email);
    if(target==nullptr) {
        cout<<"No account associated with this email found!";
        return nullptr;
    }
    cout<<"\nPassword\n";
    string pass=getPass();
    if(!target->password.compare(pass)){
        cout<<"Login successful!\n";
        return target;
    }
    cout<<"Login failed!\n";
    return nullptr;
}

void adminMenu(user*& u){
    cout<<"\n-----Admin Menu-----\n";
    string options[]={
        "Add room",
        "Add feature to list",
        "Remove feature from list",
        "Assign feature to room",
        "Add location",
        "Remove location",
        "Add room type",
        "Remove room type",
        "Delete room",
        "Edit room info",
        "Change password",
        "Logout"
    };
    int s=sizeof(options)/sizeof(string);
    room* r=nullptr;
    int rnum;
    int choice=selectChoice(options,s);
    switch(choice){
        case 1:
            addRoom();
            break;
        case 2:
            addToVector(features);
            break;
        case 3:
            removeFromVector(features);
            break;
        case 4:
            cout<<"Room Number\n";
            validate(rnum);
            r=findRoom(rnum);
            if(!r) {
                cout<<"Room not found!\n";
                break;
            }
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            assignFeatures(r);
            break;
        case 5:
            addToVector(locations);
            break;
        case 6:
            removeFromVector(locations);
            break;
        case 7:
            addToVector(types);
            break;
        case 8:
            removeFromVector(types);
            break;
        case 9:
            deleteRoom();
            break;
        case 10:
            cout<<"Room Number\n";
            validate(rnum);
            r=findRoom(rnum);
            if(!r) {
                cout<<"Room not found!\n";
                break;
            }
            editRoom(r);
            break;
        case 11:
            cout<<"New Password\n";
            u->password=getPass();
            break;
        case 12:
            u=nullptr;
            return;
        default:
            cout<<"Invalid Option!\n";
            return adminMenu(u);
    }
    cout<<"Press enter to continue...";
    string temp;
    cin.clear();
    cin.ignore(INT_MAX,'\n');
    getline(cin,temp);
    sync();
}

void clientMenu(user*& u){
    cout<<"\n-----Client Menu-----\n";
    string options[]={
        "Make reservation",
        "Cancel reservation",
        "Change password",
        "Logout"
    };
    int s=sizeof(options)/sizeof(string);
    int choice=selectChoice(options,s);
    size_t i=0;
    switch (choice) {
        case 1:
            addReservation(u);
            break;
        case 2:
            for(auto res:resVec)if(res.u==u){
                res.displayInfo();
                i++;
            }
            if(!i){
                cout<<"No reservations found!\n";
                break;
            }
            cancelReservation(u);
            break;
        case 3:
            cout<<"New Password\n";
            u->password=getPass();
        case 4:
            u=nullptr;
            return;
        default:
            cout<<"Invalid Option!\n";
            return clientMenu(u);
    }
    cout<<"Press enter to continue...";
    string temp;
    cin.clear();
    cin.ignore(INT_MAX,'\n');
    getline(cin,temp);
    sync();
}

void firstSetup(){
    cout<<"No Data Found; Entering first-time setup...\n";
    cout<<"Creating files...\n";
    fout.open("data/room.csv");
    fout.close();
    fout.open("data/user.csv");
    fout.close();
    fout.open("data/reservation.csv");
    fout.close();
    fout.open("data/features.csv");
    fout.close();
    fout.open("data/locations.csv");
    fout.close();
    fout.open("data/types.csv");
    fout.close();
    cout<<"Craeted files.\n";
    cout<<"Create admin user:\n";
    addUser();
    locations={"Beirut","Jbeil","Baalbek","Zahleh","Tyr","Tripoli"};
    sync();
}

void start(){
    system("clear");
    string file="data/user.csv";
    cout<<"Loading data...\n";
    size_t s=fileSize(file);
    if(!s) firstSetup();
    else pullAll();
    cout<<"Loaded data.\n";
}

int main(){
    start();
    string loginChoices[]={"Login","Register","Quit"};
    bool cont=0;
    user* up=nullptr;
    while(!cont){
        system("clear");
        cout<<"\n-----Main Menu-----\n";
        switch (selectChoice(loginChoices,3)) {
        case 1:
            up=login();
            break;
        case 2:
            addUser();
            break;
        case 3:
            return 0;
        }
        cout<<"Press enter to continue...";
        string temp;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        getline(cin,temp);
        sync();
        while(up){
            system("clear");
            if(up->ID==1) adminMenu(up);
            else clientMenu(up);
        }
    }
}