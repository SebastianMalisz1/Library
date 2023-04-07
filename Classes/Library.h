#pragma once
#include <vector>

#include "Member.h"
#include "Book.h"

class Library
{
public:

	Library();
	~Library();

	Member* Login(std::string login, std::string password);
	Member* RegisterNewMember(std::string login,  std::string password);

	Book* GetBookByIndex(int index);

	bool AddNewBook(std::string title, std::string author, const int publishedYear);
	bool BorrowBook(Member* member, Book* book);

	void DisplayBooks();

private:

	bool FileExists(const std::string_view path);
	bool AlreadyContainsMember(const std::string_view login);
	bool AlreadyContainsBook(const std::string_view title);
	bool SaveUserDataBase(const std::string_view fileName);
	bool SaveBookDataBase(const std::string_view fileName);
	bool LoadUserDataBase(const std::string_view fileName);
	bool LoadBookDataBase(const std::string_view fileName);

	std::string_view userPath;
	std::string_view bookPath;

	std::vector<std::string> Split(std::string input, const char splitter);
	std::vector<Member*> members;
	std::vector<Book*> books;

	int lastIndex;
};