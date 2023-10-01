
#include <iostream>
#include <random>
#include <string>
#include <fstream>

#include <thread>
#include <chrono>
#include <vector>

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
};
void store_position(){
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
    int total_array[total_count];
    for(int i =0; i<total_count;i++){
    	
    	for(int j=0;j<4;j++){
    		int num = (i*4) + j;
    		total_array[i][j] = position[num];
		}
    	
	}
	
	for ( int i=0;i<total_count;i++){
		string array_que[4];
		for(int j=0;j<4;j++){
		     if(total_array[i][j]==2){
			 
			int startPosition = 0; // Starting position
    int endPosition = 1; }  // Ending position (excluding position 305)
else if(total_array[i][j]==3 ){
	
	int startPosition = 0; // Starting position
    int endPosition = 2;
	
}
else if(j == 0 && i !=0){
	
	int startPosition = total_array[i-1][3]; // Starting position
    int endPosition = total_array[i][j];
}
else{
		int startPosition = total_array[i][j-1]; // Starting position
    int endPosition = total_array[i][j];
	
}
    inputFile.seekg(startPosition, ios::beg); 

    char buffer[endPostion-startPosition]; 
    inputFile.read(buffer, endPosition - startPosition + 1); // Read the specified number of characters

    string extractedString(buffer, endPosition - startPosition + 1); // Convert the buffer to a string
    array_que[j] = buffer;
    	
    	
	}
		QnA real_question[i+1]::add_input(i+1, array_que[1], array_que[2], stoi(array_que[3] ), stoi(answer_que[0] ));	
	
		
	
	
		}
		
		
	}
	


    	cout<< "The total questions are :"<< total_count<<endl;
}


int main(){
    store_position();
    return 0;
    
    
    

}
