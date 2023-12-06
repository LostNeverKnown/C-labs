#include "Ps2Game.hpp"

Ps2Game::Ps2Game()
	:Media(), studio("?"), year(0)
{
}

Ps2Game::Ps2Game(const std::string& title, const std::string& studio, int year)
	:Media(title), studio(studio), year(year)
{
}

Ps2Game::Ps2Game(const Ps2Game& other)
	:Media(other.getTitle()), studio(other.studio), year(other.year)
{
}

Ps2Game::~Ps2Game()
{
}

Ps2Game& Ps2Game::operator=(const Ps2Game& other)
{
	if (this != &other) {
		Media::operator=(other);
		this->studio = other.studio;
		this->year = other.year;
	}
	return *this;
}

const std::string& Ps2Game::getStudio() const
{
	return this->studio;
}

int Ps2Game::getYear() const
{
	return this->year;
}

bool Ps2Game::operator==(const Ps2Game& other) const
{
	return this->getTitle() == other.getTitle() && this->studio == other.studio && this->year == other.year;
}

bool Ps2Game::operator!=(const Ps2Game& other) const
{
	return this->getTitle() != other.getTitle() || this->studio != other.studio || this->year != other.year;
}

std::string Ps2Game::prettyPrint() const
{
	return "\nTitle: " + this->getTitle() + "\nStudio: " + this->studio + "\nPublished: " + std::to_string(this->year) + '\n';
}

bool Ps2Game::operator==(const Media& other) const
{
	return typeid(*this) == typeid(other);
}

bool Ps2Game::operator!=(const Media& other) const
{
	return typeid(*this) != typeid(other);
}
