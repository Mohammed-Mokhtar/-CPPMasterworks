#include <bits/stdc++.h>
#define io                                                                     \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define ll long long
#define INF 0x3f3f3f3f
using namespace std;
const double MX = 1e5 + 5;
const double eps = 1e-9;
const double pi = 3.141592653589793238;

int main() {
  int grid[100][100] = {0};
  int n;
  cout << "Enter Grid Dimension: ";
  cin >> n;
  int turn = 0;
  int steps = 0;
  while (true) {
    if (steps == n * n) {
      cout << "Tie\n";
      break;
    }
    char symbol = 'x';
    if (turn == 1) {
      symbol = 'o';
    }
    cout << "Player " << symbol << " turn. Enter empty location As [r,c]: ";
    int r, c;
    cin >> r >> c;
    r--, c--;
    if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 0) {
      cout << "Invalid input. Try again\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    grid[r][c] = turn + 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        char ch = '.';
        if (grid[i][j] == 1)
          ch = 'x';
        else if (grid[i][j] == 2)
          ch = 'o';
        cout << ch;
      }
      cout << "\n";
    }
    bool win = false;
    for (int i = 0; i < n; i++) {
      bool rowWin = true, colWin = true;
      for (int j = 0; j < n; j++) {
        if (grid[i][j] != turn + 1) {
          rowWin = false;
        }
        if (grid[j][i] != turn + 1)
          colWin = false;
      }
      if (rowWin || colWin) {
        win = true;
        cout << "Player " << symbol << " Wins!\n";
        break;
      }
    }
    if (win)
      break;
    bool diag1Win = true, diag2Win = true;
    for (int i = 0; i < n; i++) {
      if (grid[i][i] != turn + 1)
        diag1Win = false;
      if (grid[i][n - i - 1] != turn + 1)
        diag2Win = false;
    }
    if (diag1Win || diag2Win) {
      cout << "Player " << symbol << " Wins!\n";
      break;
    }

    turn = !turn;
    steps++;
  }
  return 0;
}
