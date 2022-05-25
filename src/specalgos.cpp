#include "password.h"
#include <string>
using namespace std;

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
    char illegal[]="',<>/{}()*&^%$#!-+=`~|\'\"\\";
    for(auto c:illegal) if(email.find(c)!=string::npos){
        valid=0;
        break;
    }
    if(valid==0){
        cout<<"Invalid Email!\n";
        return validateEmail();
    }
    return email;
}

string validatePhone(){
    unsigned int n;
    validate(n);
    string num=to_string(n);
    if(num.length()==7)num="0"+num;
    else if(num.length()!=8){
        cout<<"Invalid Phone Number!\n";
        return validatePhone();
    }
    bool valid=0;
    string rc=num.substr(0,2);
    string rcs[]={"01","03","04","05","06","07","08","09","70","71","76","78","79","80","81"};
    for(auto r:rcs){
        if(rc.compare(r)==0){
            valid=1;
            break;
        }
    }
    if(!valid){
        cout<<"Invalid Region Code!\n";
        return validatePhone();
    }
    num=rc + "-" + num.substr(2,6);
    return num;
}

string validateName(){
    string name;
    cout<<">>";
    getline(cin,name);
    for(auto c:name){
        if(!isalpha(c) && c!=' '){
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