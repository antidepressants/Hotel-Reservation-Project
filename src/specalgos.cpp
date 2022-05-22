#include "password.h"
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