#include "cli.h"
using namespace std;

int main(){
    start();
    string loginChoices[]={"Login","Register","Quit"};
    user* up=nullptr;
    while(true){
        sysClear();
        cout<<"\n-----Main Menu-----\n";
        switch (selectChoice(loginChoices,3)) {
        case 1:
            up=login();
            break;
        case 2:
            addUser();
            break;
        case 3:
            sysClear();
            return 0;
        }
        sysPause();
        sync();
        if(!fout) {
            cerr<<"Error writing to file!\n";
            return EXIT_FAILURE;
        }
        while(up){
            sysClear();
            if(up->ID==1) adminMenu(up);
            else clientMenu(up);
        }
    }
}