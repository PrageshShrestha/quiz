
// should return ascii_value for system
#include <random>
#include <string>
#include <sstream> // Include the header for stringstream
#include <fstream>
#include <codecvt>
#include <ctime>
#include <algorithm> // Include algorithm for shuffle
#include <iostream>
#include <windows.h>
#include <thread>
#include <conio.h>
#include <stdlib.h>
#include <numeric>
#include <time.h>
#include <wingdi.h>

using namespace std;

static int questionNumber{1};
class QnA
{
    string question;
    string answer;
    static int point;
    vector<string> options;

public:
    void getData(string *q, string *a, vector<string> o)
    {
        question = *q;
        answer = *a;
        options = o;
    }
    void setColor(int bg, int t)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * bg + t);
    }
    int sendPoint()
    {
        return point;
    }
    void print(int *l)
    {
        char key = 0;
        int option = 0;
        do
        {
            key = 0;
            // timer
            system("CLS");
            // int timeLimit = 10; // Set the time limit in seconds
            // auto startTime = chrono::steady_clock::now();
            // auto endTime = startTime + chrono::seconds(timeLimit);

            // while (chrono::steady_clock::now() < endTime) {
            //     // Calculate remaining time
            //     int remainingTime = chrono::duration_cast<chrono::seconds>(endTime - chrono::steady_clock::now()).count();
            //     cout << "Time remaining: " << remainingTime << " seconds\r" << std::flush;
            // }
            cout << "Level: " << *l + 1 << endl;
            cout << questionNumber << ")";
            cout << question << '\n';
            for (int i = 0; i < 4; i++)
            {
                if (i == option)
                {
                    cout << '>';
                    setColor(0, 3);
                }
                cout << options[i] << endl;
                setColor(0, 7);
            }
            while (key == 0)
            {
                key = _getch();
            }

            switch (key)
            {
            case 72:
                if (option != 0)
                {
                    option--;
                }
                else
                {
                    option = 3;
                }
                break;
            case 80:
                if (option != 3)
                {
                    option++;
                }
                else
                {
                    option = 0;
                }
                break;
            default:
                break;
            }
        } while (key != '\r');
        system("CLS");
        if (answer == options[option])
        {
            point += (*l) + 1;
            if (*l != 4)
            {
                (*l)++;
            }
            cout << "Level: " << *l + 1 << endl;
            cout << questionNumber << ")";
            cout << question << '\n';
            for (int i = 0; i < 4; i++)
            {
                if (answer == options[i])
                {
                    setColor(0, 10);
                }
                cout << options[i] << endl;
                setColor(0, 7);
            }
            while (key == 0)
            {
                key = _getch();
            }
        }
        else
        {
            if (*l != 0)
            {
                (*l)--;
            }

            cout << "Level: " << *l + 1 << endl;
            cout << questionNumber << ")";
            cout << question << '\n';
            for (int i = 0; i < 4; i++)
            {
                if (answer == options[i])
                {
                    setColor(0, 10);
                }
                else if (options[i] == options[option])
                {
                    setColor(0, 12);
                }
                cout << options[i] << endl;
                setColor(0, 7);
            }
            while (key == 0)
            {
                key = _getch();
            }
        }
        cout << "You have " << point << " points\n";
        _getch();
        cout << endl;
        questionNumber++;
    }
};

//[level][questionNumber]
QnA questionBank[5][20];

int menu()
{
    char key = 0;
    int s = 0;
    system("CLS");
    do
    {
        key = 0;
        system("CLS");
        if (s == 0)
            cout << ">" << "MATH114\nPHYS102\nENEV101\nCOMP116\nENGT105\nENGG112\n";
        else if (s == 1)
            cout << "MATH114\n" << u8"\u2794" << "PHYS102\nENEV101\nCOMP116\nENGT105\nENGG112\n";
        else if (s == 2)
            cout << "MATH114\nPHYS102\n"
                 << ">" << "ENEV101\nCOMP116\nENGT105\nENGG112\n";
        else if (s == 3)
            cout << "MATH114\nPHYS102\nENEV101\n"
                 << ">"<< "COMP116\nENGT105\nENGG112\n";
        else if (s == 4)
            cout << "MATH114\nPHYS102\nENEV101\nCOMP116\n"
                 << ">" << "ENGT105\nENGG112\n";
        else if (s == 5)
            cout << "MATH114\nPHYS102\nENEV101\nCOMP116\nENGT105\n"
                 << ">" << "ENGG112\n";
        else
            s = 0;
        while (key == 0)
        {
            key = _getch();
        }
        switch (key)
        {
        case 72:
            if (s != 0)
                s--;
            else
                s = 5;
            break;
        case 80:
            if (s != 5)
                s++;
            else
                s = 0;
            break;
        }
    } while (key != '\r');
    return s;
}
struct user
{
    string playerName;
    int points;
};

void sortLeaderboard(struct user player[500], int sortNumber)
{
    struct user temp;
    for (int i = 0; i < sortNumber - 1; i++)
    {
        for (int j = 1; j < sortNumber; j++)
        {
            if (player[i].points < player[j].points)
            {
                temp = player[i];
                player[i] = player[j];
                player[j] = temp;
            }
        }
    }
}

void displayScore(string currentUser)
{
    int score = questionBank[0][0].sendPoint();
    cout << "Leaderboard";
    ifstream readFile("scores.txt");
    string unparsed;
    string name;
    char point[50];
    int counter = 0;
    int player_index = 0;
    QnA a;
    struct user player[500];
    while (getline(readFile, unparsed))
    {
        for (size_t i = 0; unparsed[i] != ' '; i++)
        {
            point[counter] = unparsed[i];
            counter++;
        }
        point[counter] = '\0';
        int i = 0;
        name = unparsed.substr(++counter);
        player[player_index].playerName = name;
        player[player_index].points = stoi(point);
        player_index++;
        counter = 0;
    }
    player[player_index].playerName = currentUser;
    player[player_index].points = a.sendPoint();

    sortLeaderboard(player, player_index);

    readFile.close();

    ofstream writeFile;

    writeFile.open("scores.txt");

    for (int i = 0; i <= player_index; i++)
    {
        if (i <= 10)
        {
            cout << '\n'
                 << i + 1 << '\t' << player[i].playerName << '\t' << player[i].points << '\n';
        }
        writeFile << player[i].points << ' ' << player[i].playerName << '\n';
    }
}

void loadQuestion(int subjectCode)
{

    // for opening the file in UTF-8
    ifstream questionFile;
    string File = "question" + to_string(subjectCode) + ".txt";
    questionFile.open(File, ios::in);
    string unparsedString;
    int qN;
    vector<string> option;
    int level;
    int subject;
    /*subject_code)qn)level)question|option1|option2|option3|option4|answer\
    question format*/
    char temp[100];
    if (!questionFile.is_open())
    {
        cout << "File not found\n";
    }
    else
    {

        while (getline(questionFile, unparsedString))
        {
            int counter = 0;
            int i = 0;

            while (unparsedString[counter] != ')')
            {
                temp[i] = unparsedString[counter];
                counter++;
                i++;
            }
            temp[i] = '\0';
            counter++;
            i = 0;
            subject = stoi(temp);
            if (subject == subjectCode)
            {
                while (unparsedString[counter] != ')')
                {
                    temp[i] = unparsedString[counter];
                    counter++;
                    i++;
                }
                temp[i] = '\0';
                qN = stoi(temp);
                counter++;
                i = 0;
                while (unparsedString[counter] != ')')
                {
                    temp[i] = unparsedString[counter];
                    counter++;
                    i++;
                }
                temp[i] = '\0';
                level = stoi(temp);
                counter++;
                i = 0;

                char temp[50]{};

                while (unparsedString[counter] != '|')
                {
                    temp[i] = unparsedString[counter];
                    counter++;
                    i++;
                }
                temp[i] = '\0';
                string question = temp;
                counter++;
                i = 0;

                char temp1[4][50];

                for (int j = 0; j < 4; j++)
                {
                    while (unparsedString[counter] != '|')
                    {
                        temp1[j][i] = unparsedString[counter];
                        counter++;
                        i++;
                    }
                    temp1[j][i] = '\0';
                    option.push_back(temp1[j]);
                    counter++;
                    i = 0;
                }

                while (unparsedString[counter] != '\\')
                {
                    temp[i] = unparsedString[counter];
                    counter++;
                    i++;
                }
                temp[i] = '\0';
                string answer{temp};
                counter++;
                i = 0;
                questionBank[level][qN].getData(&question, &answer, option);
                option.clear();
            }
        }
        questionFile.close();
    }
}
int random(int min, int max)
{
    random_device rd;
    uniform_int_distribution<int> dist(min, max);
    return dist(rd);
}
void displayQuestion()
{
    int level = 0;
    int questionNumber;
    vector<int> questionAvailable[5];
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            questionAvailable[i].push_back(j);
        }
    }
    system("CLS");
    for (int i = 0; i < 20; i++)
    {
        do
        {
            questionNumber = random(0, 19);
        } while (!count(questionAvailable[level].begin(), questionAvailable[level].end(), questionNumber));
        vector<int>::iterator new_end;
        new_end = remove(questionAvailable[level].begin(), questionAvailable[level].end(), questionNumber);
        questionAvailable[level].erase(new_end, questionAvailable[level].end());
        questionBank[level][questionNumber].print(&level);
    }
}

string main_menu()
{

    system("CLS");
    static string playerName;
    cout << "Please enter your name.: ";
    cin >> playerName;
    return playerName;
}

int QnA::point = 0;
int main()
{
    int level;
    string player;
    player = main_menu();
    int subjectCode = menu();
    loadQuestion(subjectCode);
    displayQuestion();
    displayScore(player);
}
