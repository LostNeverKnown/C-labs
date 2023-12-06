#pragma once
#include<string>
#include<typeinfo>

class Media {
private:
    std::string title;
public:
    Media();
    Media(const std::string& title);
    virtual ~Media();
    const std::string& getTitle() const;
    virtual std::string prettyPrint() const = 0;
    Media& operator=(const Media& other);
    bool operator==(const Media& other) const;
    bool operator!=(const Media& other) const;
};
