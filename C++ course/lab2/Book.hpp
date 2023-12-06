#pragma once
#include "Media.hpp"

class Book : public Media {
private:
    std::string author;
    std::string isbn;
    int pages;
    int edition;
public:
    Book();
    Book(const std::string& title, const std::string& author,
         const std::string& isbn, int pages, int edition);
    Book(const Book& other);
    ~Book();
    Book& operator=(const Book& other);
    const std::string& getAuthor() const;
    const std::string& getIsbn() const;
    int getPages() const; 
    int getEdition() const;
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
    virtual std::string prettyPrint() const override;
    bool operator==(const Media& other) const;
    bool operator!=(const Media& other) const;
};
