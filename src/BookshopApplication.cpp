#include "../include/BookshopApplication/BookshopApplication.h"
#include <iomanip> 
#include <fstream>
#include <chrono>
#include <ctime>

BookshopApplication::BookshopApplication() : isLoggedIn(false) {
    loadData();
    loadInitialBooks();
}

void BookshopApplication::loadInitialBooks() {
    // Add some initial books to the 'books' vector
    Book book1 = {1, "The Catcher in the Rye", "J.D. Salinger", 15.99};
    Book book2 = {2, "To Kill a Mockingbird", "Harper Lee", 12.50};
    Book book3 = {3, "1984", "George Orwell", 10.75};
    Book book4 = {4, "Pride and Prejudice", "Jane Austen", 14.25};
    Book book5 = {5, "The Great Gatsby", "F. Scott Fitzgerald", 13.99};
    Book book6 = {6, "Moby-Dick", "Herman Melville", 18.50};
    Book book7 = {7, "The Odyssey", "Homer", 11.99};
    Book book8 = {8, "War and Peace", "Leo Tolstoy", 21.75};
    Book book9 = {9, "One Hundred Years of Solitude", "Gabriel García Márquez", 17.50};
    Book book10 = {10, "The Hobbit", "J.R.R. Tolkien", 14.99};
    Book book11 = {11, "Jane Eyre", "Charlotte Brontë", 12.25};
    Book book12 = {12, "The Lord of the Rings", "J.R.R. Tolkien", 24.99};
    Book book13 = {13, "The Count of Monte Cristo", "Alexandre Dumas", 16.75};
    Book book14 = {14, "Brave New World", "Aldous Huxley", 13.25};
    Book book15 = {15, "The Brothers Karamazov", "Fyodor Dostoevsky", 19.50};
    Book book16 = {16, "Anna Karenina", "Leo Tolstoy", 15.25};
    Book book17 = {17, "The Picture of Dorian Gray", "Oscar Wilde", 11.50};
    Book book18 = {18, "Wuthering Heights", "Emily Brontë", 12.99};
    Book book19 = {19, "Great Expectations", "Charles Dickens", 14.75};
    Book book20 = {20, "Frankenstein", "Mary Shelley", 10.99};

    books = {book1, book2, book3, book4, book5, book6, book7, book8, book9, book10,
             book11, book12, book13, book14, book15, book16, book17, book18, book19, book20};
}

void BookshopApplication::run() {
    int choice;
    while (true) {
        if (!isLoggedIn) {
             std::string username, password;

            std::cout << "Enter username: ";
            std::cin >> username;

            std::cout << "Enter password: ";
            std::cin >> password;

    // Call the login function with the entered username and password
            login(username, password);
        
        } else {
            displayMenu();
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    manageBooks();
                    break;
                case 2:
                    manageOrders();
                    break;
                case 3:
                    viewBooks();
                    break;
                case 4:
                    searchBooks();
                    break;
                case 5:
                    logout();  // Logout option
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
}

void BookshopApplication::login(const std::string& enteredUsername, const std::string& enteredPassword) {
    std::string username = enteredUsername;
    std::string password = enteredPassword;

    std::cout << "=============================================\n";
    std::cout << "           Welcome to Nethra Book Shop        \n";
    std::cout << "=============================================\n\n";
    
    // Check if the entered credentials match the default cashier account
    if (username == defaultUsername && password == defaultPassword) {
        std::cout << "Login successful!\n";
        isLoggedIn = true;
    } else {
        std::cout << "Invalid credentials.\n";
        // You can add code to create a new cashier account here
    }
}

void BookshopApplication::logout() {
    std::cout << "Logout successful!\n";
    isLoggedIn = false;
}

void BookshopApplication::displayMenu() {
    std::cout << "\n===== Nethra Book Shop =====\n";
    std::cout << "1. Manage Books\n";
    std::cout << "2. Manage Orders\n";
    std::cout << "3. View Books\n";
    std::cout << "4. Search Books\n";
    std::cout << "5. Logout\n";
    std::cout << "6. Exit\n";
}

void BookshopApplication::manageBooks() {
    int bookChoice;
    do {
        std::cout << "\n===== Manage Books =====\n";
        std::cout << "1. View Books\n";
        std::cout << "2. Add Book\n";
        std::cout << "3. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> bookChoice;

        switch (bookChoice) {
            case 1:
                viewBooks();
                break;
            case 2:
                addBook();
                break;
            case 3:
                break; // Return to the main menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (bookChoice != 3);
}

void BookshopApplication::viewBooks() {
    if (books.empty()) {
        std::cout << "No books available.\n";
        return;
    }

    std::cout << "===== List of Books =====\n";
    for (const Book& book : books) {
        std::cout << "ID: " << book.bookId << ", Title: " << book.title << ", Author: " << book.author << ", Price: RS:" << book.price << "\n";
    }
}

void BookshopApplication::addBook() {
    Book newBook;
    std::cout << "Enter book title: ";
    std::getline(std::cin >> std::ws, newBook.title);
    std::cout << "Enter author: ";
    std::getline(std::cin >> std::ws, newBook.author);

    // Input validation for price
    while (true) {
        std::cout << "Enter price: ";
        if (std::cin >> newBook.price) {
            // Input is a valid number, break out of the loop
            break;
        } else {
            // Clear the error flag
            std::cin.clear();
            // Discard invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Display error message
            std::cout << "Error: Enter a valid number for price.\n";
        }
    }

    newBook.bookId = books.size() + 1;
    books.push_back(newBook);

    std::cout << "Book added successfully.\n";
}

void BookshopApplication::searchBooks() {
    std::string keyword;
    std::cout << "Enter a keyword to search for books: ";
    std::getline(std::cin >> std::ws, keyword);

    if (keyword.empty()) {
        std::cout << "Invalid keyword. Please try again.\n";
        return;
    }

    // Convert the keyword to lowercase for case-insensitive comparison
    std::string lowercaseKeyword = keyword;
    std::transform(lowercaseKeyword.begin(), lowercaseKeyword.end(), lowercaseKeyword.begin(), ::tolower);

    // Search for the keyword in book titles and authors
    std::cout << "===== Search Results =====\n";
    for (const Book& book : books) {
        std::string lowercaseTitle = book.title;
        std::string lowercaseAuthor = book.author;
        std::transform(lowercaseTitle.begin(), lowercaseTitle.end(), lowercaseTitle.begin(), ::tolower);
        std::transform(lowercaseAuthor.begin(), lowercaseAuthor.end(), lowercaseAuthor.begin(), ::tolower);

        if (lowercaseTitle.find(lowercaseKeyword) != std::string::npos || lowercaseAuthor.find(lowercaseKeyword) != std::string::npos) {
            std::cout << "ID: " << book.bookId << ", Title: " << book.title << ", Author: " << book.author << ", Price: RS:" << book.price << "\n";
        }
    }
}

void BookshopApplication::manageOrders() {
    int orderChoice;
    do {
        std::cout << "\n===== Manage Orders =====\n";
        std::cout << "1. Place Order\n";
        std::cout << "2. View Orders\n";
        std::cout << "3. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> orderChoice;

        switch (orderChoice) {
            case 1:
                placeOrder();
                break;
            case 2:
                viewOrders();
                break;  
            case 3:
                break; // Return to the main menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (orderChoice != 4);
}

void BookshopApplication::addDiscount(Order& order) {
    int bookQuantity = order.books.size();

    if (bookQuantity > 20) {
        order.discount = 0.40 * order.totalAmount; // 40% discount for orders with more than 20 books
    } else if (bookQuantity > 10) {
        order.discount = 0.30 * order.totalAmount; // 30% discount for orders with more than 10 books
    } else if (bookQuantity > 5) {
        order.discount = 0.10 * order.totalAmount; // 10% discount for orders with more than 5 books
    }
}


void BookshopApplication::placeOrder() {
    if (books.empty()) {
        std::cout << "No books available to place an order.\n";
        return;
    }
    // Display the list of available books
    viewBooks();
    // Create a new order
    Order newOrder;
    newOrder.orderId = orders.size() + 1; // Assign a unique order ID
    // Select books for the order
    std::cout << "Enter the IDs of the books you want to order (enter 0 to finish):\n";
    int bookId;
    while (true) {
        std::cout << "Book ID: ";
        std::cin >> bookId;

        if (bookId == 0) {
            break; // User entered 0 to finish selecting books
        }
        // Check if the entered book ID is valid
        auto it = std::find_if(books.begin(), books.end(), [bookId](const Book& book) { return book.bookId == bookId; });
        if (it != books.end()) {
            newOrder.books.push_back(*it); // Add the selected book to the order
        } else {
            std::cout << "Invalid book ID. Please try again.\n";
        }
    }
    // Calculate the total amount for the order
    newOrder.totalAmount = 0.0;
    for (const Book& book : newOrder.books) {
        newOrder.totalAmount += book.price;
    }
    // Apply discount based on the quantity of books
    addDiscount(newOrder);
    // Add the order to the list of orders
    orders.push_back(newOrder);
    // Print the beautiful receipt
    printReceipt(newOrder);
    std::cout << "Order placed successfully!\n";
}

void BookshopApplication::printReceipt(const Order& order) {
    if (order.books.empty()) {
        std::cout << "Error: No books in the order.\n";
        return;
    }

    std::cout << "==================== Receipt ====================\n";
    std::cout << std::left << std::setw(15) << "Order ID:" << std::setw(10) << order.orderId << "\n";
    std::cout << std::left << std::setw(15) << "Customer:" << std::setw(10) << getCustomerName() << "\n";
    std::cout << std::left << std::setw(15) << "Date:" << std::setw(10) << getCurrentDate() << "\n";

    // Display book details in the order
    std::cout << "================= Books in the Order =================\n";
    std::cout << std::setw(30) << std::left << "Title" << std::setw(30) << "Author" << std::setw(10) << "Price\n";
    
    for (const Book& book : order.books) {
        std::cout << std::setw(30) << std::left << book.title << std::setw(30) << book.author << std::fixed << std::setprecision(2) << "RS" << book.price << "\n";
    }

    std::cout << "=====================================================\n";
    std::cout << std::setw(65) << std::left << "Total Amount:" << std::fixed << std::setprecision(2) << "$" << order.totalAmount << "\n";
    std::cout << std::setw(65) << std::left << "Discount:" << std::fixed << std::setprecision(2) << "$" << order.discount << "\n";

    // Calculate and display the final amount after applying the discount
    double finalAmount = order.totalAmount - order.discount;
    std::cout << std::setw(65) << std::left << "Final Amount:" << std::fixed << std::setprecision(2) << "$" << finalAmount << "\n";
    std::cout << "=====================================================\n";
}

void BookshopApplication::viewOrders() {
    if (orders.empty()) {
        std::cout << "No orders available.\n";
        return;
    }

    std::cout << "===== List of Orders =====\n";
    for (const Order& order : orders) {
        std::cout << "Order ID: " << order.orderId << ", Total Amount: $" << order.totalAmount << ", Discount: $" << order.discount << "\n";
    }
}

void BookshopApplication::saveData() {
    saveBooks();
    saveOrders();
}

void BookshopApplication::saveBooks() {
    std::ofstream bookFile("data/books.txt");
    if (bookFile.is_open()) {
        for (const Book& book : books) {
            bookFile << book.bookId << "," << book.title << "," << book.author << "," << book.price << "\n";
        }
        bookFile.close();
        std::cout << "Books data saved successfully.\n";
    } else {
        std::cout << "Error saving books data.\n";
    }
}

void BookshopApplication::saveOrders() {
    std::ofstream orderFile("data/orders.txt");
    if (orderFile.is_open()) {
        for (const Order& order : orders) {
            orderFile << order.orderId << ",";
            for (const Book& book : order.books) {
                orderFile << book.bookId << ",";
            }
            orderFile << "-1,"; // Mark the end of book IDs
            orderFile << order.totalAmount << "," << order.discount << "\n";
        }
        orderFile.close();
        std::cout << "Orders data saved successfully.\n";
    } else {
        std::cout << "Error saving orders data.\n";
    }
}

void BookshopApplication::loadData() {
    loadBooks();
    loadOrders();
}

void BookshopApplication::loadBooks() {
    std::ifstream bookFile("data/books.txt");

    if (!bookFile.is_open()) {
        std::cout << "Error opening books file. Creating an empty list.\n";
        return;
    }

    Book book;
    while (bookFile >> book.bookId >> std::ws && std::getline(bookFile, book.title, ',') >> std::ws && std::getline(bookFile, book.author, ',') >> std::ws && bookFile >> book.price) {
        books.push_back(book);
    }

    bookFile.close();
}

void BookshopApplication::loadOrders() {
    std::ifstream orderFile("data/orders.txt");

    if (!orderFile.is_open()) {
        std::cout << "Error opening orders file. Creating an empty list.\n";
        return;
    }

    Order order;
    while (orderFile >> order.orderId >> std::ws) {
        // Read book IDs until a newline character is encountered
        int bookId;
        while (orderFile >> bookId && bookId != -1) {
            auto it = std::find_if(books.begin(), books.end(), [bookId](const Book& book) {
                return book.bookId == bookId;
            });

            if (it != books.end()) {
                order.books.push_back(*it);
            }
        }

        orderFile >> order.totalAmount >> order.discount;
        orders.push_back(order);

        // Clear the vector for the next order
        order.books.clear();
    }

    orderFile.close();
}

std::string BookshopApplication::getCustomerName() const {
    // Implement the logic to retrieve the customer name
    // For example, you can prompt the user to enter their name
    std::string customerName;
    std::cout << "Enter customer name: ";
    std::getline(std::cin >> std::ws, customerName);
    return customerName;
}

std::string BookshopApplication::getCurrentDate() const {
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a string representing the current date
    std::string currentDate = std::ctime(&currentTime);

    // Remove the newline character from the end of the string
    currentDate.pop_back();

    return currentDate;
}