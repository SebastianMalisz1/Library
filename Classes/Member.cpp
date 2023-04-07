#include "Member.h"

#include <iostream>

Member::Member(std::string login, std::string password)
{
	this->login = login;
	this->password = password;
}

bool Member::Login(std::string login, std::string password)
{
	if (login == this->login && password == this->password)
		return true;

	return false;
}

bool Member::BorrowBook(Book* book)
{
	if(book == nullptr)
		return false;

	borrowedBooks.push_back(book);
	book->Borrow();

	return true;
}

bool Member::ReturnBook(int index)
{
	for (auto &book : borrowedBooks)
	{
		if (book->GetIndex() == index)
		{
			book->Return();
			borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), book));
			return true;
		}
	}

	return false;
}

void Member::ShowBorrowedBooks()
{
	for (auto &book : borrowedBooks)
	{
		std::cout << book->GetIndex() << ". " << book->GetTitle() << ", Borrowed: " << book->IsBorrowed() << '\n';
	}
}

std::string Member::GetUsername()
{
	return this->login;
}

std::string Member::GetPassword()
{
	return this->password;
}
