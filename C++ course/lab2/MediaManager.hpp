#pragma once
#include "Book.hpp"
#include "Ps2Game.hpp"

class MediaManager {
private:
	std::size_t size;
	Media** media;
public:
	MediaManager(size_t size);
	MediaManager(const MediaManager& other);
	~MediaManager();
	void addMedia(Media* media);
	void addBook(const Book& book);
	void addPs2Game(const Ps2Game& game);
	std::string printMedia() const;
	void getBooks(Book*& out_array, int& out_bookCount) const;
	void getPs2Games(Ps2Game*& out_array, int& out_gameCount) const;
	Media** getMedias() const;
	bool operator==(const MediaManager& other) const;
	bool operator!=(const MediaManager& other) const;
};
