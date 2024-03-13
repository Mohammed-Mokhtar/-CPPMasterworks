#include <bits/stdc++.h>
#define io                 \
  ios::sync_with_stdio(0); \
  cin.tie(NULL);           \
  cout.tie(NULL);
using namespace std;
const int max_specialization = 20;
const int max_queue = 5;
// Arrays to store patient names, statuses, and queue lengths for each specialization
string names[max_specialization + 1][max_queue + 1];
int Statuses[max_specialization + 1][max_queue + 1];
int queue_length[max_specialization + 1];

// Function to shift elements to the right in the queue
void sheft_right(int specialization, string name, int status)
{
  for (int i = queue_length[specialization] + 1; i > 1; i--)
  {
    names[specialization][i] = names[specialization][i - 1];
    Statuses[specialization][i] = Statuses[specialization][i - 1];
  }
  names[specialization][1] = name;
  Statuses[specialization][1] = status;
}

// Function to shift elements to the left in the queue
void sheft_left(int specialization)
{
  for (int i = 0; i <= queue_length[specialization]; i++)
  {
    names[specialization][i] = names[specialization][i + 1];
    Statuses[specialization][i] = Statuses[specialization][i + 1];
  }
  queue_length[specialization]--;
}

// Function to display menu and get user choice
int menu()
{
  cout << "\nEnter your choice: \n";
  cout << "1) Add new patient\n";
  cout << "2) Print all patients\n";
  cout << "3) Get next patient\n";
  cout << "4) Exit\n";
  int choice;
  cin >> choice;
  return choice;
}

// Function to add new patients to the queue
void add_patients()
{
  cout << "Enter specilization, name, status: ";
  int specialization;
  string name;
  int status;
  cin >> specialization >> name >> status;
  if (queue_length[specialization] == 5)
  {
    cout << "Sorry we can't add more patients for this specilaization\n";
  }
  else if (status == 1)
  {
    queue_length[specialization]++;
    sheft_right(specialization, name, status);
  }
  else
  {
    queue_length[specialization]++;
    names[specialization][queue_length[specialization]] = name;
    Statuses[specialization][queue_length[specialization]] = status;
  }
}

// Function to print all patients in the queue
void print_patients()
{
  cout << "******************\n";
  for (int i = 1; i <= max_specialization + 1; i++)
  {
    if (queue_length[i] > 0)
    {
      cout << "There are " << queue_length[i] << " patients in specialization " << i << '\n';
      for (int j = 1; j <= queue_length[i]; j++)
      {
        cout << names[i][j] << " ";
        if (Statuses[i][j] == 0)
        {
          cout << "regular\n";
        }
        else
          cout << "urgent\n";
      }
      cout << '\n';
    }
  }
  cout << '\n';
}

// Function to get the next patient for a given specialization
void get_next_patients()
{
  cout << "Enter specialization: ";
  int specialization;
  cin >> specialization;
  if (queue_length[specialization] > 0)
  {
    cout << names[specialization][1] << " please go with Dr\n\n";
    sheft_left(specialization);
  }
  else
  {
    cout << "No patients at the moment. Have rest, Dr\n\n";
  }
}

// Function to manage the hospital system operations
void hospital_system()
{
  while (true)
  {
    int choice = menu();
    if (choice == 1)
      add_patients();
    else if (choice == 2)
      print_patients();
    else if (choice == 3)
      get_next_patients();
    else
      break;
  }
}

int main()
{
  hospital_system();
  return 0;
}
