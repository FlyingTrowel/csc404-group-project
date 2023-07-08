/**
 * 1. Applying pointers concepts
 * 2. Applying \function concepts
 * 3. Applying file \io concepts
 * 4. Applying \1-d and 2-d array concepts
 * 5. Applying \text files concepts
 * 6. Integrating pointers, \function, \arrays and \text files in the system
 * 7. Interactivity
 * 8. Calculation
 * 9. Exception handling
 */

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//definition of Employee struct
struct Employee{
    int id;
    string name;
    string designation;
    double hourlyRate;
    int hoursWorked;
    int overtimeHours;
    double allowance;
    double deduction;
};
const int MAX_EMPLOYEE = 100;

int readEmployeeData(Employee employee[])
{
    ifstream file("D:\\Github\\Learn\\404\\csc404-group-project\\files\\employee.txt");
    if(!file){
        cerr<<"Error opening the file: ";
        return -1;
    }

    string line;
    int index = 0;

    while(getline(file, line))
    {
        stringstream linestream(line);
        string cell;

        getline(linestream, cell, ',');
        employee[index].id = stoi(cell);
        getline(linestream, cell, ',');
        employee[index].name = cell;
        getline(linestream, cell, ',');
        employee[index].designation = cell;
        getline(linestream, cell, ',');
        employee[index].hourlyRate = stod(cell);
        getline(linestream, cell, ',');
        employee[index].hoursWorked = stoi(cell);
        getline(linestream, cell, ',');
        employee[index].overtimeHours = stoi(cell);
        getline(linestream, cell, ',');
        employee[index].allowance = stod(cell);
        getline(linestream, cell, ',');
        employee[index].deduction = stod(cell);

        index++;
    }

    file.close();
    return index;
}

void printEmployeeData(const Employee (&employee)[MAX_EMPLOYEE]){
    for(int i =0; i<100; i++){
        if(employee[i].name != "")
        {
            cout<<employee[i].id<<", ";
            cout<<employee[i].name<<", ";
            cout<<employee[i].designation<<", ";
            cout<<employee[i].hourlyRate<<", ";
            cout<<employee[i].hoursWorked<<", ";
            cout<<employee[i].overtimeHours<<", ";
            cout<<employee[i].allowance<<", ";
            cout<<employee[i].deduction<<endl;
        }
        else
            break;
    }
}

int main(){
    //declare employee struct variable
    Employee employees[MAX_EMPLOYEE];

    int lastIndex = -1;

    //store data from employee.txt to employees array
    lastIndex = readEmployeeData(employees);

    //display all the employee data
    printEmployeeData(employees);


}