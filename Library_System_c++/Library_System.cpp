#include <bits/stdc++.h>
#define io                 \
  ios::sync_with_stdio(0); \
  cin.tie(NULL);           \
  cout.tie(NULL);
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
const double MX = 1e5 + 5;
const double eps = 1e-9;
const double pi = 3.141592653589793238;

// Function to shift elements of an array to the left
void shift_left(int arr[], int indexToRemove, int &len)
{
  for (int i = indexToRemove; i < len; i++)
  {
    arr[i] = arr[i + 1];
  }
  len--;
}

// Function to shift elements of an array of strings to the left
void shift_left(string arr[], int indexToRemove, int &len)
{
  for (int i = indexToRemove; i < len; i++)
  {
    arr[i] = arr[i + 1];
  }
  len--;
}

// Definition of the user structure
struct user
{
  string name_user;
  int id_user;
  int book_id[100];
  int len_book_id;
  user()
  {
    len_book_id = 0;
    id_user = 0;
  }

  // Function to add a user with a name and ID
  void add_user(string name, int id)
  {
    name_user = name;
    id_user = id;
  }

  // Function to add a borrowed book ID to the user's record
  void add_borrowed_book(int bor_book_id)
  {
    book_id[len_book_id] = bor_book_id;
    len_book_id++;
  }

  // Function to remove a borrowed book from the user's record
  void remove_borrowed_book(int return_book_id)
  {
    for (int i = 0; i < len_book_id; i++)
    {
      if (book_id[i] == return_book_id)
      {
        shift_left(book_id, i, len_book_id);
        break;
      }
    }
  }

  // Function to print the IDs of borrowed books by the user
  void print_books_id()
  {
    for (int i = 0; i < len_book_id; i++)
    {
      cout << book_id[i] << " ";
    }
  }
};

// Definition of the book structure
struct book
{
  int ids;
  string name_book;
  int total_quantity;
  int total_borrowed;
  string user_borrow[100];
  int len_user_borrow;
  book()
  {
    ids = 0;
    total_quantity = 0;
    total_borrowed = 0;
    len_user_borrow = 0;
  }

  // Function to add a book at the end with ID, name, and quantity
  void add_end(int id, string name, int quantity)
  {
    ids = id;
    name_book = name;
    total_quantity = quantity;
  }

  // Function to add a user who borrowed the book
  void add_user_borrow(string user_name)
  {
    user_borrow[len_user_borrow] = user_name;
    len_user_borrow++;
  }

  // Function to remove a user who returned the book
  void remove_user_borrow(string user_name)
  {
    for (int i = 0; i < len_user_borrow; i++)
    {
      if (user_borrow[i] == user_name)
      {
        shift_left(user_borrow, i, len_user_borrow);
      }
    }
  }

  // Function to print the names of users who borrowed the book
  void print_user_borrow()
  {
    for (int i = 0; i < len_user_borrow; i++)
    {
      cout << user_borrow[i] << '\n';
    }
  }
};

// Comparison functions for sorting books by ID and name
bool compare_id(book &a, book &b)
{
  return a.ids < b.ids;
}

bool compare_name(book &a, book &b)
{
  return a.name_book < b.name_book;
}

// Definition of the library system
struct library_system
{
  book books[100];
  user users[100];
  int len_book;
  int len_user;
  library_system()
  {
    len_book = 0;
    len_user = 0;
    for (int i = 0; i < 100; i++)
    {
      books[i] = book();
    }
    for (int i = 0; i < 100; i++)
    {
      users[i] = user();
    }
  }

  // Main function to run the library system
  void run()
  {
    while (true)
    {
      int choice = menu();
      if (choice == 1)
        add_book();
      else if (choice == 2)
        search_books_by_prefix();
      else if (choice == 3)
        print_who_borrowed_book_by_name();
      else if (choice == 4)
        print_library_by_id();
      else if (choice == 5)
        print_library_by_name();
      else if (choice == 6)
        add_user();
      else if (choice == 7)
        user_borrow_book();
      else if (choice == 8)
        user_return_book();
      else if (choice == 9)
        print_users();
      else
        break;
    }
  }

  // Function to display the menu and get user's choice
  int menu()
  {
    int choice = -1;
    while (choice == -1)
    {
      cout << "\nLibrary Menu;\n";
      cout << "1) add_book\n";
      cout << "2) search_books_by_prefix\n";
      cout << "3) print_who_borrowed_book_by_name\n";
      cout << "4) print_library_by_id\n";
      cout << "5) print_library_by_name\n";
      cout << "6) add_user\n";
      cout << "7) user_borrow_book\n";
      cout << "8) user_return_book\n";
      cout << "9) print_users\n";
      cout << "10) Exit\n\n";
      cout << "Enter your menu choice [1 - 10]: ";
      if (!(cin >> choice))
      {
        // If input cannot be converted to integer, clear the input stream and ignore the rest of the line
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid menu choice.\n";
      }
      if (!(1 <= choice && choice <= 10))
      {
        cout << "Invalid choice. Try again\n";
        choice = -1;
      }
    }
    return choice;
  }

  // Function to add a book to the library
  void add_book()
  {
    int id, quantity;
    string name;
    cout << "Enter book info:id & name & total quantity: ";
    cin >> id >> name >> quantity;
    books[len_book].add_end(id, name, quantity);
    len_book++;
  }

  // Function to print the library inventory sorted by ID
  void print_library_by_id()
  {
    cout << "\n";
    sort(books, books + len_book, compare_id);
    for (int i = 0; i < len_book; i++)
    {
      cout << "id = " << books[i].ids << " name = " << books[i].name_book << " total_quantity " << books[i].total_quantity << " total_borrowed " << books[i].total_borrowed << "\n";
    }
  }

  // Function to print the library inventory sorted by name
  void print_library_by_name()
  {
    cout << "\n";
    sort(books, books + len_book, compare_name);
    for (int i = 0; i < len_book; i++)
    {
      cout << "id = " << books[i].ids << " name = " << books[i].name_book << " total_quantity " << books[i].total_quantity << " total_borrowed " << books[i].total_borrowed << "\n";
    }
  }

  // Function to search for books by name prefix
  void search_books_by_prefix()
  {
    string name;

    cout << "Enter book name prefix: ";
    cin >> name;
    bool flag2 = false;
    for (int i = 0; i < len_book; i++)
    {
      bool flag = true;
      for (int j = 0; j < name.size(); j++)
      {
        char nbook = books[i].name_book[j];
        if (name[j] != nbook)
        {
          flag = false;
          break;
        }
      }
      if (flag)
      {
        flag2 = true;
        cout << books[i].name_book << '\n';
      }
    }
    if (!flag2)
      cout << "No books with such prefix\n";
  }

  // Function to add a user to the library
  void add_user()
  {
    string name;
    int nat_id;
    cout << "Enter your name & national id: ";
    cin >> name >> nat_id;
    users[len_user].add_user(name, nat_id);
    len_user++;
  }

  // Function for a user to borrow a book
  void user_borrow_book()
  {
    string name, book_name;
    cout << "Enter user name and book name: ";
    cin >> name >> book_name;
    for (int i = 0; i < len_user; i++)
    {
      if (name == users[i].name_user)
      {
        for (int j = 0; j < len_book; j++)
        {
          if (books[j].name_book == book_name)
          {
            if (books[j].total_quantity > 0)
            {
              books[j].add_user_borrow(name);
              users[i].add_borrowed_book(books[j].ids);
              books[j].total_quantity--;
              books[j].total_borrowed++;
            }
            else
            {
              cout << "Book out of stock.\n";
            }
          }
        }
      }
    }
  }

  // Function to print users and their borrowed books
  void print_users()
  {
    for (int i = 0; i < len_user; i++)
    {
      cout << "user " << users[i].name_user << " id " << users[i].id_user << " borrowed books ids: ";
      users[i].print_books_id();
      cout << '\n';
    }
  }

  // Function to print users who borrowed a specific book
  void print_who_borrowed_book_by_name()
  {
    string book_name;
    cout << "Enter book name: ";
    cin >> book_name;
    bool flag = false;
    for (int i = 0; i < len_book; i++)
    {
      if (books[i].name_book == book_name)
      {
        flag = true;
        books[i].print_user_borrow();
      }
    }
    if (!flag)
    {
      cout << "Invalid book name\n";
    }
  }

  // Function for a user to return a book
  void user_return_book()
  {
    string name, book_name;
    cout << "Enter user name and book name: ";
    cin >> name >> book_name;
    for (int i = 0; i < len_user; i++)
    {
      if (name == users[i].name_user)
      {
        for (int j = 0; j < len_book; j++)
        {
          if (books[j].name_book == book_name)
          {
            users[i].remove_borrowed_book(books[j].ids);
            books[j].remove_user_borrow(name);
            books[j].total_borrowed--;
            books[j].total_quantity++;
          }
        }
      }
    }
  }
};

// Main function
int main()
{
  // Initialize the library system and run it
  library_system library = library_system();
  library.run();
  return 0;
}
