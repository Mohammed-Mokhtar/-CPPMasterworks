#include <bits/stdc++.h>
#define io                 \
  ios::sync_with_stdio(0); \
  cin.tie(NULL);           \
  cout.tie(NULL);
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;

vector<string> ReadFileLines(string path)
{
  vector<string> lines;
  fstream file_handler(path.c_str());
  if (file_handler.fail())
  {
    cout << "\n\nError: Can't open the file\n\n";
    return lines;
  }
  string line;
  while (getline(file_handler, line))
  {
    if (line.size() == 0)
      continue;
    lines.push_back(line);
  }
  file_handler.close();
  return lines;
}

void WriteFileLines(string path, vector<string> lines, bool append = true)
{
  auto status = ios::in | ios::out |
                ios::app;

  if (!append)
    status = ios::in | ios::out | ios::trunc;

  fstream file_handler(path.c_str(), status);

  if (file_handler.fail())
  {
    cout << "\n\nError: Can't open the file\n\n";
    return;
  }
  for (auto line : lines)
    file_handler << line << "\n";

  file_handler.close();
}

vector<string> SplitString(string s, string delimiter = ",")
{
  vector<string> strs;

  int pos = 0;
  string substr;
  while ((pos = (int)s.find(delimiter)) != -1)
  {
    substr = s.substr(0, pos);
    strs.push_back(substr);
    s.erase(0, pos + delimiter.length());
  }
  strs.push_back(s);
  return strs;
}

int ToInt(string str)
{
  istringstream iss(str);
  int num;
  iss >> num;

  return num;
}

int ReadInt(int low, int high)
{
  cout << "\nEnter number in range " << low << " - " << high << ": ";
  int value;
  cin >> value;
  if (low <= value && value <= high)
    return value;
  cout << "Error: invalid number...Try again\n";
  return ReadInt(low, high);
}

int ShowReadMenu(vector<string> choices)
{
  cout << "\nMenu:\n";
  for (int ch = 0; ch < (int)choices.size(); ch++)
  {
    cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
  }
  return ReadInt(1, choices.size());
}

struct Question
{
  int question_id;
  int parent_question_id;
  int from_user_id;
  int to_user_id;
  int is_anonymous_questions;
  string question_text;
  string answer_text;

  Question()
  {
    question_id = parent_question_id = from_user_id = to_user_id = -1;
    is_anonymous_questions = 1;
  }

  Question(string line)
  {
    vector<string> substrs = SplitString(line);
    question_id = ToInt(substrs[0]);
    parent_question_id = ToInt(substrs[1]);
    from_user_id = ToInt(substrs[2]);
    to_user_id = ToInt(substrs[3]);
    is_anonymous_questions = ToInt(substrs[4]);
    question_text = substrs[5];
    answer_text = substrs[6];
  }

  void PrintFromQuestion()
  {
    cout << "Question Id (" << question_id << ")";
    if (!is_anonymous_questions)
      cout << "!AQ";
    cout << "to user id(" << to_user_id << ")";
    cout << "\t Question: " << question_text;

    if (answer_text != "")
      cout << "\tAnswer: " << answer_text << "\n";
    else
      cout << "\tNOT Answered\n";
  }

  void PrintToQuestion()
  {
    string prefix = "";
    if (parent_question_id != -1)
      prefix = "\tThread: ";

    cout << prefix << "Question Id(" << question_id << ")";
    if (!is_anonymous_questions)
      cout << " from user id(" << from_user_id << ")";
    cout << "\t question: " << question_text << "\n";

    if (answer_text != "")
      cout << prefix << "\tAnswer: " << answer_text << "\n";
    cout << "\n";
  }

  void PrintFeedQuestion()
  {
    if (parent_question_id = -1)
    {
      cout << "Thread Parent Question ID(" << parent_question_id << ") ";
    }
    cout << "Question Id (" << question_id << ")";
    if (!is_anonymous_questions)
      cout << " from user id(" << from_user_id << ")";

    cout << " To user id(" << to_user_id << ")";

    cout << "\t Question: " << question_text << "\n";
    if (answer_text != "")
      cout << "\tAnswer: " << answer_text << "\n";
  }

  string ToString()
  {
    ostringstream oss;
    oss << question_id << "," << parent_question_id << "," << from_user_id << "," << to_user_id << "," << is_anonymous_questions << "," << question_text << "," << answer_text;
    return oss.str();
  }
};

struct User
{
  int user_id;
  string user_name;
  string password;
  string name;
  string email;
  int allow_anonymous_questions;

  vector<int> questions_id_from_me;
  map<int, vector<int>> questionId_questionIdsThread_to_map;

  User()
  {
    user_id = allow_anonymous_questions = -1;
  }

  User(string line)
  {
    vector<string> substrs = SplitString(line);
    assert(substrs.size() == 6);

    user_id = ToInt(substrs[0]);
    user_name = substrs[1];
    password = substrs[2];
    name = substrs[3];
    email = substrs[4];
    allow_anonymous_questions = ToInt(substrs[5]);
  }

  string toString()
  {
    ostringstream oss;
    oss << user_id << "," << user_name << "," << password << "," << name << "," << email << "," << allow_anonymous_questions;

    return oss.str();
  }
};

struct QuestionsManager
{
  map<int, vector<int>> questionId_questionsIdsThread_to_map;

  map<int, Question> questionId_questionObject_map;
  int last_id;
  QuestionsManager()
  {
    last_id = 0;
  }

  void LoadDatabase()
  {
    last_id = 0;
    questionId_questionObject_map.clear();
    questionId_questionsIdsThread_to_map.clear();

    vector<string> lines = ReadFileLines("questions.txt");
    for (auto &line : lines)
    {
      Question question(line);
      last_id = max(last_id, question.question_id);

      questionId_questionObject_map[question.question_id] = question;

      if (question.parent_question_id == -1)
        questionId_questionsIdsThread_to_map[question.question_id].push_back(question.question_id);
      else
        questionId_questionsIdsThread_to_map[question.parent_question_id].push_back(question.question_id);
    }
  }

  void FillUserQuestions(User &user)
  {
    user.questions_id_from_me.clear();
    user.questionId_questionIdsThread_to_map.clear();

    for (auto &pair : questionId_questionsIdsThread_to_map)
    {
      for (auto &question_id : pair.second)
      {
        Question &question = questionId_questionObject_map[question_id];

        if (question.from_user_id == user.user_id)
          user.questions_id_from_me.push_back(question.question_id);
        if (question.to_user_id == user.user_id)
        {
          if (question.parent_question_id == -1)
            user.questionId_questionIdsThread_to_map[question.question_id].push_back(question.question_id);
          else
            user.questionId_questionIdsThread_to_map[question.parent_question_id].push_back(question.question_id);
        }
      }
    }
  }

  void PrintUserToQuestions(User &user)
  {
    cout << "\n";
    if (user.questionId_questionIdsThread_to_map.size() == 0)
      cout << "No Questions for you";
    for (auto &pair : user.questionId_questionIdsThread_to_map)
    {
      for (auto &question_id : pair.second)
      {
        Question &question = questionId_questionObject_map[question_id];
        question.PrintToQuestion();
      }
    }
  }

  void PrintUserFromQuestions(User &user)
  {
    cout << "\n";
    for (auto &question_id : user.questions_id_from_me)
    {
      Question &question = questionId_questionObject_map[question_id];
      question.PrintFromQuestion();
    }
    cout << "\n";
  }

  void AskQuestion(User &user, pair<int, int> to_user_pair)
  {
    Question question;
    if (!to_user_pair.second)
    {
      cout << "Note: Anonymous questions are not allowed for this user\n";
      question.is_anonymous_questions = 0;
    }
    else
    {
      cout << "Is anonymous questions?: (0 or 1): ";
      cin >> question.is_anonymous_questions;
    }
    question.parent_question_id = ReadQuestionIdThread(user);
    cout << "Enter question text: ";
    getline(cin, question.question_text);
    // getline(cin, question.question_text);

    question.from_user_id = user.user_id;
    question.to_user_id = to_user_pair.first;

    question.question_id = ++last_id;

    questionId_questionObject_map[question.question_id] = question;

    if (question.parent_question_id == -1)
      questionId_questionsIdsThread_to_map[question.question_id].push_back(question.question_id);
    else
      questionId_questionsIdsThread_to_map[question.parent_question_id].push_back(question.question_id);
  }

  void AnswerQuestion(User &user)
  {
    int question_id = ReadQuestionIdAny(user);

    if (question_id == -1)
      return;

    Question &question = questionId_questionObject_map[question_id];

    question.PrintToQuestion();

    if (question.answer_text != "")
      cout << "\nWarning: Already answered. Answer will be updated\n";

    cout << "Enter answer: ";
    getline(cin, question.answer_text);
    getline(cin, question.answer_text);
  }

  void DeleteQuestion(User &user)
  {
    int question_id = ReadQuestionIdAny(user);
    if (question_id == -1)
      return;

    vector<int> ids_to_remove;

    if (questionId_questionsIdsThread_to_map.count(question_id))
    {
      ids_to_remove = questionId_questionsIdsThread_to_map[question_id];

      questionId_questionsIdsThread_to_map.erase(question_id);
    }
    else
    {
      ids_to_remove.push_back(question_id);

      for (auto &pair : questionId_questionsIdsThread_to_map)
      {
        vector<int> &vec = pair.second;
        for (int pos = 0; pos < (int)vec.size(); pos++)
        {
          if (question_id == vec[pos])
          {
            vec.erase(vec.begin() + pos);
            break;
          }
        }
      }
    }
    for (auto id : ids_to_remove)
    {
      questionId_questionObject_map.erase(id);
    }
  }

  void ListFeed()
  {
    for (auto &pair : questionId_questionObject_map)
    {

      Question &question = pair.second;
      if (question.answer_text == "")
        continue;
      question.PrintFeedQuestion();
    }
  }

  int ReadQuestionIdAny(User &user)
  {
    int question_id;
    cout << "Enter Question id or -1 to cancel: ";
    cin >> question_id;

    if (question_id == -1)
      return -1;
    if (!questionId_questionObject_map.count(question_id))
    {
      cout << "\nError: No question with such ID. Try again\n\n";
      return ReadQuestionIdAny(user);
    }
    Question &question = questionId_questionObject_map[question_id];

    if (question.to_user_id != user.user_id)
    {
      cout << "\nError: Invalid question ID. Try again\n\n";
      return ReadQuestionIdAny(user);
    }
    return question_id;
  }

  int ReadQuestionIdThread(User &user)
  {
    int question_id;
    cout << "For thread question: Enter Question id or -1 for new question: ";
    cin >> question_id;
    if (question_id == -1)
      return -1;
    if (!questionId_questionObject_map.count(question_id))
    {
      cout << "No thread question with such ID. Try again\n";
      return ReadQuestionIdThread(user);
    }
    return question_id;
  }

  void UpdateDatabase()
  {
    vector<string> lines;
    for (auto &pair : questionId_questionObject_map)
      lines.push_back(pair.second.ToString());

    WriteFileLines("questions.txt", lines, false);
  }
};

struct UsersManager
{
  map<string, User> username_userObject_map;
  User current_user;
  int last_id;
  UsersManager()
  {
    last_id = 0;
  }

  void LoadDatabse()
  {
    last_id = 0;
    username_userObject_map.clear();

    vector<string> lines = ReadFileLines("users.txt");
    for (auto &line : lines)
    {
      User user(line);
      username_userObject_map[user.user_name] = user;
      last_id = max(last_id, user.user_id);
    }
  }

  void AccessSystem()
  {
    int choice = ShowReadMenu({"Login", "Sign Up"});
    if (choice == 1)
      DoLogin();
    else
      DoSignUp();
  }

  void DoLogin()
  {
    LoadDatabse();

    while (true)
    {
      cout << "Enter user name & password: ";
      cin >> current_user.user_name >> current_user.password;

      if (!username_userObject_map.count(current_user.user_name))
      {
        cout << "\nInvalid user name or passowrd. Try again\n\n";
        continue;
      }
      User user_exist = username_userObject_map[current_user.user_name];

      if (current_user.password != user_exist.password)
      {
        cout << "\nInvlaid user name or password. Try again\n\n";
        continue;
      }
      current_user = user_exist;
      break;
    }
  }

  void DoSignUp()
  {
    while (true)
    {
      cout << "Enter user name. (No spaces): ";
      cin >> current_user.user_name;
      if (username_userObject_map.count(current_user.user_name))
        cout << "This user name Already Used. Try another one\n";
      else
        break;
    }
    cout << "Enter password: ";
    cin >> current_user.password;

    cout << "Enter Your name: ";
    cin >> current_user.name;

    while (true)
    {
      cout << "Enter email: ";
      cin >> current_user.email;

      bool email_in_use = false;
      for (const auto &pair : username_userObject_map)
      {
        if (pair.second.email == current_user.email)
        {
          email_in_use = true;
          break;
        }
      }

      if (email_in_use)
        cout << "This email is already used. Try another one\n";
      else
        break;
    }
    cout << "Allow anonymous questions? (0 or 1): ";
    cin >> current_user.allow_anonymous_questions;

    current_user.user_id = ++last_id;
    username_userObject_map[current_user.user_name] = current_user;

    UpdateDatabse(current_user);
  }

  void ListUsersNamesIds()
  {
    for (auto &pair : username_userObject_map)
      cout << "ID: " << pair.second.user_id << "\t\tName: " << pair.second.name << "\n";
  }

  pair<int, int> ReadUserId()
  {
    int user_id;
    cout << "Enter user id or -1 to cancel: ";
    cin >> user_id;
    if (user_id == -1)
      return make_pair(-1, -1);

    for (auto &pair : username_userObject_map)
    {
      if (pair.second.user_id == user_id)
        return make_pair(user_id, pair.second.allow_anonymous_questions);
    }
    cout << "Invalid User ID. Try again\n";
    return ReadUserId();
  }

  void UpdateDatabse(User &user)
  {
    string line = user.toString();
    vector<string> lines(1, line);
    WriteFileLines("users.txt", lines);
  }
};

struct AskMeSystem
{
  UsersManager users_manager;
  QuestionsManager questions_manager;

  void LoadDatabse(bool fill_user_questions = false)
  {
    users_manager.LoadDatabse();
    questions_manager.LoadDatabase();

    if (fill_user_questions)
    {
      questions_manager.FillUserQuestions(users_manager.current_user);
    }
  }

  void run()
  {
    LoadDatabse();
    users_manager.AccessSystem();
    questions_manager.FillUserQuestions(users_manager.current_user);

    vector<string> menu;
    menu.push_back("Print questinos To Me");
    menu.push_back("Print Quesiton From Me");
    menu.push_back("Answer Question");
    menu.push_back("Delete Question");
    menu.push_back("Ask Question");
    menu.push_back("List System Users");
    menu.push_back("Feed");
    menu.push_back("Logout");

    while (true)
    {
      int choice = ShowReadMenu(menu);
      if (choice == 1)
      {
        questions_manager.PrintUserToQuestions(users_manager.current_user);
      }
      else if (choice == 2)
      {
        questions_manager.PrintUserFromQuestions(users_manager.current_user);
      }
      else if (choice == 3)
      {
        questions_manager.AnswerQuestion(users_manager.current_user);
        questions_manager.UpdateDatabase();
      }
      else if (choice == 4)
      {
        questions_manager.DeleteQuestion(users_manager.current_user);
        questions_manager.FillUserQuestions(users_manager.current_user);
        questions_manager.UpdateDatabase();
      }
      else if (choice == 5)
      {
        pair<int, int> to_user_pair = users_manager.ReadUserId();
        questions_manager.AskQuestion(users_manager.current_user, to_user_pair);
        questions_manager.UpdateDatabase();
      }
      else if (choice == 6)
      {
        users_manager.ListUsersNamesIds();
      }
      else if (choice == 7)
      {
        questions_manager.ListFeed();
      }
      else
        break;
    }
    run();
  }
};

int main()
{
  AskMeSystem service;
  service.run();

  return 0;
}
