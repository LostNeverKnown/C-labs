#include "Media.hpp"

Media::Media()
	:title("?")
{
}

Media::Media(const std::string& title)
	:title(title)
{
}

Media::~Media()
{
}

const std::string& Media::getTitle() const
{
	return this->title;
}

Media& Media::operator=(const Media& other)
{
	this->title = other.title;
	return *this;
}

bool Media::operator==(const Media& other) const
{
	return this->title == other.title && typeid(*this) == typeid(other);
}

bool Media::operator!=(const Media& other) const
{
	return this->title != other.title || typeid(*this) != typeid(other);
}
