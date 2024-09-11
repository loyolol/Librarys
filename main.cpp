#include <iostream>
#include <string>
#include "book.h"
#include "library.h"
#include "writer.h"
#include <limits>
#include <clocale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    Library library;
    Writer writer1 = { "01:01:1980", "Lev Nikolaevich Tolstoy", {}, 42 };
    Writer writer2 = { "15:03:1975", "Ivan Alexandrovich Goncharov", {}, 47 };
    Writer writer3 = { "13:02:1960", "Pushkin Aleksandr Sergeevich", {}, 39 };


    WriteBook(writer1, "The War and Peace", "roman", 1869);
    WriteBook(writer2, "Oblomov", "roman", 1877);
    WriteBook(writer3, "Evgeny Onegin", "roman", 1831);

    AddBook(library, CreateBook("The War and Peace", "��� ���������� �������", 1869, "roman"));
    AddBook(library, CreateBook("Oblomov", "Ivan Alexandrovich Goncharov", 1877, "roman"));
    AddBook(library, CreateBook("Evgeny Onegin", "Pushkin Aleksandr Sergeevich", 1831, "roman"));

    int choice;

    do {
        cout << "\n����:\n";
        cout << "1. �������� �����\n";
        cout << "2. ������� �����\n";
        cout << "3. ����� �����\n";
        cout << "4. ������� ������ ���� ����\n";
        cout << "5. �����\n";
        cout << "������� ����� ��������: ";

        if (!(cin >> choice)) {
            cout << "������������ ����. ������� �����.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            string title, author, genre;
            int year;

            do {
                cout << "������� �������� �����: ";
                cin.ignore();
                getline(cin, title);
                if (title.empty()) {
                    cout << "�������� ����� �� ����� ���� ������. ���������� �����.\n";
                }
            } while (title.empty());

            do {
                cout << "������� ������ �����: ";
                getline(cin, author);

                if (author.empty()) {
                    cout << "����� ����� �� ����� ���� ������. ������� ������. ���������� �����.\n";
                    continue; 
                }

                bool onlyDigits = true;
                for (char c : author) {
                    if (!isdigit(c)) {
                        onlyDigits = false;
                        break;
                    }
                }
                if (onlyDigits) {
                    cout << "��� ������ ����� �� ����� �������� ������ �� ����. ������� ������. ���������� �����.\n";
                    continue; 
                }

                break; 
            } while (true);


            do {
                cout << "������� ��� ������� �����: ";
                string yearStr;
                getline(cin, yearStr); // ��������� ��� ��� ������

              
                if (yearStr.empty()) {
                    cout << "��� ������� �� ����� ���� ������. ������� �����. ���������� �����.\n";
                    continue; 
                }

                // ����������� ������ � �����
                try {
                    year = stoi(yearStr); // stoi ������� ����������, ���� �������������� �� �������
                    if (year < 0) {
                        cout << "��� ������� �� ����� ���� �������������. ������� ������.\n";
                        continue; 
                    }
                    else {
                        break; 
                    }
                }
                catch (const std::invalid_argument& e) {
                    cout << "��� ������� �� ����� ���� ������ �������. ������� �����. ���������� �����.\n";
                }
                catch (const std::out_of_range& e) {
                    cout << "��������� �������� ���� ������� �� ������� ����������� ���������. ������� ������.\n";
                }
            } while (true);

            do {
                cout << "������� ���� �����: ";
                getline(cin, genre); // ��������� ���� ��� ������

                if (genre.empty()) {
                    cout << "���� ����� �� ����� ���� ������. ������� ����. ���������� �����.\n";
                    continue; 
                }

                bool onlyDigits = true;
                for (char c : genre) {
                    if (!isdigit(c)) {
                        onlyDigits = false;
                        break;
                    }
                }
                if (onlyDigits) {
                    cout << "���� ����� �� ����� �������� ������ �� ����. ������� ����. ���������� �����.\n";
                    continue; 
                }

                break; 
            } while (true);

            Book newBook = CreateBook(title, author, year, genre);
            AddBook(library, newBook);
            break;
        }
        case 2: {
            string title;
            cout << "������� �������� ����� ��� ��������: ";
            cin.ignore();
            getline(cin, title);
            RemoveBook(library, title);
            break;
        }
        case 3: {
            string searchTerm;
            while (true) {
                cout << "������� �������� ��� ������ ��� ������: ";
                cin.ignore();
                getline(cin, searchTerm);

                // ���������, ������� �� ������ ������ �� ��������
                bool isOnlySpaces = true;
                for (char c : searchTerm) {
                    if (!isspace(c)) {
                        isOnlySpaces = false;
                        break;
                    }
                }

                // ���������, �������� �� ������ ������ ��� �������� ������ �������
                if (searchTerm.empty() || isOnlySpaces) {
                    cout << "������: ���� �� ����� ���� ������ ��� ��������� ������ �������. ���������� �����.\n";
                }
                else {
                    break; // ���� ���� ���������, ������� �� �����
                }
            }

            vector<Book> results = FindBooks(library, searchTerm);

            if (results.empty()) {
                cout << "����� �� �������.\n";
            }
            else {
                cout << "��������� �����:\n";
                for (const Book& book : results) {
                    cout << "��������: " << book.title << "\n";
                    cout << "�����: " << book.author << "\n";
                    cout << "��� �������: " << book.year << "\n";
                    cout << "����: " << book.genre << "\n\n";
                }
            }
            break;
        }

        case 4:
            PrintBooks(library);
            break;
       
        case 5:
            cout << "����� �� ���������.\n";
            break;
        default:
            cout << "������������ ����. ������� ����� �� 1 �� 5. ���������� �����.\n";
        }
    } while (choice != 6);

    return 0;
}