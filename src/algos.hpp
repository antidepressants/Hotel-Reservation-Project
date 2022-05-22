#pragma once
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>
#include <climits>

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
    std::cout<<">>";
    std::cin>>a;
    if(!std::cin){
      valid=0;
      std::cout<<"Invalid input!\n";
      std::cin.clear();
      std::cin.ignore(INT_MAX,'\n');
    }
  }while(!valid);
}

int selectNum(int lBound,int hBound);

template <class t>
int selectChoice(t choices[],int size){
  t choice;
  for(size_t i=0;i<size;i++){
    std::cout<<"["<<i+1<<"] "<<choices[i]<<"\n";
  }
  return selectNum(1,size);
}

bool validateVector(std::vector<std::string> vec1,std::vector<std::string> vec2);
void listVector(std::vector<std::string> vec);
bool yN();