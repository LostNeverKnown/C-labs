#include <iostream>
#include <vector>
#include <string>
using namespace std;
//#include "BST.h"
 #include "AVL.h"

int main(/* int argc, char** argv */ )
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    AVL<int> bst;

    // Insert elements
    //std::vector<int> elementsToInsert{ 36, 22, 43, 98, 29, 77, 90, 14, 51, 85, 34, 93, 25 };
    //std::vector<int> elementsToInsert{3, 2, 1, 4, 5, 6, 7};
    std::vector<int> elementsToInsert{3, 2};
    for (int element : elementsToInsert)
    {
        bst.insert(element);
    }
    int height = bst.getTreeHeight();
    std::cout << height << std::endl;

    // Print Graphvis code to terminal
    //std::cout << std::endl << bst.ToGraphviz() << std::endl;

    return 0;
}