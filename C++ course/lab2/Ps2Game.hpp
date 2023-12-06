#pragma once
#include "Media.hpp"

class Ps2Game : public Media {
private:
    std::string studio;
    int year;
public:
    Ps2Game();
    Ps2Game(const std::string& title, const std::string& studio, int year);
    Ps2Game(const Ps2Game& other);
    ~Ps2Game();
    Ps2Game& operator=(const Ps2Game& other);
    const std::string& getStudio() const;
    int getYear() const;
    bool operator==(const Ps2Game& other) const;
    bool operator!=(const Ps2Game& other) const;
    virtual std::string prettyPrint() const override;
    bool operator==(const Media& other) const;
    bool operator!=(const Media& other) const;
};
