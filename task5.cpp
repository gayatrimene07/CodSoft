#include <iostream>
#include <string>

using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book() : isAvailable(true) {}

    void inputBookDetails() {
        cout << "Enter title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, ISBN);
    }

    void displayBookDetails() const {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class Library {
private:
    Book books[100];
    int bookCount;
    struct BorrowInfo {
        string ISBN;
        int borrowDays;
    } borrowedBooks[100];
    int borrowedCount;
    const double finePerDay = 1.0;

public:
    Library() : bookCount(0), borrowedCount(0) {}

    void addBook() {
        if (bookCount < 100) {
            books[bookCount].inputBookDetails();
            bookCount++;
        } else {
            cout << "Library is full, cannot add more books." << endl;
        }
    }

    void searchBook() {
        string query, type;
        cout << "Search by (title/author/ISBN): ";
        cin >> type;
        cout << "Enter " << type << ": ";
        cin.ignore();
        getline(cin, query);

        for (int i = 0; i < bookCount; ++i) {
            if ((type == "title" && books[i].title == query) || 
                (type == "author" && books[i].author == query) || 
                (type == "ISBN" && books[i].ISBN == query)) {
                books[i].displayBookDetails();
            }
        }
    }

    void checkoutBook() {
        string ISBN;
        cout << "Enter ISBN of the book to checkout: ";
        cin.ignore();
        getline(cin, ISBN);

        for (int i = 0; i < bookCount; ++i) {
            if (books[i].ISBN == ISBN && books[i].isAvailable) {
                books[i].isAvailable = false;
                borrowedBooks[borrowedCount].ISBN = ISBN;
                cout << "Enter the number of days for borrowing: ";
                cin >> borrowedBooks[borrowedCount].borrowDays;
                borrowedCount++;
                cout << "Book checked out successfully." << endl;
                return;
            }
        }
        cout << "Book not available." << endl;
    }

    void returnBook() {
        string ISBN;
        int returnDays;
        cout << "Enter ISBN of the book to return: ";
        cin.ignore();
        getline(cin, ISBN);

        for (int i = 0; i < borrowedCount; ++i) {
            if (borrowedBooks[i].ISBN == ISBN) {
                cout << "Enter the number of days since the book was borrowed: ";
                cin >> returnDays;

                for (int j = 0; j < bookCount; ++j) {
                    if (books[j].ISBN == ISBN) {
                        books[j].isAvailable = true;
                        break;
                    }
                }

                double fine = calculateFine(borrowedBooks[i].borrowDays, returnDays);
                borrowedBooks[i] = borrowedBooks[--borrowedCount]; // remove the entry
                cout << "Book returned successfully. Fine: $" << fine << endl;
                return;
            }
        }
        cout << "Book not found in borrowed list." << endl;
    }

    double calculateFine(int borrowDays, int returnDays) const {
        if (returnDays > borrowDays + 14) { // Assuming a 2-week loan period
            return (returnDays - (borrowDays + 14)) * finePerDay;
        }
        return 0;
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            library.addBook();
            break;
        case 2:
            library.searchBook();
            break;
        case 3:
            library.checkoutBook();
            break;
        case 4:
            library.returnBook();
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
