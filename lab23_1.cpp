#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename.c_str());
    string line;
    while(getline(file,line)){
        int index1 = line.find(':');
        string name = line.substr(0,index1);

        int start = index1 +2 ;
        int end = line.find(" " , start);
        int score1 = stoi(line.substr(start , end-start));

        start = end + 1 ;
        end = line.find(" " , start);
        int score2 = stoi(line.substr(start , end-start));

        start = end + 1 ;
        end = line.find(" " , start);
        int score3 = stoi(line.substr(start , end-start));

        int total = score1 + score2 + score3;
        names.push_back(name);
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
    file.close();
}

void getCommand(string &command , string& key){
    cout << "Please input your command:\n" ;
    string line;
    getline(cin,line);
    int start = line.find(' ');
    if(start == -1){
        command = line;
        key = "";
        return;
    }
    command = line.substr(0 , start);
    key = line.substr(start + 1);
}

void searchName(vector<string>& names , vector<int>& scores , vector<char>& grade , string key){
    bool same = false;
    for(int i = 0 ; i < int(names.size()) ; i++){
        if( toUpperStr(names[i]) == key){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grade[i] << "\n";;
            cout << "---------------------------------\n";
            same = true;
            break;
        }
    }
    if(!same){
            cout << "---------------------------------\n";
            cout << "Cannot found.\n";
            cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool same = false;
    char grade = key[0];
    cout << "---------------------------------\n";
    for(int i = 0 ; i < int(names.size()) ; i++){
        if(grade == grades[i]){
            cout << names[i] << " (" << scores[i] << ")\n";
            same = true;
        }
    }
    if(!same){
            cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
