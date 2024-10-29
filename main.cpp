#include "main.h"


int main () {
    AVLVector avlTree;
    string command = "";
    cout << "Welcome! To use this AVL-Vector program, type a command along with your rank/element in a single line (exact same format as listed in test data)." << endl;
    cout << "Example input: 'INSERT 1 55'" << endl;
    cout << "Enter one of the following commands: INSERT, DELETE, REPLACE, ELEMENT-AT, RANK, PRINT, or QUIT followed by the necessary numerical inputs!" << endl;

    while (true) {
        cout << "> ";

        getline(cin, command);

        size_t start = command.find_first_not_of(" \t");
        if (start == string::npos) {
            command = "";  // case where the command is all spaces
        } else {
            size_t end = command.find_last_not_of(" \t");
            command = command.substr(start, end - start + 1);
        }
        
        stringstream input(command);
        string operation; 
        input >> operation; //reading in input

        //function calls based on inputted operation!
        if (operation == "INSERT") {
            int rank, element;
            if (input >> rank >> element) {
                int result = avlTree.insertAtRank(rank, element);
                cout << endl;
            } else {
                cout << "Invalid input——the proper format is INSERT <int> <int>!" << endl;
            }


        } else if (operation == "DELETE") {
            int rank;
            if (input >> rank) {
                int result = avlTree.removeAtRank(rank);
                cout << endl;
            } else {
                cout << "Invalid input——the proper format is DELETE <int>!" << endl;
            }


        } else if (operation == "REPLACE") {
            int rank, element;
            if (input >> rank >> element) {
                int result = avlTree.replaceAtRank(rank, element);
                cout << endl;
            } else {
                cout << "Invalid input——the proper format is REPLACE <int> <int>!" << endl;
            }


        } else if (operation == "ELEMENT-AT") {
            int rank;
            if (input >> rank) {
                int result = avlTree.elementAtRank(rank);
                if (result != -1) {
                    cout << avlTree.elementAtRank(rank) << "\n" << endl;
                }
            } else {
                cout << "Invalid input——the proper format is ELEMENT-AT <int>!" << endl;
            }


        } else if (operation == "RANK") {
            int element;
            if (input >> element) {
                int rank = avlTree.rankOf(element);
                if (rank != -1) {
                    cout << rank << "\n" << endl;
                } 
            } else {
                cout << "Invalid input——the proper format is RANK <int>!" << endl;
            }


        } else if (operation == "PRINT") {
            int rootValue = avlTree.getRootValue();
            if (rootValue == -1) {
                cout << "The AVL Tree is empty.\n" << endl;
            } else {
                avlTree.printAll();
            }


        } else if (operation == "QUIT") {
            cout << "Bye!" << endl;
            cout << "\n";
            return 0;


        } else {
            cout << "Error: Unknown Command:" << command << endl; 
        }
    }

    return 0;
}