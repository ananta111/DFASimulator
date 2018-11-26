//Author: Ananta Thapaliya



#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>



using namespace std;


class Node {

    public:
        int from;
        char input;
        int to;
        int getFrom(){
            return from;
        }

        char getInput(){
            return input;
        }

        int getTo(){
            return to;
        }

        string toString(){
            return to_string(from) + "--" + input + "-->" + to_string(to);
        }

        Node(){

        };
};


int checkAlphabetValidity(char c, vector<char> alphabets){
    int isValidChar = 0;
    for (char a: alphabets){
        if (c==a){
            isValidChar = 1;
            break;
        }
    }

    return isValidChar;
}





int simulateDFA(string input, vector<Node> transitions, vector<char> alphabets, vector<int> finalStates) {

    fstream outputfile;
    outputfile.open("../output.txt", fstream::app);
    outputfile << "String " << input << " was given to the machine as input\n\n";
    int result = 0;
    int curr = 0;
    Node finalNode;
    for (char c: input){
        if (checkAlphabetValidity(c,alphabets)==0){
            cout << "You entered " << c << ", an invalid alphabet that does not belong to the language of this  DFA\n";
            outputfile << "You entered " << c << ", an invalid alphabet that does not belong to the language of this  DFA\n"
            << "------------------------------------------------------------------------------\n";
            return 0;
        }
        for (Node n: transitions){
            if (n.from == curr && n.input == c){
                curr = n.to;
                cout << n.toString() << "\n";
                outputfile << n.toString() << "\n";
                finalNode = n;
                break;
            }
        }
    }

    for (int i: finalStates){
        if (finalNode.to == i) {
            result = 1;
            break;
        }
    }

    if (result==1){
        outputfile << "The string was accepted by this machine.\n\n---------------------------------------------------\n";
    }else{
        outputfile << "The string was rejected by this machine.\n\n----------------------------------------------------\n";
    }

    return result;


}


int main() {

    cout  << "[Compiled successfully] " __TIMESTAMP__ <<"\n\n";
    std::ifstream myfile; //inputfile containing the DFA
    std:string fileName;
    cout << "Enter the name of the file which should be located in the same directory as your .cpp file\n";
    cin >> fileName;
    fileName = "../" + fileName;

    myfile.open(fileName);
    if (!myfile){
        cerr <<"Unable to open the file";
        exit(1);
    }

    std::string firstLine;

    std::getline(myfile,firstLine);

    vector<int> finalStates;

    for (char c: firstLine){
        if (c!=' '){
            finalStates.push_back((int)c-48);
        }
    }

    vector<Node> transitions;
    std::string nextLine;
    vector<char> alphabets;

    while (std::getline(myfile,nextLine).good()){
        Node node;
        node.from = (nextLine[0]-'0');
        node.input = nextLine[2];
        node.to = nextLine[4]-'0';
        if (std::find(alphabets.begin(),alphabets.end(),node.input)==alphabets.end()){
            alphabets.push_back(node.input);
        }

        transitions.push_back(node);

    }



    //Primary DFA Simulator Program
    while (true){
        string s;
        cout << "Enter the test string or enter \'quit\' if you are done\n";
        cin >> s;
        if (s=="quit"){
            break;
        }

        int result = simulateDFA(s, transitions,alphabets,finalStates);

        if (result==1){
            cout << "The string was accepted\n";


        }else{
            cout << "The string was rejected\n";
        }

    }




}









