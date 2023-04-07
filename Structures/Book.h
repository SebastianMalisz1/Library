#pragma once
#include <string>

struct Book
{
public:
	Book(std::string titleArg, std::string authorArg, int indexArg, int publishedYearArg) : 
		index(indexArg), title(titleArg), author(authorArg), publishedYear(publishedYearArg)
	{
		isBorrowed = false;
	}

	bool Borrow()
	{
		if (this->isBorrowed == true)
			return false;

		this->isBorrowed = true;
		return true;
	}

	bool Return()
	{
		if (this->isBorrowed == false)
			return false;

		this->isBorrowed = false;
		return true;
	}

	std::string GetTitle()
	{
		return this->title;
	}

	int GetIndex()
	{
		return this->index;
	}
	
	std::string GetAuthor()
	{
		return this->author;
	}

	int GetPublishedYear()
	{
		return this->publishedYear;
	}

	bool IsBorrowed()
	{
		return this->isBorrowed;
	}

private:
	int index;
	std::string title;
	int publishedYear;
	std::string author;
	bool isBorrowed;
};