#ifndef lIBRARY_H
#define lIBRARY_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include "book.h"

class Library {
private:
    std::map<int, Book> books;   // STL container: key = book ID
    std::string filename;

public:
    Library(const std::string& file) : filename(file) {
        loadFromFile();
    }

    void addBook(int id, const std::string& title, const std::string& author) {
        if (books.find(id) != books.end()) {
            std::cout << "Error: A book with ID " << id << " already exists.\n";
            return;
        }
        books.emplace(id, Book(id, title, author));
        std::cout << "Book added successfully.\n";
    }

    void searchByTitle(const std::string& keyword) const {
        bool found = false;
        for (const auto& pair : books) {
            if (pair.second.getTitle().find(keyword) != std::string::npos) {
                pair.second.display();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No books found with title containing \"" << keyword << "\".\n";
        }
    }

    void listBooks() const {
        if (books.empty()) {
            std::cout << "The library has no books.\n";
            return;
        }
        for (const auto& pair : books) {
            pair.second.display();
        }
    }

    void issueBook(int id) {
        auto it = books.find(id);
        if (it == books.end()) {
            std::cout << "Error: No book found with ID " << id << ".\n";
            return;
        }
        if (!it->second.isAvailable()) {
            std::cout << "Error: Book " << id << " is already issued.\n";
            return;
        }
        it->second.setAvailable(false);
        std::cout << "Book issued successfully.\n";
    }

    void returnBook(int id) {
        auto it = books.find(id);
        if (it == books.end()) {
            std::cout << "Error: No book found with ID " << id << ".\n";
            return;
        }
        if (it->second.isAvailable()) {
            std::cout << "Error: Book " << id << " was not issued.\n";
            return;
        }
        it->second.setAvailable(true);
        std::cout << "Book returned successfully.\n";
    }

    // Load book data from CSV file at program start
    void loadFromFile() {
        std::ifstream in(filename);
        if (!in) return;   // file doesn't exist yet on first run

        std::string line;
        while (std::getline(in, line)) {
            std::stringstream ss(line);
            std::string idStr, title, author, availStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, title, ',');
            std::getline(ss, author, ',');
            std::getline(ss, availStr, ',');

            if (idStr.empty()) continue;

            int id = std::stoi(idStr);
            books.emplace(id, Book(id, title, author, availStr == "1"));
        }
    }

    // Save book data to CSV file
    void saveToFile() const {
        std::ofstream out(filename);
        for (const auto& pair : books) {
            const Book& b = pair.second;
            out << b.getId() << ','
                << b.getTitle() << ','
                << b.getAuthor() << ','
                << (b.isAvailable() ? 1 : 0) << '\n';
        }
        std::cout << "Data saved to " << filename << ".\n";
    }
};

#endif