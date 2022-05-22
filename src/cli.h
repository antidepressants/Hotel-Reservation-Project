#pragma once
#include "pdfops.h"
#include "dbops.h"

user* login();
void adminMenu(user*& u);
void clientMenu(user*& u);
void firstSetup();
void start();