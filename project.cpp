
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int points = 0;

class QnA {
    int qnr;
    char mt; // menu type
    string question_main;
    char answer;
    int level;
    public:
    	void add_input(int qn, string question, char answer_given , int level_given){
    		qnr = qn;
    		question_main = question;
    		answer = answer_given;
    		level = level_given;
    		cout << qn << "Saved"<< endl;
    		
		}
		char return_mt(){
			return mt;
		}
    	char return_answer(){
    		return answer;
		}
		string return_question(){
			return question_main;
		}
		int return_qnr(){
		    return qnr;
		}
};

QnA questions[15];
QnA real_question[700];
void display_menu(){
    
    char choice_str;
    string options[7] = {"General" ,"Sports" , "Programming" , "STEM" , "Geography and Food" , "History" , "Arts"};
    cout << "Enter the corresponding Number or select one of them to play:"<< endl;
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


char display_question( int qn) {
	char answer;
cout << real_question[qn].return_question();
cout << endl;
cin >> answer;
return answer;
}

int add_point(char mt ,int level) {
    int pointsToAdd = 0; // Initialize the variable

    // Adjust the pointsToAdd based on the question number ranges
    if (level==1) {
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

    return points + pointsToAdd; // Return the updated points
}

string check_answer(int qn ,char answer) {
    char real_answer = real_question[qn].return_answer();
   
    
    if (real_answer == answer) {
    	char st_var = real_question[qn].return_mt();
        add_point(st_var);// Update points using the add_point function
        cout << "Correct  ";
        if(level<5){
            	return level + 1;
			}
			else{
				return level;
			}
    } else {
        if (qn % 2 == 0) {
            cout << "Sorry. The answer is: " << real_answer;
           if(level>1){
            	return level -1;
			}
			else{
				return level;
			}
        } else {
            cout << "Nah. The answer is: " << real_answer;
            if(level>1){
            	return level -1;
			}
			else{
				return level;
			}
            
        }
    }
}
 
int main() {
    design();

   for(int k =1;k<2500;k++){
	   real_question[k-1] = {k, "Which gas is most abundant in Earth's atmosphere?", 'B'};

   }

   

    for (int qn = 1; qn <= 14; qn++) {
        char answer;
        cout << "Score: " << points << endl;
        cout << display_question(qn, questions) << endl;
        cout << "Ans: ";
        cin >> answer;
        cout << check_answer(qn, questions, answer) << endl;
    }
    
    float accuracy = (static_cast<float>(points) / 40) * 100; // Convert points to float for accurate division
    cout << "Your Total Score is: " << points << endl;
    cout << "Accuracy: " << accuracy << "%" << endl;

    return 0;
}


