#include <iostream>
#include <random>
#include <string>
#include <fstream>

#include <thread>
#include <chrono>
#include <vector>
#include <algorithm> // Include algorithm for shuffle
using namespace std;

int points = 0;

class QnA {
    int qnr;
    int mt; // menu type
    string question_main;
    string answer;
    int level;
    string subject;

public:

  QnA() {
        int count++; // Increment the count when an object is created
    }

    ~QnA() {
        int count--; // Decrement the count when an object is destroyed
    }

    int getCount() {
        return count; 
    }
    void add_input(int qn, string question, string answer_given, int level_given , int mt_given) {
        qnr = qn;
		
        mt = mt_given;
        question_main = question;
        answer = answer_given;
        level = level_given;
         
        switch (mt_given){
            case 1:
                subject = "math";
                break;
            case 2:
                subject = "physics";
                break;
            case 3:
                subject = "enviroment";
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
       
    
        cout << qn << " Saved" << endl;
    }
    
    int return_mt() {
        return mt;
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
   int return_level(){
return level;
}
};




vector<string> answer_options_array( QnA question) {
    vector<string> answer_options_u(4);
    answer_options_u[0] = question.return_answer();

    for (int i = 1; i < 4; i++) {
        answer_options_u[i] = question.return_answer();
    }

    return answer_options_u;
}


void display_menu() {
    string choice_str;
    string options[7] = {"MATHS", "PHYSICS", "ENVIRONMENT", "COMPUTER",  "ENGLISH", "ENGINEERING"};
    cout << "Enter the corresponding Number or select one of them to play:" << endl;
    cout << "OPTION:";
    cin >> choice_str;
}
int Randnum(int min, int max) {
constexpr unsigned int LCG_A = 1664525;
constexpr unsigned int LCG_C = 1013904223;
constexpr unsigned int LCG_M = 65536; // 2^32


unsigned int lcg_seed = 12345;



    lcg_seed = (LCG_A * lcg_seed + LCG_C) % LCG_M;
    return min + (lcg_seed % (max - min + 1));
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

string display_question(int qn , QnA question) {
    string answer;
    cout << question.return_question();
    cout << endl;
   
    return answer;
}

int add_point( int level, int points) {
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
void shuffle_vector(vector<string>& vec) {
    // To obtain a time-based seed
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Shuffling our vector
    shuffle(vec.begin(), vec.end(), default_random_engine(seed));
}




int question_finder(int level ,int Question_bank[7][5][20], vector<int>& already_shown_qn,int mt = 0){
previous:
int qn2 , num1 , num2,num3;
num2 = level;
 num3 = Randnum(0,19);
if(mt == 0){
 num1 = Randnum(0,4);
}
else{
num1 = mt-1;
}
qn2 = Question_bank[num1][num2][num3];
int size = already_shown_qn.size();
for(int i=1;i<size;i++){
if(qn2 == already_shown_qn[i-1]){
goto previous;
}
}
return qn2;
}

int check_answer(int qn, string answer, int level , QnA question) {
    string real_answer = question.return_answer();

    if (real_answer == answer) {
        int st_var = question.return_mt();
        points = add_point(level, points); // Update points using the add_point function
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


#include<vector>

int classifier_function(int count, vector<QnA> question2) {
    // Assuming QnA has methods return_level(), return_mt(), and return_qn()
    vector<vector<vector<int>>> Question_bank(7, vector<vector<int>>(5, vector<int>(20)));

    for (int i = 0; i < count; i++) {
        int level = question2[i].return_level();
        int mt = question2[i].return_mt();
        int qn = question2[i].return_qnr();

        // Make sure indices are within bounds
        if (mt >= 1 && mt <= 7 && level >= 1 && level <= 5 && qn >= 1 && qn <= 20) {
            Question_bank[mt - 1][level - 1][qn - 1] = qn;
        }
    }

    // You may want to return the Question_bank here, depending on your requirements
    return 0; // Modify this return value as needed
}


int stringToInteger(const string& str) {
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
    }
    else if (i < str.length() && str[i] == '+') {
        i++;
    }

    // Convert stringacters to integer
    while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result * sign;
}

std::vector<QnA> store_position() {
    std::string inputString = "2 | whwat is your name ?| pragesh | 3 | 4 | mis | hello | 5 |3| what is my name| pragesh | 4|";
    char targetstring = '|';

    std::vector<int> positions; // Vector to store positions of the target character

    for (size_t i = 0; i < inputString.length(); i++) {
        if (inputString[i] == targetstring) {
            positions.push_back(i);
        }
    }

    int total_count = positions.size() / 4;
    int total_array[total_count][4];
    std::vector<QnA> QnA_array(total_count);

    for (int i = 0; i < total_count; i++) {
        for (int j = 0; j < 4; j++) {
            int num = (i * 4) + j;
            total_array[i][j] = positions[num];
        }
    }

    for (int i = 0; i < total_count; i++) {
        std::string array_que[4];
        for (int j = 0; j < 4; j++) {
            int startPosition, endPosition;
            if (total_array[i][j] == 2) {
                startPosition = 0; // Starting position
                endPosition = 1;
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

            std::string extractedString = inputString.substr(startPosition, endPosition - startPosition + 1);
            array_que[j] = extractedString;
        }

        try {
            int answerInt = stringToInteger(array_que[0]);
            int hello = stringToInteger(array_que[3]);
            QnA_array[i] = QnA(answerInt, array_que[1], array_que[2], hello, 0); // 0 as a placeholder for 'answer'
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
            // Handle the invalid argument as needed, e.g., provide a default value.
        }
    }

    return QnA_array;
}



int main() {
int QnA::count = 0;
    design();
int Question_bank[7][5][20];
vector<QnA> question2 = store_position();
Question_bank = classifier_function(count , question2);
    int level = 1;
    string answer;
    int qn;
    string questions;
   vector<int> already_shown_qn;// for not repeating already shown questions
    vector<string> answer_options;
	

    for (int qn = 1; qn <= 20; qn++) {
        cout << "Score: " << points << endl;
        int qn1  =  question_finder(level ,Question_bank, already_shown_qn);
		  QnA question = question2[qn1]; // Accessing a specific question
        cout << qn << "."<<display_question(question) << endl;
     
        answer_options = answer_options_array(question);

        shuffle_vector(answer_options);
        for (int i = 0; i < 4; i++) {
            cout << i << ". " << answer_options[i] << endl;
        }
        cout << "Ans: ";
        cin >> answer;
        level = check_answer(qn1, answer, level , question);
    }

    float accuracy = (static_cast<float>(points) / 40) * 100; // Convert points to float for accurate division
    cout << "Your Total Score is:" << points << endl;
    cout << "Accuracy: " << accuracy << "%" << endl;

    return 0;
}







void sound_given()
{
  int frequency, duration;
  frequency = 1000;
  duration = 1000;

  cout << " frequency (in Hz): ";

  cout << "duration (in milliseconds): ";

  Beep(frequency, duration);

  return 0;
}
