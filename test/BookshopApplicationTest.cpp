#include "../include/BookshopApplication/BookshopApplication.h"
#include <cassert>	// assert()
#include <iostream>	// std::cout


void testLogin() {
    BookshopApplication app;

    // Test with correct credentials
    app.login("admin", "admin123");
    assert(app.isLoggedIn);
    std::cout << "Login with correct credentials: Passed\n";

    // Test with incorrect credentials
    app.login("wrong_username", "wrong_password");
    assert(!app.isLoggedIn);
    std::cout << "Login with incorrect credentials: Passed\n";
}

void testAddBook() {
    BookshopApplication app;
    int initialBooksCount = app.books.size();

    // Test adding a book
    Book testBook = {21, "Test Book", "Test Author", 19.99};
    app.books.push_back(testBook);
    assert(app.books.size() == initialBooksCount + 1);
    std::cout << "Add Book: Passed\n";
}

int main() {
    // Run your tests
    testLogin();
    testAddBook();

    return 0;
}
