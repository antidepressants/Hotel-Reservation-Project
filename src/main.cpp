#include "cli.h"
#include <cstdlib>
using namespace std;

int main(){
    start();
    string loginChoices[]={"Login","Register","Quit"};
    user* up=nullptr;
    while(true){
        (windows)?system("cls"):system("clear");
        cout<<"\n-----Main Menu-----\n";
        switch (selectChoice(loginChoices,3)) {
        case 1:
            up=login();
            break;
        case 2:
            addUser();
            break;
        case 3:
            (windows)?system("cls"):system("clear");
            return 0;
        }
        cout<<"\nPress enter to continue...";
        string temp;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
        getline(cin,temp);
        sync();
        if(!fout) {
            cerr<<"Error writing to file!\n";
            return EXIT_FAILURE;
        }
        while(up){
            (windows)?system("cls"):system("clear");
            if(up->ID==1) adminMenu(up);
            else clientMenu(up);
        }
    }
}