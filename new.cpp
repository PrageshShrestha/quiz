#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class QnA {
    int qnr;
    int mt; // menu type
    string question_main;
    string answer;
    int level;

public:
    void add_input(int qn, string question, string answer_given, int level_given, int mt_given) {
        qnr = qn;
        mt = mt_given;
        question_main = question;
        answer = answer_given;
        level = level_given;
        cout << qn << " Saved" << endl;
    }
};

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

        try {
            int answerInt = istringstream(array_que[0]);
            int hello = istringstream(array_que[3]);
            real_question_array[i].add_input(i + 1, array_que[1], array_que[2],hello , answerInt);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument: " << e.what() << endl;
            // Handle the invalid argument as needed, e.g., provide a default value.
        }
    }

    cout << "The total questions are: " << total_count << endl;
}

int main() {
    store_position();
    return 0;
}
