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

const int MAX_BOOKS = 10;
const int MAX_USERS = 10;

struct book
{
  int id;
  string name;
  int total_quantity;
  int total_borrowed;
  book()
  {
    total_quantity = total_borrowed = 0;
    id = -1;
    name = "";
  }
  void read()
  {
    cout << "Enter book info: id & name & total quantity: ";
    cin >> id >> name >> total_quantity;
    total_borrowed = 0;
  }

  bool has_prefix(string prefix)
  {
    if (name.size() < prefix.size())
      return false;

    for (int i = 0; i < (int)prefix.size(); i++)
    {
      if (prefix[i] != name[i])
        return false;
    }
    return true;
  }

  void print()
  {
    cout << "id = " << id << " name = " << name << " total_quantity "
         << total_quantity << " total_borrowed " << total_borrowed
         << "\n";
  }

  bool borrow(int user_id)
  {
    if (total_quantity - total_borrowed == 0)
      return false;
    total_borrowed++;
    return true;
  }

  void return_copy()
  {
    assert(total_borrowed > 0);
    total_borrowed--;
  }
};
bool cmp_book_by_name(book &a, book &b)
{
  return a.name < b.name;
}
bool cmp_book_by_id(book &a, book &b)
{
  return a.id < b.id;
}

struct user
{
  int id;
  string name;

  set<int> borrowed_books_ids;

  user()
  {
    name = "";
    id = -1;
  }

  void read()
  {
    cout << "Enter user name & national id: ";
    cin >> name >> id;
  }

  void print()
  {
    cout << "user " << name << " id " << id << " borrowed books ids: ";
    for (int book_id : borrowed_books_ids)
      cout << book_id << " ";
    cout << "\n";
  }

  void borrow(int book_id)
  {
    borrowed_books_ids.insert(book_id);
  }

  bool is_borrowed(int book_id)
  {
    auto it = borrowed_books_ids.find(book_id);
    return it != borrowed_books_ids.end();
  }

  void return_copy(int book_id)
  {
    auto it = borrowed_books_ids.find(book_id);
    if (it != borrowed_books_ids.end())
      borrowed_books_ids.erase(it);
    else
      cout << "User " << name << " never borrowed book id " << book_id
           << "\n";
  }
};

struct library_system
{
  vector<book> books;
  vector<user> users;

  library_system()
  {
  }
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

  int menu()
  {
    int choice = -1;
    while (choice == -1)
    {
      cout << "\nLibrary Menu;\n";
      cout << "1) add_book\n";
      cout << "2) search_books_by_prefix\n";
      cout << "3)print_who_borrowed_book_by_name\n";
      cout << "4) print_library_by_id\n";
      cout << "5) print_library_by_name\n";
      cout << "6) add_user\n";
      cout << "7) user_borrow_book\n";
      cout << "8) user_return_book\n";
      cout << "9) print_users\n";
      cout << "10) Exit\n";

      cout << "\nEnter your menu choice [1 - 10]";

      cin >> choice;
      if (!(1 <= choice && choice <= 10))
      {
        cout << "Invalid choice. Try again\n";
        choice = -1;
      }
    }
    return choice;
  }

  void add_book()
  {
    book b;
    b.read();
    books.push_back(b);
  }

  void search_books_by_prefix()
  {
    cout << "Enter book name prefix: ";
    string prefix;
    cin >> prefix;

    int cnt = 0;
    for (book &b : books)
    {
      if (b.has_prefix(prefix))
      {
        cout << b.name << "\n";
        cnt++;
      }
    }
    if (!cnt)
      cout << "No books with such prefix\n";
  }

  void add_user()
  {
    user u;
    u.read();
    users.push_back(u);
  }

  void print_library_by_id()
  {
    sort(books.begin(), books.end(), cmp_book_by_id);

    cout << "\n";
    for (book &b : books)
      b.print();
  }

  void print_library_by_name()
  {
    sort(books.begin(), books.end(), cmp_book_by_name);

    cout << "\n";
    for (book &b : books)
      b.print();
  }

  void print_users()
  {
    cout << "\n";
    for (user &u : users)
      u.print();
  }

  int find_user_idx_by_name(string name)
  {
    for (int i = 0; i < (int)users.size(); i++)
    {
      if (name == users[i].name)
        return i;
    }
    return -1;
  }
  int find_book_idx_by_name(string name)
  {
    for (int i = 0; i < (int)books.size(); i++)
    {
      if (name == books[i].name)
        return i;
    }
    return -1;
  }

  bool read_user_name_and_book_name(int &user_idx, int &book_idx, int trials = 5)
  {
    string user_name;
    string book_name;

    while (trials--)
    {
      cout << "Enter user name and book name: ";
      cin >> user_name >> book_name;

      user_idx = find_user_idx_by_name(user_name);

      if (user_idx == -1)
      {
        cout << "Invalid user name. Try again\n";
        continue;
      }
      book_idx = find_book_idx_by_name(book_name);

      if (book_idx == -1)
      {
        cout << "Invalid book name. Try again\n";
        continue;
      }
      return true;
    }
    cout << "You did several tirals! Try later.";
    return false;
  }

  void user_borrow_book()
  {
    int user_idx, book_idx;
    if (!read_user_name_and_book_name(user_idx, book_idx))
      return;

    int user_id = users[user_idx].id;
    int book_id = books[book_idx].id;

    if (!books[book_idx].borrow(user_id))
      cout << "NO more copies available right now\n";
    else
      users[user_idx].borrow(book_id);
  }

  void user_return_book()
  {
    int user_idx, book_idx;
    if (!read_user_name_and_book_name(user_idx, book_idx))
      return;
    int book_id = books[book_idx].id;
    books[book_idx].return_copy();
    users[user_idx].return_copy(book_id);
  }

  void print_who_borrowed_book_by_name()
  {
    string book_name;
    cout << "Enter book name: ";
    cin >> book_name;
    int book_idx = find_book_idx_by_name(book_name);

    if (book_idx == -1)
    {
      cout << "Invalid book name.\n";
      return;
    }
    int book_id = books[book_idx].id;

    if (books[book_idx].total_borrowed == 0)
    {
      cout << "No borrowed copies\n";
      return;
    }
    for (user &u : users)
    {
      if (u.is_borrowed(book_id))
        cout << u.name << "\n";
    }
  }
};

int main()
{
  library_system library;

  library.run();

  return 0;
}
