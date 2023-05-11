//
//  main.cpp
//  244A3
//
//  Created by Najmuddin Nazary on 2023-04-14.
//

#include <iostream>
using namespace std;
#include "TA.hpp"
#include <fstream>
#include <vector>
#include <sstream>



bool studentIdExists(const vector<TA>& TAs, int Id);

enum SortColumn { FIRST_NAME, WORKING_HOURS, STATUS, AGE, ID };

SortColumn getSortColumn();

void addNewTA(vector<TA>& TA);


bool getSortOrder();


void sortTAs(vector<TA> &TAs);



int main() {
    ifstream inputFile("TAs.txt");
    vector<TA> validTA;
    string line;
    int numRecords;
    
    if (inputFile.is_open()) {
        getline(inputFile, line);
        numRecords = stoi(line);
        for (int i = 0; i < numRecords; i++) {
            getline(inputFile, line);
            istringstream stream(line);
            string firstName, status;
            int workingHours, age, studentId;
            stream >> firstName >> workingHours >>status >> age >> studentId;
            if (status != "Alum") {
                validTA.push_back(TA(firstName,workingHours, status, age, studentId));
            }
        }
        inputFile.close();
    } else {
        cerr << "Unable to open file." <<endl;
        return 1;
    }
    
    ofstream outputFile("TAs.txt", ios::trunc);
    if (outputFile.is_open()) {
        outputFile << validTA.size() << endl;
        for (const auto &ta : validTA) {
            outputFile << ta.firstName << " "<< ta.workingHours <<" " << ta.status << " "
            << ta.age<< " " << ta.Id <<endl;
        }
        outputFile.close();
    } else {
        cerr <<"Unable to open file."<<endl;
        return 1;
    }
    
        
        int choice = 0;
        while (choice != 3) {
            cout << "1. Add new TA\n2. Sort TAs\n3. Save & Exit"<< endl;
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    addNewTA(validTA);
                    break;
                case 2:
                    sortTAs(validTA);
                    break;
                case 3:
                    cout << "Saving and exiting" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
        
        outputFile.open("TAs.txt", ios::trunc);
        
        if (outputFile.is_open()) {
            outputFile << validTA.size() << endl;
            for (const auto &ta : validTA) {
                outputFile << ta.firstName << " " << ta.workingHours << " " << ta.status << " "
                << ta.age << " " << ta.Id << endl;
            }
            outputFile.close();
        } else {
            cerr << "Unable to open file." << endl;
            return 1;
        }
        
        return 0;
}

/* -------------------------------------------------studentIdExists ---------------------------------------------------------*/


bool studentIdExists(const vector<TA>& TAs, int Id) {
    for (const auto& ta : TAs) {
        if (ta.Id == Id) {
            return true;
        }
    }
    return false;
}




/* -------------------------------------------------- addNewTA ---------------------------------------------------------------*/

void addNewTA(vector<TA>& TAs)
{
    string firstName, status;
    int workingHours, age, Id;
    cout << "Enter new TA information (First_Name Working_Hours Status age Student_Id): ";
    cin >> firstName >> workingHours >> status >> age >> Id;
    while (studentIdExists(TAs, Id)) {
        cout << "Student ID already exists. Please enter a new Student ID: ";
        cin >> Id;
    }
    TAs.push_back(TA(firstName, workingHours, status, age, Id));
}


/* ----------------------------------------------------getSortOrder ---------------------------------------------------------*/



bool getSortOrder() {
    int order;
    cout << "Select sort order:\n1. Ascending\n2. Descending\n";
    cin >> order;
    return order == 1;
}


/* -------------------------------------------------getSortColumn ---------------------------------------------------------*/


SortColumn getSortColumn() {
    int option;
    cout << "Select a column to sort by:\n"
                 "1. First Name\n"
                 "2. Working Hours\n"
                 "3. Status\n"
                 "4. Age\n"
                 "5. Student ID\n";
    cin >> option;
    return static_cast<SortColumn>(option - 1);
}
/* ---------------------------------------------------- sortTAs ---------------------------------------------------------------*/

void sortTAs(vector<TA> &TAs) {
    SortColumn column = getSortColumn();
    bool ascending = getSortOrder();

    sort(TAs.begin(), TAs.end(), [column, ascending](const TA &a, const TA &b) {
        bool compareResult;
        switch (column) {
            case FIRST_NAME:
                compareResult = a.firstName< b.firstName;
                break;
            case WORKING_HOURS:
                compareResult = a.workingHours < b.workingHours;
                break;
            case STATUS:
                compareResult = a.status < b.status;
                break;
            case AGE:
                compareResult = a.age < b.age;
                break;
            case ID:
                compareResult = a.Id < b.Id;
                break;
        }
        return ascending ? compareResult : !compareResult;
    });
}




