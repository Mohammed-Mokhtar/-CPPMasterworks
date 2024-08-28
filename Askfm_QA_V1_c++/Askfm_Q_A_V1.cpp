#include <bits/stdc++.h>
#define io                 \
  ios::sync_with_stdio(0); \
  cin.tie(NULL);           \
  cout.tie(NULL);
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;

struct Question
{
  int questionId;
  string question;
  string answer;
  bool aq;
  int fromUserId;
  int ToUserId;
  vector<Question> threads;
  Question()
  {
    questionId = -1;
    question = "";
    answer = "";
    aq = false;
  }
  void readQuestion(int _questionId, string _question, bool _aq, int _fromUserId, int _toUserId)
  {
    questionId = _questionId;
    question = _question;
    aq = _aq;
    fromUserId = _fromUserId;
    ToUserId = _toUserId;
  }
  void print()
  {
    cout << "Question Id (" << questionId << ")" << (aq ? "" : " from user id(" + to_string(fromUserId) + ")") << "\t Question: " << question << endl
         << "\t" << (answer.empty() ? "There is No Answer Yet\n" : "Answer: " + answer) << "\n";
    for (auto thread : threads)
    {
      cout << "\tThread: Question Id(" << thread.questionId << ")" << (aq ? "" : " from user id(" + to_string(thread.fromUserId) + ")") << ")\tQuestion: " << thread.question << endl
           << "\tThread:\t" << (thread.answer.empty() ? "There is No Answer Yet\n" : "Answer: " + thread.answer) << "\n";
    }
  }
};

struct User
{
  int userId;
  string name,
      email,
      password,
      username;
  bool aq;
  // vector<Question> fromUserQuestions;
  // vector<Question> toUserQuestions;
  User()
  {
    userId = -1;
    name = "";
    email = "";
    password = "";
  }
};

struct AskMeSystem
{
  vector<User> users;
  vector<Question> questions;
  User fromUser;
  User toUser;
  Question *q;
  int userId;
  int questionId;
  int threadId;
  AskMeSystem()
  {
    userId = 1;
    questionId = 100;
    threadId = 200;
  }
  void run()
  {
    int choice;

    while (true)
    {
      bool validLogin;
      choice = loginMenu();
      if (choice == 1)
      {
        validLogin = login();
        if (validLogin)
        {
          break;
        }
      }
      if (choice == 2)
      {
        signUp();
        break;
      }
    }

    while (true)
    {
      choice = mainMenu();
      switch (choice)
      {
      case 1:
        printQuestionToMe();
        break;
      case 2:
        printQuestionFromMe();
        break;
      case 3:
        answerQuestion();
        break;
      case 4:
        deleteQuestion();
        break;
      case 5:
        askQuestion();
        break;
      case 6:
        listSystemUsers();
        break;
      case 7:
        feed();
        break;
      case 8:
        cout << "Logging out...\n";
        return run(); // Return to the outer loop instead of calling run() recursively
      default:
        cout << "Invalid choice. Please try again.\n";
        break;
      }
    }
  }

  int loginMenu()
  {
    int userChoice;
    while (true)
    {
      cout << "\nMenu:\n"
           << "\t1: Login\n"
           << "\t2: Sign Up\n";
      cout << "Enter a number (1 or 2): ";
      cin >> userChoice;

      if (cin.fail())
      {
        cin.clear();               // clear the error flag
        cin.ignore(INT_MAX, '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number (1 or 2):\n";
      }
      else if (userChoice == 1 || userChoice == 2)
      {
        return userChoice;
      }
      else
      {
        cout << "Please enter a choice between 1 and 2:\n";
      }
    }
  }

  void signUp()
  {
    cout << "SignUp:\n";
    cout << "Enter Your Full name: ";
    string fullname;
    getline(cin >> ws, fullname);
    fromUser.name = fullname;

    cout << "Enter Your Email: ";
    string email;
    while (true)
    {
      cin >> email;
      fromUser.email = email;
      bool validEmail = checkEmail(email);
      if (validEmail)
        break;
      else
        cout << "This Email is Already Taked Please Enter a new Email\n";
    }
    cout << "Enter a username and it must be unique: ";
    string username;
    while (true)
    {
      cin >> username;
      fromUser.username = username;
      bool validUser = checkUsername(username);
      if (validUser)
        break;
      else
        cout << "This Username is Already Taked Please Enter a new username\n";
    }
    cout << "Enter a password: ";
    string password;
    cin >> password;
    fromUser.password = password;
    cout << "Allow Anonymous press(1) Or not press(0): ";
    bool anonymous;
    cin >> anonymous;
    fromUser.aq = anonymous;
    fromUser.userId = userId++;
    users.push_back(fromUser);
  }

  bool login()
  {
    string username;
    string password;
    while (true)
    {
      cout << "Enter Your Username: ";
      cin >> username;
      bool notValidUsername = checkUsername(username);
      cout << "Enter Your Passowrd: ";
      cin >> password;
      bool notValidPassword = checkPassword(password, fromUser);
      if (notValidUsername || notValidPassword)
      {
        cout << "Username or Passowrd is Wrong please try again!\n";
        return false;
      }
      else
        return true;
    }
  }

  bool checkEmail(string email)
  {
    for (auto &user : users)
    {
      if (user.email == email)
      {
        return false;
      }
    }
    return true;
  }

  bool checkUserId(int id, User &_user)
  {
    for (auto &user : users)
    {
      if (user.userId == id)
      {
        _user = user;
        return true;
      }
    }
    return false;
  }

  bool checkQuestionId(int qId)
  {
    for (auto &question : questions)
    {
      if (question.questionId == qId)
      {
        q = &question;
        return true;
      }
      for (auto &thread : question.threads)
      {
        if (thread.questionId == qId)
        {
          q = &thread;
          return true;
        }
      }
    }
    return false;
  }

  bool checkUsername(string username)
  {
    for (auto &user : users)
    {
      if (user.username == username)
      {
        return false;
      }
    }
    return true;
  }

  bool checkPassword(string password, User &_user)
  {
    for (auto &user : users)
    {
      if (user.password == password)
      {
        _user = user;
        return false;
      }
    }
    return true;
  }

  int mainMenu()
  {
    const int MIN_OPTION = 1;
    const int MAX_OPTION = 8;
    int choice = -1;

    while (true)
    {
      cout << "\nMenu:\n";
      cout << "1) Print question To Me\n";
      cout << "2) Print question From Me\n";
      cout << "3) Answer Question\n";
      cout << "4) Delete question\n";
      cout << "5) Ask Question\n";
      cout << "6) List System Users\n";
      cout << "7) Feed\n";
      cout << "8) Logout\n";
      cout << "Enter your choice (" << MIN_OPTION << "-" << MAX_OPTION << "): ";
      cin >> choice;

      if (cin.fail() || choice < MIN_OPTION || choice > MAX_OPTION)
      {
        cin.clear();                                         // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid choice. Please try again.\n";
      }
      else
      {
        return choice;
      }
    }
  }

  void askQuestion()
  {
    string txtQuestion;
    int qId;
    bool aq = false;
    int userId;
    while (true)
    {
      cout << "Enter User id or -1 to cancel: ";
      cin >> userId;
      if (userId == -1)
        return;
      if (checkUserId(userId, toUser))
        break;
      else
        cout << "This User ID Is Not Existed\n";
    }
    if (toUser.aq)
    {
      cout << "Do You want This question to be Anonymous(1) or not(0)?: ";
      cin >> aq;
    }
    else
    {
      cout << "Anonymous qusestions are not allowed for this user\n";
    }
    while (true)
    {
      cout << "For thread question: Enter Question id or -1 for new question: ";
      cin >> qId;
      if (qId == -1)
      {
        Question newQuestion;
        cout << "Enter Question text: ";
        getline(cin >> ws, txtQuestion);
        newQuestion.readQuestion(questionId++, txtQuestion, aq, fromUser.userId, toUser.userId);
        questions.push_back(newQuestion);
        return;
      }
      else if (checkQuestionId(qId))
      {
        Question thread;
        cout << "Enter Thread Question for ID " << qId << ": ";
        getline(cin >> ws, txtQuestion);
        thread.readQuestion(threadId++, txtQuestion, aq, fromUser.userId, toUser.userId);
        q->threads.push_back(thread);
        return;
      }
      else
        cout << "This Question Id is Not Existed\n";
    }
  }

  void printQuestionToMe()
  {
    for (auto &question : questions)
    {
      if (question.ToUserId == fromUser.userId)
      {
        question.print();
      }
    }
  }

  void printQuestionFromMe()
  {
    for (auto &question : questions)
    {
      if (question.fromUserId == fromUser.userId)
      {
        question.print();
      }
    }
  }

  void answerQuestion()
  {
    int qId;
    string answer;
    cout << "Enter Question id or -1 to cancel: ";
    while (true)
    {
      cin >> qId;
      if (qId == -1)
        return;
      if (checkQuestionId(qId))
      {
        if (q->answer.empty())
        {
          cout << "Question Id(" << qId << ") from user id(" << q->fromUserId << ")\tQuestion: " << q->question << "\n\n";
          cout << "Enter answer: ";
          getline(cin >> ws, answer);
          q->answer = answer;
        }
        else
        {
          cout << "Question Id(" << qId << ") from user id(" << q->fromUserId << ")\tQuestion: " << q->question << "\n\t" << q->answer << "\n\n";
          cout << "Warning: Already answered. Answer will be updated\n";
          cout << "Enter answer: ";
          getline(cin >> ws, answer);
          q->answer = answer;
        }
        break;
      }
      else
      {
        cout << "This Question Id is Not Existed\n";
      }
    }
  }

  void deleteQuestion()
  {
    int qId;
    cout << "Enter question id or -1 to cancel: ";

    while (true)
    {
      cin >> qId;
      if (qId == -1)
        return;

      for (auto it = questions.begin(); it != questions.end();)
      {
        if (it->questionId == qId)
        {
          it = questions.erase(it); // Reassign the iterator to the returned value
          cout << "Question removed successfully\n";
          return;
        }
        else
        {
          for (auto tIt = it->threads.begin(); tIt != it->threads.end();)
          {
            if (tIt->questionId == qId)
            {
              tIt = it->threads.erase(tIt);
              cout << "Thread Question removed successfully\n";
              return;
            }
            else
            {
              ++tIt;
            }
          }
          ++it;
        }
      }

      cout << "This Question Id is Not Existed\n";
    }
  }

  void listSystemUsers()
  {
    for (auto &user : users)
    {
      cout << "ID: " << user.userId << "\t" << "Name: " << user.name << "\n";
    }
  }

  void feed()
  {
    for (auto &question : questions)
    {
      if (!question.answer.empty())
      {
        cout << "Question Id(" << question.questionId << ")" << "From user id(" << question.fromUserId << ")" << "To user id(" << question.ToUserId << ")\t" << "Question: " << question.question << "\n\tAnswer: " << question.answer << "\n";
      }
      for (auto &thread : question.threads)
      {
        cout << "Thread Parent: " << "Question Id(" << question.questionId << ") " << "Question Id(" << thread.questionId << ") " << "From user id(" << question.fromUserId << ") " << "To user id(" << question.ToUserId << ")\t" << "Question: " << question.question << "\n\tAnswer: " << thread.answer << "\n";
      }
    }
  }
};

int main()
{
  AskMeSystem askMe;
  askMe.run();

  return 0;
}
