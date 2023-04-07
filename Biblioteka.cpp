#include <iostream>
#include <filesystem>
#include <string>

#include "Member.h"
#include "Library.h"
#include "Book.h"

namespace
{
    Library lib;
    Member* user;

    bool isMenuDrawn = false;
    bool isLogged = false;
}

void AddBookToDatabase()
{
    std::string title;
    std::string author;
    int publishedYear;

    std::cout << "Enter book name: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    std::cout << "Enter book's author: ";
    std::getline(std::cin, author);

    std::cout << "Enter year of publishment: ";
    std::cin >> publishedYear;

    if (lib.AddNewBook(title, author, publishedYear))
        std::cout << "The book is added!" << '\n';
    else
        std::cout << "The book is already in library!" << '\n';
}

void Login()
{
    std::string login;
    std::string password;

    std::cout << "Enter login: ";
    std::cin >> login;

    std::cout << "Enter password: ";
    std::cin >> password;

    user = lib.Login(login, password);

    if (user != nullptr)
    {
        std::cout << "Logged in as " << login << '\n';
        isLogged = true;
    }
    else
        std::cout << "Incorrect login or password!" << '\n';
}

void Register()
{
    std::string login;
    std::string password;

    std::cout << "Enter login: ";
    std::cin >> login;

    std::cout << "Enter password: ";
    std::cin >> password;

    user = lib.RegisterNewMember(login, password);

    if (user != nullptr)
    {
        std::cout << "Registered as " << login << '\n';
        isLogged = true;
    }
    else
        std::cout << "Ups, something goes wrong!" << '\n';
}

void BorrowBook()
{
    if (isLogged)
    {
        int index;

        std::cout << "Enter book's index you want to borrow: ";
        std::cin >> index;

        if (lib.GetBookByIndex(index)->IsBorrowed())
            std::cout << "The book is already borrowed or there is no book with such an index!\n";
        else
            lib.BorrowBook(user, lib.GetBookByIndex(index));
    }
}

void ReturnBook()
{
    if (isLogged)
    {
        int index;

        std::cout << "Enter book's index you want to return: ";
        std::cin >> index;

        if (user->ReturnBook(index))
            std::cout << "You returned the book to the library!\n";
        else
            std::cout << "You have no book with such an index borrowed!\n";
    }
}

void DrawMenu()
{
    std::cout << "\n\n";
    if (!isLogged)
    {
        std::cout << "1. Log in\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";

        isMenuDrawn = true;
    }
    else
    {
        std::cout << "1. Add new book\n";
        std::cout << "2. Show books in the library\n";
        std::cout << "3. Borrow book\n";
        std::cout << "4. Return book\n";
        std::cout << "5. Show borrowed books\n";
        std::cout << "6. Exit\n";

        isMenuDrawn = true;
    }
}

bool MakeAction(int action)
{
    if (!isLogged)
    {
        if (action == 1)
        {
            Login();
            return true;
        }
        if (action == 2)
        {
            Register();
            return true;
        }
        if (action == 3)
        {
            return false;
        }
    }
    else
    {
        if (action == 1)
        {
            AddBookToDatabase();
            return true;
        }
        if (action == 2)
        {
            lib.DisplayBooks();
            return true;
        }
        if (action == 3)
        {
            BorrowBook();
            return true;
        }
        if (action == 4)
        {
            ReturnBook();
            return true;
        }
        if (action == 5)
        {
            user->ShowBorrowedBooks();
            return true;
        }
        if (action == 6)
        {
            return false;
        }
    }
}

int main()
{
    int action = 0;

    while (true)
    {
        if (!isMenuDrawn)
        {
            DrawMenu();
        }

        std::cout << "\n\nChoose your operation: ";
        std::cin >> action;

        if (action != 0)
        {
            if (!MakeAction(action))
                return 0;

            isMenuDrawn = false;
            action = 0;
        }
    }

    return 0;
}