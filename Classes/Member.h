#pragma once
#include <string>
#include <vector>

#include "Book.h"

class Member
{
public:

	Member(std::string login, std::string password);

	bool Login(std::string login, std::string password);
	bool BorrowBook(Book* book);
	bool ReturnBook(int index);

	void ShowBorrowedBooks();

	std::string GetUsername();
	std::string GetPassword();

private:

	std::string login;
	std::string password;
	std::vector<Book*> borrowedBooks;
};