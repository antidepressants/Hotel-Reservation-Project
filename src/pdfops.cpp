#include "globalvariables.h"
#include <hpdf.h>
#include <cstring>
using namespace std;

void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    cerr <<"error! "<<hex<<error_no<<" "<<detail_no<< '\n';
    throw std::exception();
}

void exportTotal(user* u){
    bool cont=0;
    for(auto res:resVec)if(res.u==u){
        cont=1;
        break;
    }
    if(!cont) return;
    string titleStr=u->fName+" "+u->lName;
    char* title=new char[titleStr.length()+1];
    strcpy(title,titleStr.c_str());
    HPDF_Doc pdf=HPDF_New(error_handler,NULL);
    HPDF_Page page=HPDF_AddPage(pdf);
    HPDF_REAL height=HPDF_Page_GetHeight(page);
    HPDF_REAL width=HPDF_Page_GetWidth(page);
    HPDF_Font font=HPDF_GetFont(pdf,"Helvetica",NULL);
    HPDF_Page_SetFontAndSize(page,font,24);
    HPDF_Page_BeginText(page);
    HPDF_REAL tw=HPDF_Page_TextWidth(page,title);
    HPDF_Page_TextOut(page,(width-tw)/2,height-50,title);
    delete [] title;
    HPDF_Page_EndText(page);
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page,font,18);
    HPDF_Page_MoveTextPos(page,50,height-100);
    for(auto res:resVec){
        if(res.u==u){
            string tempStr="Room no: "+to_string(res.r->num);
            char temp[256];
            strcpy(temp,tempStr.c_str());
            HPDF_Page_ShowText(page,temp);
            HPDF_Page_MoveTextPos(page,0,-20);
            tempStr="From "+res.start.info()+" to "+res.end.info();
            strcpy(temp,tempStr.c_str());
            HPDF_Page_ShowText(page,temp);
            HPDF_Page_MoveTextPos(page,0,-20);
            tempStr="Total: "+to_string(total(res))+"$";
            strcpy(temp,tempStr.c_str());
            HPDF_Page_ShowText(page,temp);
            HPDF_Page_MoveTextPos(page,0,-50);
        }
    }
    HPDF_Page_EndText(page);
    titleStr="data/output/"+titleStr+".pdf";
    title=new char[titleStr.length()+1];
    strcpy(title,titleStr.c_str());
    HPDF_SaveToFile(pdf,title);
    HPDF_Free(pdf);
}