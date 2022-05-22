#pragma once
#include <string>
#include "classes.h"
#include "globalvariables.h"

size_t fileSize(std::string file);
size_t max(std::string file);
room* findRoom(unsigned int rnum);
user* findUID(unsigned int uID);
user* findEmail(std::string email);
reservation* findRes(unsigned int uID,unsigned int rNum);
int findString(std::string* arr,size_t s,std::string target);
void vectorizeString(std::string line,std::vector<std::string>& vec);
void addToVector(std::vector<std::string>& vec);
void assignFeatures(room* r);
void sortRooms();
void sortRes();
void addRoom();
void addUser();
void addReservation(user* u);
void pullToSVec(std::string file,std::vector<std::string>& vec);
void pullRooms();
void pullUsers();
void pullReservations();
void pullAll();
void pushFromVec(std::string file,std::vector<std::string> vec);
void pushRooms();
void pushUsers();
void pushReservations();
void pushAll();
void sync();
void removeFromVector(std::vector<std::string> vec);
void cancelReservation(user* u);
void deleteRoom();
void editRoom(room* r);