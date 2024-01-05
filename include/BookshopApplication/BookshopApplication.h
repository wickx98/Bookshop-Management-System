// BookshopApplication.h
#ifndef BOOKSHOP_APPLICATION_H
#define BOOKSHOP_APPLICATION_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

// Structure to represent a book
struct Book {
    int bookId;
    std::string title;
    std::string author;
    double price;
};

// Structure to represent an order
struct Order {
    int orderId;
    std::vector<Book> books;
    double totalAmount;
    double discount;
};

// Main class for the Bookshop Application
class BookshopApplication {
public:
    BookshopApplication();  // Constructor

    void login(const std::string& enteredUsername, const std::string& enteredPassword);
    void run();

private:
    std::vector<Book> books;  // Vector to store books
    std::vector<Order> orders;  // Vector to store orders

    bool isLoggedIn;  // Variable to track whether a cashier is logged in

    // Credentials for the default cashier account
    const std::string defaultUsername = "admin";
    const std::string defaultPassword = "admin123";

    // Helper functions for customer information
    std::string getCustomerName() const;
    std::string getCurrentDate() const;

    // Functions for various bookshop functionalities
    void displayMenu();
    void manageBooks();
    void viewBooks();
    void addBook();
    void searchBooks();
    void placeOrder();
    void manageOrders();
    void viewOrders();
    void addDiscount(Order& order);
    void printReceipt(const Order& order);
    void saveData();
    void loadData();
    void loadBooks();
    void loadOrders();
    int getBookQuantity(const Order& order) const;

    // Functions for user authentication
    void login();
    void logout();

    // Function to load initial books into the system
    void loadInitialBooks();

    // Functions for data persistence
    void saveBooks();
    void saveOrders();

    friend void testLogin();
    friend void testAddBook();
};

#endif // BOOKSHOP_APPLICATION_H
