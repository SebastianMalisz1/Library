#include <filesystem>
#include <fstream>
#include <ranges>
#include <iostream>

#include "Library.h"

Library::Library()
{
	lastIndex = 0;
	this->userPath = "";
	this->bookPath = "";

	LoadBookDataBase("books.txt");
	LoadUserDataBase("credentials.txt");
}

Library::~Library()
{
	if (userPath != "")
		SaveUserDataBase("credentials.txt");

	if (bookPath != "")
		SaveBookDataBase("books.txt");

	for (auto &book : books)
	{
		delete book;
	}

	for (auto &member : members)
	{
		delete member;
	}
}

Member* Library::RegisterNewMember(std::string login, std::string password)
{
	if (AlreadyContainsMember(login))
		return nullptr;

	Member* member = new Member(login, password);
	members.push_back(member);

	return member;
}

Book* Library::GetBookByIndex(int index)
{
	for (auto &book : books)
	{
		if (book->GetIndex() == index)
			return book;
	}

	return nullptr;
}

bool Library::AddNewBook(const std::string title, const std::string author, const int publishedYear)
{
	if (AlreadyContainsBook(title))
		return false;

	Book* book = new Book(title, author, lastIndex, publishedYear);
	books.push_back(book);
	lastIndex++;

	return true;
}

bool Library::BorrowBook(Member* member, Book* book)
{
	if (book == nullptr)
		return false;

	if (book->IsBorrowed() == false)
	{
		member->BorrowBook(book);
		return true;
	}

	return false;
}

Member* Library::Login(std::string login, std::string password)
{
	for (auto &member : members)
	{
		if (member->Login(login, password))
		{
			return member;
		}
	}
	return nullptr;
}

bool Library::LoadUserDataBase(const std::string_view fileName)
{
	std::filesystem::create_directory("Data");
	auto path = std::format("{}//Data//{}", ".", fileName.data());

	if (!FileExists(path))
		return false;

	this->userPath = path;
	std::string line;
	std::ifstream file(path.data());

	while (std::getline(file, line))
	{
		if (line.size() < 2)
			return false;

		std::vector<std::string> memberData;
		memberData = Split(line, ',');
		Member* member = new Member(memberData.at(0), memberData.at(1));
		members.push_back(member);
	}

	file.close();
	return true;
}

bool Library::LoadBookDataBase(const std::string_view fileName)
{
	std::filesystem::create_directory("Data");
	auto path = std::format("{}//Data//{}", ".", fileName.data());

	if (!FileExists(path))
		return false;

	this->bookPath = path;
	std::string line;
	std::ifstream file(path.data());

	while (std::getline(file, line))
	{
		if (line.size() < 2)
			return false;

		std::vector<std::string> bookData;
		bookData = Split(line, ',');
		Book* book = new Book(bookData.at(0), bookData.at(1), lastIndex, std::stoi(bookData.at(2)));
		lastIndex++;
		books.push_back(book);
	}

	file.close();
	return true;
}

void Library::DisplayBooks()
{
	for (auto &book : books)
	{
		std::cout << book->GetIndex() << ". " << book->GetTitle() << ", Borrowed: " << book->IsBorrowed() << '\n';
	}
}

bool Library::FileExists(const std::string_view path)
{
	return std::filesystem::exists(path.data());
}

bool Library::SaveUserDataBase(const std::string_view fileName)
{
	std::filesystem::create_directory("Data");
	auto path = std::format("{}//Data//{}", ".", fileName.data());
	std::fstream file;

	if (!FileExists(path))
	{
		file.open(path, std::ios::in | std::ios::out | std::ios::app);
	}

	file.clear();

	for (auto &member : members)
	{
		file << member->GetUsername().data() << ',' << member->GetPassword().data() << '\n';
	}

	file.close();
	return true;
}

bool Library::SaveBookDataBase(const std::string_view fileName)
{
	std::filesystem::create_directory("Data");
	auto path = std::format("{}//Data//{}", ".", fileName.data());
	std::fstream file;

	if (FileExists(path))
	{
		file.open(path, std::ofstream::out | std::ofstream::trunc);
		file.close();
	}

	file.open(path, std::ios::in | std::ios::out | std::ios::app );

	for (auto &book : books)
	{
		file << book->GetTitle().data() << ',' << book->GetAuthor().data() << ',' << book->GetPublishedYear() << '\n';
	}

	file.close();
	return true;
}

bool Library::AlreadyContainsMember(const std::string_view login)
{
	for (auto &member : members)
	{
		if (member->GetUsername() == login)
			return true;
	}
	return false;
}

bool Library::AlreadyContainsBook(const std::string_view title)
{
	for (auto &book : books)
	{
		if (book->GetTitle() == title)
			return true;
	}
	return false;
}

std::vector<std::string> Library::Split(std::string input, const char splitter)
{

//	auto range = input
//		| std::ranges::views::split(splitter)
//		| std::ranges::views::transform([](auto&& rng)
//			{
//				return std::string_view(&*rng.begin(), std::ranges::distance(rng));
//			});
//
//	return { std::ranges::begin(range), std::ranges::end(range) };

	std::stringstream stream(input);
	std::string segment;
	std::vector<std::string> splited;

	while (std::getline(stream, segment, splitter))
	{
		splited.push_back(segment);
	}

	return splited;
}