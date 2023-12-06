#include "Book.hpp"

Book::Book()
	:Media(), author("?"), isbn("?"), pages(1), edition(1)
{
}

Book::Book(const std::string& title, const std::string& author, const std::string& isbn, int pages, int edition)
	:Media(title), author(author), isbn(isbn), pages(pages), edition(edition)
{
}

Book::Book(const Book& other)
	:Media(other.getTitle()), author(other.author), isbn(other.isbn), pages(other.pages), edition(other.edition)
{
}

Book::~Book()
{
}

Book& Book::operator=(const Book& other)
{
	if (this != &other) {
		Media::operator=(other);
		this->author = other.author;
		this->isbn = other.isbn;
		this->pages = other.pages;
		this->edition = other.edition;
	}
	return *this;
}

const std::string& Book::getAuthor() const
{
	return this->author;
}

const std::string& Book::getIsbn() const
{
	return this->isbn;
}

int Book::getPages() const
{
	return this->pages;
}

int Book::getEdition() const
{
	return this->edition;
}

bool Book::operator==(const Book& other) const
{
	return this->getTitle() == other.getTitle() && this->author == other.author &&
		this->isbn == other.isbn && this->pages == other.pages && this->edition == other.edition;
}

bool Book::operator!=(const Book& other) const
{
	return this->getTitle() != other.getTitle() || this->author != other.author ||
		this->isbn != other.isbn || this->pages != other.pages || this->edition != other.edition;
}

std::string Book::prettyPrint() const
{
	return "\nTitle: " + this->getTitle() + "\nAuthor: " + this->author +
		"\nPages: " + std::to_string(this->pages) + "\nEdition: " +
		std::to_string(this->edition) + "\nISBN: " + this->isbn + '\n';
}

bool Book::operator==(const Media& other) const
{
	return typeid(*this) == typeid(other);
}

bool Book::operator!=(const Media& other) const
{
	return typeid(*this) != typeid(other);
}
