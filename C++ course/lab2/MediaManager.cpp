#include "MediaManager.hpp"

MediaManager::MediaManager(size_t size)
	:size(size)
{
	this->media = new Media * [this->size]{ nullptr };
}

MediaManager::MediaManager(const MediaManager& other)
	:size(other.size)
{
	this->media = new Media * [this->size]{ nullptr };
	for (int i = 0; i < this->size; i++) {
		if (dynamic_cast<Book*>(other.media[i]) != nullptr) {
			Book* book = dynamic_cast<Book*>(other.media[i]);
			this->media[i] = new Book(*book);
		}
		else if (dynamic_cast<Ps2Game*>(other.media[i]) != nullptr) {
			Ps2Game* game = dynamic_cast<Ps2Game*>(other.media[i]);
			this->media[i] = new Ps2Game(*game);
		}
	}
}

MediaManager::~MediaManager()
{
	for (int i = 0; i < this->size; i++) {
		delete this->media[i];
	}
	delete[] this->media;
}

void MediaManager::addMedia(Media* media)
{
	for (int i = 0; i < this->size; i++) {
		if (this->media[i] == nullptr) {
			if (dynamic_cast<Book*>(media) != nullptr) {
				Book* book = dynamic_cast<Book*>(media);
				this->media[i] = new Book(*book);
			}
			else if (dynamic_cast<Ps2Game*>(media) != nullptr) {
				Ps2Game* game = dynamic_cast<Ps2Game*>(media);
				this->media[i] = new Ps2Game(*game);
			}
			break;
		}
	}
}

void MediaManager::addBook(const Book& book)
{
	for (int i = 0; i < this->size; i++) {
		if (this->media[i] == nullptr) {
			this->media[i] = new Book(book);
			break;
		}
	}
}

void MediaManager::addPs2Game(const Ps2Game& game)
{
	for (int i = 0; i < this->size; i++) {
		if (this->media[i] == nullptr) {
			this->media[i] = new Ps2Game(game);
			break;
		}
	}
}

std::string MediaManager::printMedia() const
{
	int bookCount = 0;
	int gameCount = 0;
	for (int i = 0; i < this->size; i++) {
		if (dynamic_cast<Book*>(this->media[i]) != nullptr) {
			bookCount++;
		}
		else if (dynamic_cast<Ps2Game*>(this->media[i]) != nullptr) {
			gameCount++;
		}
	}
	std::string bookstring;
	std::string gamestring;
	for (int i = 0; i < this->size; i++) {
		if (dynamic_cast<Book*>(this->media[i]) != nullptr) {
			bookstring += this->media[i]->prettyPrint();
		}
		else if (dynamic_cast<Ps2Game*>(this->media[i]) != nullptr) {
			gamestring += this->media[i]->prettyPrint();
		}
	}
	return "------ MediaManager ------\n\nCapacity: " + std::to_string(this->size) + "\nBooks: " + std::to_string(bookCount) +
		"\nPs2Games: " + std::to_string(gameCount) + "\n\n-- Books --\n" + bookstring + "\n-- Ps2Games --\n" + gamestring +
		"\n--------------------------";
		   
}

void MediaManager::getBooks(Book*& out_array, int& out_bookCount) const
{
	for (int i = 0; i < this->size; i++) {
		if (dynamic_cast<Book*>(this->media[i]) != nullptr) {
			out_bookCount++;
		}
	}
	Book* bookarr = new Book [out_bookCount];
	out_array = bookarr;
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (dynamic_cast<Book*>(this->media[i]) != nullptr) {
			Book* book = dynamic_cast<Book*>(this->media[i]);
			bookarr[count++] = Book(*book);
		}
	}
}

void MediaManager::getPs2Games(Ps2Game*& out_array, int& out_gameCount) const
{
	for (int i = 0; i < this->size; i++) {
		if (dynamic_cast<Ps2Game*>(this->media[i]) != nullptr) {
			out_gameCount++;
		}
	}
	Ps2Game* gamearr = new Ps2Game [out_gameCount];
	out_array = gamearr;
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (dynamic_cast<Ps2Game*>(this->media[i]) != nullptr) {
			Ps2Game* book = dynamic_cast<Ps2Game*>(this->media[i]);
			gamearr[count++] = Ps2Game(*book);
		}
	}
}

Media** MediaManager::getMedias() const
{
	return media;
}

bool MediaManager::operator==(const MediaManager& other) const
{
	bool check = true;
	for (int i = 0; i < this->size; i++) {
		if (this->media[i] != nullptr && other.media[i] != nullptr && *this->media[i] != *other.media[i]) {
			check = false;
			break;
		}
	}
	return check;
}

bool MediaManager::operator!=(const MediaManager& other) const
{
	bool check = true;
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (this->media[i] != nullptr && other.media[i] != nullptr && *this->media[i] == *other.media[i]) {
			count++;
		}
	}
	if (count == this->size) {
		check = false;
	}
	return check;
}
