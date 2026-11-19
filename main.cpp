#include <iostream>
#include <limits>
#include <string>
#include "library.h"

// Reads an integer safely; re-asks if the input is not a number
int readInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Reads a full line of text (titles/authors can have spaces)
std::string readLine(const std::string& prompt) {
    std::string text;
    std::cout << prompt;
    std::getline(std::cin, text);
    return text;
}

int main() {
    Library library("library.csv");
    int choice;

    do {
        std::cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n"
                  << "1. Add book\n"
                  << "2. Search book by title\n"
                  << "3. List all books\n"
                  << "4. Issue book\n"
                  << "5. Return book\n"
                  << "0. Save and exit\n"
                  << "Enter choice: ";
        choice = readInt("");

        switch (choice) {
            case 1: {
                int id = readInt("Enter book ID: ");
                std::string title = readLine("Enter title: ");
                std::string author = readLine("Enter author: ");
                library.addBook(id, title, author);
                break;
            }
            case 2: {
                std::string keyword = readLine("Enter title to search: ");
                library.searchByTitle(keyword);
                break;
            }
            case 3:
                library.listBooks();
                break;
            case 4: {
                int id = readInt("Enter book ID to issue: ");
                library.issueBook(id);
                break;
            }
            case 5: {
                int id = readInt("Enter book ID to return: ");
                library.returnBook(id);
                break;
            }
            case 0:
                library.saveToFile();
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}