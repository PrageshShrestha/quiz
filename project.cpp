#include <iostream>
#include <random>
#include <string>
#include <sstream> // Include the header for stringstream
#include <ctime>
#include <algorithm> // Include algorithm for shuffle
using namespace std;

int points = 0;

int Randnum(int min, int max) {
    unsigned int seed = static_cast<unsigned int>(time(0));

    // Use the system time to generate a pseudo-random number
    seed = (214013 * seed + 2531011);
    return (seed % 4) + 1; // Returns a number between 1 and 4
}

class QnA {
 static int total_objects;
    int qnr; // question number
    int mt; // menu type
    string question_main; // The question
    string answer; // Answer to the question
    int level; // The level of the question
    string subject; // The chosen subject
    string options[4];

public:
 QnA() {
  qnr = total_objects + 1;
        total_objects++; // Increment the total_objects count when a new object is created
    }
    void add_input(int mt_given,string question, int level_given, string option1) {
       
        mt = mt_given;
        question_main = question;
        level = level_given;

        // Extract the options from the option1 string
        stringstream ss(option1); // Create a stringstream object with option1
        string option;
        int i = 0;
        while (getline(ss, option, ',')) {
            options[i] = option; // Assign each option to the corresponding index in the options array
            i++;
            if (i >= 4) { // Break if the options array is full
                break;
            }
        }
        answer = options[0];

        switch (mt_given) {
            case 1:
                subject = "math";
                break;
            case 2:
                subject = "physics";
                break;
            case 3:
                subject = "environment";
                break;
            case 4:
                subject = "computer";
                break;
            case 5:
                subject = "english";
                break;
            case 6:
                subject = "engineering";
                break;
        }
    }

    int return_mt() {
        return mt;
    }

    int return_options() {
        int num = Randnum(1, 4);
        string temp = options[0];
        options[0] = options[num - 1];
        options[num - 1] = temp;
        for (int i = 0; i < 4; i++) {
            cout << "  " << i + 1 << ". " << options[i] << endl;
        }

        return num;
    }

    string return_answer() {
        return answer;
    }

    string return_question() {
        return question_main;
    }

    int return_qnr() {
        return qnr;
    }

    int return_level() {
        return level;
    }
	 static int get_total_objects() { // Static member function to access the total count
        return total_objects;
    }
};
int QnA::total_objects = 0;
int display_question(QnA question) {
    int answer;
    cout << question.return_question() << endl;
    answer = question.return_options();

    return answer;
}

int add_point(int level, int points) {
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

int question_finder(int level, vector<vector<vector<int>>> Question_bank, vector<int> already_shown_qn, int mt) {
previous:
    int qn2, num1, num2, num3;
    num2 = level-1;
    num3 = Randnum(0, 19);
    if (mt == 0) {
        num1 = Randnum(0, 3);
    } else {
        num1 = mt - 1;
    }
    qn2 = Question_bank[num1][num2][num3];
	
    int size = already_shown_qn.size();
	
    for (int i = 1; i < size; i++) {
        if (qn2 == already_shown_qn[i - 1]) {
			
            goto previous;
			break;
        }
    }
	
    return qn2;
}

int check_answer(int ans, int qn, int answer, int level, QnA question) {
    int real_answer = ans;
    string real_ans = question.return_answer();
    if (real_answer == answer) {
        int st_var = question.return_mt();
        points = add_point(level, points); // Update points using the add_point function
        cout << "  Awesome! That's correct!";
        if (level < 5) {
            return level+1;
        } else {
            return level;
        }
    } else {
        if (qn % 2 == 0) {
            cout << "Oops. The answer is: " << ans << "." << real_ans;
            if (level > 1) {
                return level-1;
            } else {
                return level;
            }
        } else {
            cout << "Nah. The answer is: " << ans << "." << real_ans;
            if (level > 1) {
                return level - 1;
            } else {
                return level;
            }
        }
    }
}

string rcs(const string str, char character) {
    string result;
    for (char c : str) {
        if (c != character) {
            result += c;
        }
    }
    return result;
}

int stringToInteger(string &str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle leading whitespace
    while (i < str.length() && (str[i] == ' ' || str[i] == '\t')) {
        i++;
    }

    // Handle sign
    if (i < str.length() && str[i] == '-') {
        sign = -1;
        i++;
    } else if (i < str.length() && str[i] == '+') {
        i++;
    }

    // Convert characters to an integer
    while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

vector<QnA> store_position() {
string inputString = "1| question2 | answer2 | 1 | option1 , option2 , option3 , option4| 1| question3 | answer3 | 1 | option1 , option2 , option3 , option4|1| question4 | answer4 | 1| option1 , option2 , option3 , option4|";
// Add 20 formats for level 1

inputString += "1| question21 | answer21 | 1 | option1 , option2 , option3 , option4| 2| question22 | answer22 | 1 | option1 , option2 , option3 , option4|2| question23 | answer23 | 1| option1 , option2 , option3 , option4|";
// Add 20 formats for level 2

inputString += "3| question41 | answer41 | 1 | option1 , option2 , option3 , option4| 3| question42 | answer42 | 1 | option1 , option2 , option3 , option4|3| question43 | answer43 | 1| option1 , option2 , option3 , option4|";
// Add 20 formats for level 3

inputString += "4| question61 | answer61 | 1 | option1 , option2 , option3 , option4| 4| question62 | answer62 | 1 | option1 , option2 , option3 , option4|4| question63 | answer63 | 1| option1 , option2 , option3 , option4|";
// Add 20 formats for level 4

inputString += "5| question81 | answer81 | 1 | option1 , option2 , option3 , option4| 5| question82 | answer82 | 1 | option1 , option2 , option3 , option4|5| question83 | answer83 | 1| option1 , option2 , option3 , option4|";
// Add 20 formats for level 5

 char targetstring = '|';
    vector<int> positions; // Vector to store positions of the target character

    for (size_t i = 0; i < inputString.length(); i++) {
        if (inputString[i] == targetstring) {
            positions.push_back(i);
        }
    }

    int total_count = positions.size() / 5;
    int total_array[total_count][5];
    vector<QnA> QnA_array(total_count);

    for (int i = 0; i < total_count; i++) {
        for (int j = 0; j < 5; j++) {
            int num = (i * 5) + j;
            total_array[i][j] = positions[num];
        }
    }

    for (int i = 0; i < total_count; i++) {
        string array_que[4];
        for (int j = 0; j < 5; j++) {
            int startPosition, endPosition; 
            if (total_array[i][j] == 2) {
                startPosition = 0; // Starting position
                endPosition = 1;
            } else if (total_array[i][j] == 3) {
                startPosition = 0; // Starting position
                endPosition = 3;
            } else if (j == 0 && i != 0) {
                startPosition = total_array[i - 1][4]; // Starting position
                endPosition = total_array[i][j];
            } else {
                startPosition = total_array[i][j - 1]; // Starting position
                endPosition = total_array[i][j];
            }

            string extractedString = inputString.substr(startPosition, endPosition - startPosition + 1);
            array_que[j] = rcs(extractedString, '|');
        }

        try {
            int answerInt = stringToInteger(array_que[0]);
            int hello = stringToInteger(array_que[3]);

            QnA_array[i].add_input(answerInt, array_que[1], hello, array_que[4]);
            // 0 as a placeholder for mt level
        } catch (invalid_argument &e) {
            cerr << "Invalid argument: " << e.what() << endl;
            // Handle the invalid argument as needed, e.g., provide a default value.
        }
    }

    return QnA_array;
}

vector<vector<vector<int>>> classifier_function(int count, vector<QnA> question2) {
    // Assuming QnA has methods return_level(), return_mt(), and return_qn()
    vector<vector<vector<int>>> Question_bank(7, vector<vector<int>>(5, vector<int>(20)));
    vector<vector<int>> total_counts(7, vector<int>(5));

    for (int i = 0; i < count; i++) {
        int level = question2[i].return_level();
        int mt = question2[i].return_mt();
        int qn = question2[i].return_qnr();

        // Make sure indices are within bounds
        if (mt >= 1 && mt <= 7 && level >= 1 && level <= 5) {
			for(int j=0;j<7;j++){
				for(int k = 0;k<5;k++){
				if(j == mt-1 && k==level-1){
					int l = total_counts[j][k];
            Question_bank[mt - 1][level - 1][l] = qn;
			          total_counts[j][k] = total_counts[j][k] +1;
				}
				}
			}
        }
    }

    // Return the Question_bank here
    return Question_bank;
}

int display_menu() {
    string choice_str;
    string options[6] = {"MATHS", "PHYSICS", "ENVIRONMENT", "COMPUTER", "ENGLISH", "ENGINEERING"};
    int choice = 0;

    while (choice < 1 || choice > 6) {
        cout << "Select the subject you want to play:" << endl;
        for (int i = 1; i <= 6; i++) {
            cout << i << ". " << options[i - 1] << endl;
        }
        cout << "OPTION: ";
        cin >> choice_str;

        // Convert the user input to an integer
        choice = stringToInteger(choice_str);

        // Check if the input is a valid option
        if (choice < 1 || choice > 6) {
            cout << "Invalid choice! Please select a valid option." << endl;
        }
    }

    return choice;
}
void printQuestionBank(const vector<vector<vector<int>>>& Question_bank) {
    for (size_t i = 0; i < Question_bank.size(); i++) {
        for (size_t j = 0; j < Question_bank[i].size(); j++) {
            for (size_t k = 0; k < Question_bank[i][j].size(); k++) {
                cout << "Question_bank[" << i << "][" << j << "][" << k << "]: " << Question_bank[i][j][k] << endl;
            }
        }
    }
}
void backend(){
		
	 /*
	 for (int qn = 1; qn <= 20; qn++) {
        // Your existing code...
        cout << "Question Bank:" << endl;
        printQuestionBank(Question_bank);
    }

		for (auto &q : question2) {
    cout << "Question Number: " << q.return_qnr() << endl;
    cout << "Menu Type: " << q.return_mt() << endl;
    cout << "Main Question: " << q.return_question() << endl;
    cout << "Level: " << q.return_level() << endl;
		}
  
}*/
	
	
}

int main() {
    
    vector<vector<vector<int>>> Question_bank(7, vector<vector<int>>(5, vector<int>(20)));//menutype , diffculty , question
    vector<QnA> question2 = store_position();
    
    int qn;
    
    vector<int> already_shown_qn; // for not repeating already shown questions
    int count= QnA::get_total_objects();
    cout << "Total number of questions created: " << count << endl;
	Question_bank = classifier_function(count, question2);
    int choice = display_menu();
	int level=1;
     


  cout << endl<< "ACTUAL GAME STARTS. शु स्वागतम् ." <<endl;
    for (int qn = 1; qn <= 20; qn++) {
		
    string answer;
        cout << endl<< "Your Score: " << points << endl;
        int qn1 = question_finder(level, Question_bank, already_shown_qn , choice);
		
        QnA question = question2[qn1]; // Accessing a specific question
        cout << qn << ". ";
        int actual_answer = display_question(question);

        cout << endl<< "  Ans: ";
		
        cin >> answer;
		cout << '\a'<<endl;
        level = check_answer(actual_answer, qn1, stringToInteger(answer), level, question);
    }

    float accuracy = (static_cast<float>(points) / 40) * 100; // Convert points to float for accurate division
    cout << endl
         << "Your Total Score is: " << points << endl;
    cout << "Your Accuracy: " << accuracy << "%" << endl;

    return 0;
}
 
