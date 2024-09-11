#include "library.h"
#include <iostream>

void AddBook(Library& library, const Book& book) {
    library.books.push_back(book);
    std::cout << "����� ���������!\n";
}

void RemoveBook(Library& library, const std::string& title) {
    auto it = std::find_if(library.books.begin(), library.books.end(),
        [&title](const Book& book) { return book.title == title; });

    if (it != library.books.end()) {
        library.books.erase(it);
        std::cout << "����� �������!\n";
    }
    else {
        std::cout << "����� �� �������.\n";
    }
}

std::vector<Book> FindBooks(const Library& library, const std::string& searchTerm) {
    std::vector<Book> results;
    for (const Book& book : library.books) {
        if (book.title.find(searchTerm) != std::string::npos ||
            book.author.find(searchTerm) != std::string::npos) {
            results.push_back(book);
        }
    }
    return results;
}

void PrintBooks(const Library& library) {
    if (library.books.empty()) {
        std::cout << "���������� �����.\n";
        return;
    }

    std::cout << "������ ����:\n";
    for (const Book& book : library.books) {
        std::cout << "��������: " << book.title << "\n";
        std::cout << "�����: " << book.author << "\n";
        std::cout << "��� �������: " << book.year << "\n";
        std::cout << "����: " << book.genre << "\n\n";
    }
}