#include <iostream>
#include <Windows.h>
#include <conio.h>
#include<vector>
#include<unordered_set>
#include<set>
#include<algorithm>
#include<string>

using namespace std;

vector < vector<char>> sudoku(9, vector<char>(9,'_'));
vector<vector<char>> temp(9, vector<char>(9));
vector<vector<bool>> invalid_points(9, vector<bool>(9, false));
set<pair<short, short>> fixed_points;

vector<vector<char>> sudokus();
void generate_sudoku();
void start_menu();
void play();
void printSudoku();
void printline(short);
void shuffle();
void switching();
void calculate_progress();
void Clear();
void update(short,short);
void show_solution();
bool invalids(string);
void additional();


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
short progress = 0;
bool help_taken = false,play_time;
short y;

int main()
{
    play_time = true;
    while (play_time)
    {
        help_taken = false;
        play_time = false;
        generate_sudoku();
        start_menu();
        while (progress < 81)
        {
            play();
        }
        if (!help_taken)
        {
            COORD cursor = { 30, 26 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
            cout << "Congratulations! You solved the puzzle" << endl;
            cursor = { 30,27 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
            cout << "Do you want to play again? Enter 'Y' for Yes. anything else for No: ";
            string ask; cin >> ask;
            if (ask == "Y") play_time = true;
            cursor = { 30,28 };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
            if (play_time) cout << "You chose to play the game again.     " << endl<<endl;
            else cout << "You chose not to play the game again. Game will exit now." << endl<<endl;
            system("pause");
        }
        fixed_points.clear();
    }
    return 0;
}
vector<vector<char>> sudokus()
{
    vector<vector<char>> store[1];
    store[0] = { { '4','3','5','2','6','9','7','8','1' },{ '6','8','2','5','7','1','4','9','3' },{ '1','9','7','8','3','4','5','6','2' },{ '8','2','6','1','9','5','3','4','7' },{ '3','7','4','6','8','2','9','1','5' },{ '9','5','1','7','4','3','6','2','8' },{ '5','1','9','3','2','6','8','7','4' },{ '2','4','8','9','5','7','1','3','6' },{ '7','6','3','4','1','8','2','5','9' } };
    return store[0];
}
void generate_sudoku()
{
    srand(time(NULL));
    temp = sudokus();
    shuffle(); switching();
    shuffle(); switching();
    shuffle(); switching();
    set<pair<short, short>> choose; 
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++)
        {
            choose.insert(make_pair(i, j));
            sudoku[i][j] = '_';
        }
    }
    short hints = 30;
    while (hints--)
    {
        short hold = rand() % choose.size(), turn = 0;

        for (auto x : choose)
        {
            if (turn == hold)
            {
                short i = x.first, j = x.second;
                sudoku[i][j] = temp[i][j];
                fixed_points.insert(x);
                choose.erase(x);
                break;
            }
            turn++;
        }
    }
    progress = 30;
}
void start_menu()
{
    Clear();
    y = 5;
    COORD cursor = {35, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Welcome to Sudoku Puzzle" << endl;
    y++;
    y++;
    cursor = { 45, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout<< "RULES" << endl;
    y++;
    y++;
    cursor = { 5, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Sudoku is played on a 9x9 grid. Player has to fill vacant grids such that following 3 rules are obeyed: " << endl;
    y++;
    cursor = { 5, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "1. Each digit from 1 - 9 should appear in a row once." << endl;
    y++;
    cursor = { 5, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "2. Each digit from 1 - 9 should appear in a column once." << endl;
    y++;
    cursor = { 5, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "3. On dividing the 9x9 grid into 9 equal parts each part should have all digits from 1 - 9 occur once." << endl;
    y++;
    cursor = { 5, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    system("pause");
    
}
void play()
{
    printSudoku();
    if (progress == 81) return;
    COORD cursor = { 15,26 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    string r, c, value;
    cout << "Enter row number (1-9): ";
    cin >> r;
    while (invalids(r))
    {
        if (r == "-1")
        {
            show_solution();
            return;
        }
        if (r == "-2")
        {
            start_menu();
            return;
        }
        printSudoku();
        cursor = { 15,26 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "Row number can only be between 1-9, Please enter a valid row number: ";
        cin >> r;
    }
    printSudoku();
    cursor = { 15,26 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Row Selected: " << r << endl;
    cursor = { 15,27 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Enter column number (1-9): ";
    cin >> c;
    while (invalids(c))
    {
        if (c == "-1")
        {
            show_solution();
            return;
        }
        if (c == "-2")
        {
            start_menu();
            return;
        }
        printSudoku();
        cursor = { 15,26 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "Row Selected: " << r << endl;
        cursor = { 15,27 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "Column number can only be between 1-9, Please enter a valid row number: ";
        cin >> c;
    }
    if (fixed_points.count(make_pair(stoi(r) - 1, stoi(c) - 1)))
    {
        printSudoku();
        cursor = { 15,26 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "Row Selected: " << r << endl;
        cursor = { 15,27 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "You cannot change values at Fixed points. Please try again.";
        cursor = { 15,28 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        system("pause");
        return;
    }
    printSudoku();
    cursor = { 15,26 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Row Selected: " << r << endl;
    cursor = { 15,27 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Column Selected: " << c << endl;
    cursor = { 15,28 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Please Enter a Valid Value(1-9): ";
    cin >> value;
    while (invalids(value))
    {
        printSudoku();
        cursor = { 15,26 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "Row Selected: " << r << endl;
        cursor = { 15,27 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "Column Selected: " << c << endl;
        cursor = { 15,28 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        cout << "The value you entered is invalid. Please Enter a Valid Value(1-9): ";
        cin >> value;
    }
    char values = value[0], row = r[0], col = c[0];
    sudoku[row - '0' - 1][col - '0' - 1] = values;
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++) invalid_points[i][j] = false;
    }
    update(0, 0);
    update(0, 3);
    update(0, 6);
    update(3, 0);
    update(3, 3);
    update(3, 6);
    update(6, 0);
    update(6, 3);
    update(6, 6);
}
void printline(short x = 9)
{
    SetConsoleTextAttribute(hConsole, x);
    for (short i = 0; i < 13; i++) cout << char(196);
    SetConsoleTextAttribute(hConsole, x + 1);
    for (short i = 0; i < 13; i++) cout << char(196);
    SetConsoleTextAttribute(hConsole, x + 2);
    for (short i = 0; i < 13; i++) cout << char(196);
    cout << endl;
    SetConsoleTextAttribute(hConsole, 7);
    y++;
    COORD cursor = { 30, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}
void printSudoku()
{
    Clear();
    // reset cursor position
    additional();
    y = 0;
    COORD cursor = { 15, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    SetConsoleTextAttribute(hConsole, 7);
    cout << "Enter -1 as Row Number or Column Number to see solution at any moment" << endl;
    y++;
    cursor = { 15, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Enter -2 as Row Number or Column Number to see rules at any moment " << endl;
    y += 2;
    cursor = { 30, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    SetConsoleTextAttribute(hConsole, 7);
    printline();

    for (short i = 1; i <= 9; i++)
    {
        for (short j = 1; j <= 9; j++)
        {
            if (j % 3 == 1)
            {

                if (j == 1)
                {
                    if (i >= 4 and i <= 6) SetConsoleTextAttribute(hConsole, 12);
                    else SetConsoleTextAttribute(hConsole, 9);
                    cout << '|';
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if (j == 4)
                {
                    if (i >= 4 and i <= 6) SetConsoleTextAttribute(hConsole, 13);
                    else SetConsoleTextAttribute(hConsole, 10);
                    cout << '|';
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                {
                    if (i >= 4 and i <= 6) SetConsoleTextAttribute(hConsole, 14);
                    else SetConsoleTextAttribute(hConsole, 11);
                    cout << '|';
                    SetConsoleTextAttribute(hConsole, 7);
                }

            }
            cout << " ";
            if (invalid_points[i - 1][j - 1] and sudoku[i - 1][j - 1] != '_') SetConsoleTextAttribute(hConsole, 12);
            if (fixed_points.count(make_pair(i - 1, j - 1))) SetConsoleTextAttribute(hConsole, 6);
            cout << sudoku[i - 1][j - 1] << " ";
            SetConsoleTextAttribute(hConsole, 7);
            if (j % 3 == 0)
            {
                if (j == 3)
                {
                    if (i <= 3 or i > 6) SetConsoleTextAttribute(hConsole, 9);
                    else SetConsoleTextAttribute(hConsole, 12);
                    cout << '|';
                    SetConsoleTextAttribute(hConsole, 7);
                }
                if (j == 6)
                {
                    if (i <= 3 or i > 6) SetConsoleTextAttribute(hConsole, 10);
                    else SetConsoleTextAttribute(hConsole, 13);
                    cout << '|';
                    SetConsoleTextAttribute(hConsole, 7);
                }
                if (j == 9)
                {
                    if (i <= 3 or i > 6) SetConsoleTextAttribute(hConsole, 11);
                    else SetConsoleTextAttribute(hConsole, 14);
                    cout << '|';
                    SetConsoleTextAttribute(hConsole, 7);
                }

            }
            else cout << char(179);
        }
        cout << endl;
        y++;
        cursor = { 30, y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
        if (i == 3) printline();
        else if (i == 6) printline(12);
        if (i >= 3 and i <= 5) printline(12);
        else printline();
    }
    calculate_progress();
    if (progress <= 81) cout << "PROGRESS: " << progress << "/81" << endl << endl;
    else cout << endl;

}

bool invalids(string a)
{
    vector<string> ans = { "1","2","3","4","5","6","7","8","9" };
    for (auto x : ans)
    {
        if (x == a) return false;
    }
    return true;
}
void shuffle()
{
    short col = rand() % 3, add_col = 1 + rand() % 2, row = rand() % 3, add_row = 1 + rand() % 2;
    for (short i = 0; i < 9; i++)
    {
        swap(temp[i][3 * col], temp[i][(3 * col + 3 * add_col) % 9]);
        swap(temp[i][3 * col + 1], temp[i][(3 * col + 3 * add_col + 1) % 9]);
        swap(temp[i][3 * col + 2], temp[i][(3 * col + 3 * add_col + 2) % 9]);
    }
    for (short i = 0; i < 9; i++)
    {
        swap(temp[3 * row][i], temp[(3 * row + 3 * add_row) % 9][i]);
        swap(temp[3 * row + 1][i], temp[(3 * row + 3 * add_row + 1) % 9][i]);
        swap(temp[3 * row + 2][i], temp[(3 * row + 3 * add_row + 2) % 9][i]);
    }

}
void switching()
{
    
    int x = 1 + rand() % 9, y = 1 + rand() % 9;
    char l = '0' + x,m='0'+y;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (temp[i][j] == l) temp[i][j] = m;
            else if (temp[i][j] == m) temp[i][j] = l;
        }
    }
}
void calculate_progress()
{
    progress = 0;
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++)
        {
            if (invalid_points[i][j] == false and sudoku[i][j] != '_') progress++;
        }
    }
}
void Clear()
{
    system("CLS");
}
void update(short x, short y)
{
    for (short i = x; i < x + 3; i++)
    {
        for (short j = y; j < y+3; j++)
        {
            for (short k = 0; k < 9; k++)
            {
                if (sudoku[i][k] == sudoku[i][j] and j != k)
                {
                    invalid_points[i][k] = true;
                    invalid_points[i][j] = true;
                }
                if (sudoku[k][j] == sudoku[i][j] and i != k)
                {
                    invalid_points[k][j] = true;
                    invalid_points[i][j] = true;
                }
            }
        }
    }
    for (short i = x; i < x + 3; i++)
    {
        for (short j = y; j < y + 3; j++)
        {
            for (short k = x; k < x + 3; k++)
            {
                for (short l = y; l < y + 3; l++)
                {
                    if (k == i and l == j) continue;
                    if (sudoku[i][j] == sudoku[k][l])
                    {
                        invalid_points[i][j] = true;
                        invalid_points[k][l] = true;
                    }
                }
            }
        }
    }
    for (auto z : fixed_points)
    {
        invalid_points[z.first][z.second] = false;
    }
}
void show_solution()
{
    help_taken = true;
    for (short i = 0; i < 9; i++)
    {
        for (short j = 0; j < 9; j++)
        {
            sudoku[i][j] = temp[i][j];
            invalid_points[i][j] = false;
        }
    }
    printSudoku();
    COORD cursor = { 15,26 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "GAME OVER! You were not able to solve the Sudoku Puzzle."<<endl;
    cursor = { 15,27 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    cout << "Do you want to play again? Enter 'Y' for Yes. anything else for No: ";
    string ask; cin >> ask;
    if (ask == "Y") play_time = true;
    cursor = { 15,28 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    if (play_time) cout << "You chose to play the game again.     " << endl;
    else cout << "You chose not to play the game again. Game will exit now." << endl;
    cursor = { 15,29 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    system("pause");
} 
void additional()
{
    COORD cursor = { 75, 10 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    SetConsoleTextAttribute(hConsole, 6);
    cout <<char(219);
    SetConsoleTextAttribute(hConsole, 7);
    cout << " = Fixed_Values, You cannot change them"<< endl;
    cursor = { 75, 12 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
    SetConsoleTextAttribute(hConsole, 12);
    cout << char(219);
    SetConsoleTextAttribute(hConsole, 7);
    cout << " = Invalid Value, Check for clashes" << endl;


}