#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


using namespace std;

class QNA{//question and answer
	string question;
	string answers;
    string question_file;
    string answer_file;
    string subject_code;
    vector<int> question_available{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,0};
	public:
    int random(){
        int r;
        do{
            r = rand() % (question_available.size());
        }while (!count(question_available.begin(), question_available.end(), r));

        remove(question_available.begin(), question_available.end(), r);
        return r;
    }
	void load_question(){
		fstream q;
        q.open(question_file, ios::out);

        if (q.is_open()){
            for (int i = 1; i <= random(); i++){
                getline(q, question);
            }
        }
	}
    int subjectRegister(int s){
        switch (s){
            case 1:
                subject_code = "math";
                break;
            case 2:
                subject_code = "physics";
                break;
            case 3:
                subject_code = "enviroment";
                break;
            case 4:
                subject_code = "computer";
                break;
            case 5:
                subject_code = "english";
                break;
            case 6:
                subject_code = "engineering";
                break;
            default:
                return 1;
        }
        return 0;
    }
    void file_chooser(int level){
        question_file = subject_code + '/' + to_string(level) + ".txt";
    }
    void print(){
        cout << question << '\n';
    }

};

int main(){
    QNA q1;
    q1.subjectRegister(2);
    q1.file_chooser(1);
    q1.load_question();
}
