#include<iostream>
#include<string>
//#include"Vector.hpp"
#include<vector>
#include<time.h>

using namespace std;

int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::cout << "Hello assignment!" << std::endl;
    clock_t tstart = clock();

    vector<int> myvec;
    myvec.push_back(1);
    myvec.push_back(2);
    myvec.push_back(3);
    myvec.push_back(4);
    //myvec.erase(1);
    for (int i = 0; i < myvec.size(); i++) {
        std::cout << std::to_string(myvec[i]) << std::endl;
    }
    for (int i = 0; i < 10000000; i++) {
        myvec.push_back(i);
    }
    for (int i = 0; i < 10000000; i++) {
        myvec.pop_back();
    }

{
     vector<std::string> myVector;

     myVector.push_back("Hello");
     //myVector.insert(1, "world");

     for (int i = 0; i < myVector.size(); i++) {
         std::cout << myVector[i] << " ";
     }
     std::cout << std::endl;
 }
    std::cout << "Time taken: " << (double)(clock() - tstart) / CLOCKS_PER_SEC << std::endl;

	return 0;
}