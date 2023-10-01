#include <iostream>
#include <random>
#include <string>
#include <fstream>

#include <thread>
#include <chrono>
#include <vector>
#include <algorithm> // Include algorithm for std::shuffle
using namespace std;

int points = 0;

class QnA {
    int qnr;
    int mt; // menu type
    string question_main;
    string answer;
    int level;

public:
    void add_input(int qn, string question, string answer_given, int level_given , int mt_given) {
        qnr = qn;
        mt = mt_given;
        question_main = question;
        answer = answer_given;
        level = level_given;
        cout << qn << " Saved" << endl;
    }

    char return_mt() {
        return mt;
    }
    char return_answer() {
        return answer;
    }
    string return_question() {
        return question_main;
    }
    int return_qnr() {
        return qnr;
    }
};

QnA questions[15];


vector<char> answer_options_array(int qn) {
    vector<char> answer_options_u(4);
    answer_options_u[0] = real_question[qn].return_answer();

    for (int i = 1; i < 4; i++) {
        answer_options_u[i] = real_question[qn - 1].return_answer();
    }

    return answer_options_u;
}

void display_menu() {
    char choice_str;
    string options[7] = {"General", "Sports", "Programming", "STEM", "Geography and Food", "History", "Arts"};
    cout << "Enter the corresponding Number or select one of them to play:" << endl;
    cout << "OPTION:";
    cin >> choice_str;
}

void design() {
    cout << "QUIZ HUNT" << endl;

    // Print dots animation
    for (int i = 0; i < 10; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    cout << endl;
}

char display_question(int qn) {
    char answer;
    cout << real_question[qn].return_question();
    cout << endl;
    cin >> answer;
    return answer;
}

int add_point(char mt, int level, int points) {
    int pointsToAdd = 0; // Initialize the variable

    // Adjust the pointsToAdd based on the question number ranges
    if (level == 1) {
        pointsToAdd = 1;
    } else if (level == 2) {
        pointsToAdd = 2;
    } else if (level == 3) {
        pointsToAdd = 3;
    } else if (level == 4) {
        pointsToAdd = 4;
    } else if (level == 5) {
        pointsToAdd = 5;
    }

    points = points + pointsToAdd;
    return points; // Return the updated points
}

// Shuffle vector
void shuffle_vector(vector<char>& vec) {
    // To obtain a time-based seed
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Shuffling our vector
    shuffle(vec.begin(), vec.end(), default_random_engine(seed));
}

int check_answer(int qn, char answer, int level) {
    char real_answer = real_question[qn].return_answer();

    if (real_answer == answer) {
        int st_var = real_question[qn].return_mt();
        points = add_point(st_var, level, points); // Update points using the add_point function
        cout << "Correct  ";
        if (level < 5) {
            return level++;
        } else {
            return level;
        }
    } else {
        if (qn % 2 == 0) {
            cout << "Sorry. The answer is: " << real_answer;
            if (level > 1) {
                return level--;
            } else {
                return level;
            }
        } else {
            cout << "Nah. The answer is: " << real_answer;
            if (level > 1) {
                return level - 1;
            } else {
                return level;
            }
        }
    }
}

void store_position() {
    string inputString = "2 | whwat is your name ?| pragesh | 3 | 4 | mis | hello | 5 |3| what is my name| pragesh | 4|";
    char targetChar = '|';

    vector<int> positions; // Vector to store positions of the target character

    for (size_t i = 0; i < inputString.length(); i++) {
        if (inputString[i] == targetChar) {
            positions.push_back(i);
        }
    }
    int count = positions.size();

    int total_count = count / 4;
    int total_array[total_count][4];
    vector<QnA> real_question_array(total_count);
    for (int i = 0; i < total_count; i++) {

        for (int j = 0; j < 4; j++) {
            int num = (i * 4) + j;
            total_array[i][j] = positions[num];
        }
    }

    for (int i = 0; i < total_count; i++) {
        string array_que[4];
        for (int j = 0; j < 4; j++) {
            int startPosition, endPosition;
            if (total_array[i][j] == 2) {
                startPosition = 0; // Starting position
                endPosition = 1;   // Ending position (excluding position 305)
            }
            else if (total_array[i][j] == 3) {

                startPosition = 0; // Starting position
                endPosition = 3;

            }
            else if (j == 0 && i != 0) {

                startPosition = total_array[i - 1][3]; // Starting position
                endPosition = total_array[i][j];
            }
            else {
                startPosition = total_array[i][j - 1]; // Starting position
                endPosition = total_array[i][j];
            }

            char buffer[endPosition - startPosition + 1];
            for (int k = 0; k < endPosition - startPosition + 1; k++) {
                buffer[k] = inputString[startPosition + k]; // Access and copy each character
            }
            buffer[endPosition - startPosition + 1] = '\0'; // Null-terminate the buffer

            string extractedString(buffer); // Convert the buffer to a string
            array_que[j] = extractedString;
        }

        real_question_array[i].add_input(i + 1, array_que[1], array_que[2], stoi(array_que[3]), stoi(array_que[0]));
    }

    cout << "The total questions are: " << total_count << endl;
}







int main() {
    design();
    int level = 1;
    char answer;
    int qn;
    string questions;
    vector<char> answer_options;

    for (int qn = 1; qn <= 20; qn++) {
        cout << "Score: " << points << endl;
        cout << display_question(qn) << endl;
        answer_options = answer_options_array(qn);

        shuffle_vector(answer_options);
        for (int i = 0; i < 4; i++) {
            cout << i << ". " << answer_options[i] << endl;
        }
        cout << "Ans: ";
        cin >> answer;
        level = check_answer(qn, answer, level);
    }

    float accuracy = (static_cast<float>(points) / 40) * 100; // Convert points to float for accurate division
    cout << "Your Total Score is: " << points << endl;
    cout << "Accuracy: " << accuracy << "%" << endl;

    return 0;
}
