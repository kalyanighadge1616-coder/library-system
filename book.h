#ifndef bOOK_H
#define bOOK_H

#include <iostream>
#include <string>

// Encapsulation: data is private, accessed through getters/setters
class Book {
private:
    int id;
    std::string title;
    std::string author;
    bool available;

public:
    Book(int id, const std::string& title, const std::string& author, bool available = true)
        : id(id), title(title), author(author), available(available) {}

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    bool isAvailable() const { return available; }

    void setAvailable(bool status) { available = status; }

    void display() const {
        std::cout << "ID: " << id
                  << " | Title: " << title
                  << " | Author: " << author
                  << " | " << (available ? "Available" : "Issued") << "\n";
    }
};

#endif 