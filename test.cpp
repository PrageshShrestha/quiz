//doesn't work on non windows system
//should return ascii_value for system
#include <random>
#include <string>
#include <sstream>// Include the header for stringstream
#include <fstream>
#include <codecvt> 
#include <ctime>
#include <algorithm> // Include algorithm for shuffle
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<thread>
#include<stdlib.h>
#include<numeric>

using namespace std;

class QnA {
    string question;
    string answer;
    int points = 0;
    vector<string> options;
    public:
        void getData(string *q, string *a, vector<string> o) {
            question = *q;
            answer = *a;
            options = o;
            
        }
        void pointAdd(bool x){
            if (x){
                points += 1;
            }
            else{
                points += 1;
            }
        }
        void print(int *l) {
            char key = 0;
            int option = 0;
            do{
                system("cls");
                cout << question << '\n';
                for (int i = 0; i < 4; i++){
                    if (i == option){
                        cout << u8"\u2794";
                    }
                    cout << options[i];
                }
                key = _getch(); 
            }while(key != '\r');
            if (answer == options[option]){
                points+= *l;
                if (*l != 5){
                    *l++;
                }
            }
            else if(*l != 1){
                *l--;
            }
            cout << endl;
        }
};

//[level][questionNumber]
QnA questionBank[5][20];

int timer() {
    int timeLimit = 10; // Set the time limit in seconds
    auto startTime = chrono::steady_clock::now();
    auto endTime = startTime + chrono::seconds(timeLimit);

    while (chrono::steady_clock::now() < endTime)
    {
        // Calculate remaining time
        int remainingTime = chrono::duration_cast<chrono::seconds>(endTime - chrono::steady_clock::now()).count();
        cout << "Time remaining: " << remainingTime << " seconds\r" << std::flush;
        this_thread::sleep_for(chrono::milliseconds(1000)); // Wait for 1 second
    }

    cout << "Time's up!!!!!!!" << endl;
    return 0;
}


int menu() {
    char key = 0;
    int s = 0;
    system("CLS");
    do{
        key = 0;
        system("CLS");
        if (s == 0)
            cout << u8"\u2794" << "MATH114\nPHYS102\nENEV101\nCOMP116\nENGT105\nENGG112\n";
        else if (s == 1)
            cout << "MATH114\n" << u8"\u2794" << "PHYS102\nENEV101\nCOMP116\nENGT105\nENGG112\n";
        else if (s == 2)
            cout << "MATH114\nPHYS102\n" << u8"\u2794" << "ENEV101\nCOMP116\nENGT105\nENGG112\n";
        else if (s == 3)
            cout << "MATH114\nPHYS102\nENEV101\n" << u8"\u2794" << "COMP116\nENGT105\nENGG112\n";
        else if (s == 4)
            cout << "MATH114\nPHYS102\nENEV101\nCOMP116\n" << u8"\u2794" << "ENGT105\nENGG112\n";
        else if (s == 5)
            cout << "MATH114\nPHYS102\nENEV101\nCOMP116\nENGT105\n" << u8"\u2794" << "ENGG112\n";
        else
            s = 0;
        while (key == 0) {
            key = getch();
        }
        switch (key) {
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
    }while (key != '\r');
    return s;
}

void loadQuestion(int subjectCode) {
    
    //for opening the file in UTF-8
    ifstream questionFile;
    questionFile.open("questions.txt");
    string unparsedString;
    int qN;
    vector<string> option;
    int level;
    int subject;
    //subject_code)qn)level)question|option1|option2|option3|option4|answer\
    question format
    char temp[100];
    while (getline(questionFile, unparsedString)) {
        int counter = 0;
        int i = 0;
        
        while(unparsedString[counter] != ')'){
            temp[i] = unparsedString[counter];
            counter++;
            i++;
        }
        temp[i] = '\0';
        counter++;
        i = 0;
        subject = stoi(temp);
        if (subject == subjectCode){
            while(unparsedString[counter] != ')'){
            temp[i] = unparsedString[counter];
            counter++;
            i++;
        }
        temp[i] = '\0';
        qN = stoi(temp);
        counter++;
        i = 0;
        while(unparsedString[counter] != ')'){
            temp[i] = unparsedString[counter];
            counter++;
            i++;
        }
        temp[i] = '\0';
        level = stoi(temp);
        counter++;
        i = 0;
        char temp3[50];

        while(unparsedString[counter] != '|'){
            temp3[i] = unparsedString[counter];
            counter++;
            i++;
        }
        temp[i] = '\0';
        string question{temp3};
        counter++;
        i = 0;
        
        char temp1[4][50];
        
        for (int j = 0; j < 4; j++){
            while(unparsedString[counter] != '|'){
                temp1[j][i] = unparsedString[counter];
                counter++;
                i++;
            }
            temp1[j][i] = '\0';
            option.push_back(temp1[j]);
            counter++;
            i = 0;
        }

        while(unparsedString[counter] != '\\'){
            temp[i] = unparsedString[counter];
            counter++;
            i++;
        }
        temp[i] = '\0';
        string answer{temp};
        counter++;
        i = 0;
        questionBank[level][qN].getData(&question, &answer, option);
        }
    }
    questionFile.close();
}
int random(int min, int max){
    random_device rd;
    uniform_int_distribution<int> dist(min, max);
    return dist(rd);
}
void displayQuestion() {
    int level = 0;
    int questionNumber;
    vector<int> questionAvailable[5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 20; j++) {
            questionAvailable[i].push_back(j);
        }
    }
    system("CLS");
    for (int i = 0; i <= 20; i++) {
        do{
            questionNumber = random(0,19);
            cout << questionNumber;
        }while (!count(questionAvailable[level].begin(),questionAvailable[level].end(), questionNumber));
        questionBank[level][questionNumber].print(&level);

        cout << "HI";

    }
    this_thread::sleep_for(chrono::milliseconds(1));

}


int main(){
    int level;
    int subjectCode = menu();
    loadQuestion(subjectCode);
    thread th1(displayQuestion);
    thread th2(timer);
    th1.join();
    th2.join();
}
