#include <iostream>
#include "MediaManager.hpp"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    MediaManager manager(4);
    MediaManager secondManager(4);
    manager.addBook(Book("a", "b", "c", 1, 1));
    secondManager.addBook(Book("a", "b", "c", 1, 1));

    manager.addPs2Game(Ps2Game("b", "c", 1));
    secondManager.addPs2Game(Ps2Game("b", "c", 1));
    manager.addBook(Book("x", "b", "c", 1, 1));
    secondManager.addPs2Game(Ps2Game("y", "b", 1));
    std::cout << (manager != secondManager) << std::endl;
    Book book("Sagan om Ringen", "J.R.R Tolkien", "0 00 717197", 535, 2);
    Ps2Game game("Sagan om Ringen", "Sophisticated Games Ltd", 2001);
    std::cout << (book != game) << std::endl;
    Media* bookAsMedia = &book;
    Media* gameAsMedia = &game;
    std::cout << (*bookAsMedia != *gameAsMedia) << std::endl;
    int count = 0;
    Ps2Game* gamearr;
    manager.getPs2Games(gamearr, count);

    return 0;
}