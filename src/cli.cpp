#include "cli.h"
using namespace std;

user* login(){
    cout<<"\n-----Login-----\n";
    cout<<"Email Address\n";
    string email=validateEmail();
    user* target=findEmail(email);
    if(target==nullptr) {
        cout<<"No account associated with this email found!\n";
        return nullptr;
    }
    cout<<"Password\n";
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
            exportTotal(u);
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
    cout<<"Created files.\n";
    cout<<"Create admin user:\n";
    addUser();
    locations={"Beirut","Jbeil","Baalbek","Zahleh","Tyr","Tripoli"};
    sync();
}

void start(){
    system("clear");
    cout<<"Loading data...\n";
    size_t s=fileSize("data/user.csv");
    if(!s) firstSetup();
    else pullAll();
    cout<<"Loaded data.\n";
}