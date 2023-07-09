/**
 * c++11 minimum
 * TODO: 1. Applying \pointers concepts
 * TODO: 2. Applying \function concepts
 * TODO: 3. Applying file \i \o concepts
 * TODO: 4. Applying \1-d and \2-d array concepts
 * TODO: 5. Applying \text files concepts
 * TODO: 6. Integrating \pointers, \function, \arrays and \text files in the system
 * TODO: 7. Interactivity
 * TODO: 8. \Calculation
 * TODO: 9. Exception handling
 *
 * TODO: https://stackoverflow.com/questions/49775560/how-to-create-standalone-exe-in-clion
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>

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

void printEmployeeData(Employee employee[], int lastIndex){
    for(int i = 0; i<lastIndex; i++) {
        cout << employee[i].id << ", "<<employee[i].name<<", "<<employee[i].designation<<", "<<employee[i].hourlyRate<<", "<<employee[i].hoursWorked<<", "<<employee[i].overtimeHours<<", "<<employee[i].allowance<<", "<<employee[i].deduction<<endl;
    }
}

void addEmployee(Employee& employee, int* lastIndex) {
    bool validInput = false;

    while (!validInput) {
        // Prompt for employee details
        cout << "Enter the employee details:" << endl;
        try {
            cout << "ID: ";
            cin >> employee.id;
            if (!cin) {
                throw runtime_error("Invalid input. ID must be an integer.");
            }

            cin.ignore();  // Ignore the newline character left in the input buffer

            cout << "Name: ";
            getline(cin, employee.name);

            cout << "Designation: ";
            getline(cin, employee.designation);

            cout << "Hourly Rate: ";
            cin >> employee.hourlyRate;
            if (!cin) {
                throw runtime_error("Invalid input. Hourly rate must be a number.");
            }

            cout << "Hours Worked: ";
            cin >> employee.hoursWorked;
            if (!cin) {
                throw runtime_error("Invalid input. Hours worked must be an integer.");
            }

            cout << "Overtime Hours: ";
            cin >> employee.overtimeHours;
            if (!cin) {
                throw runtime_error("Invalid input. Overtime hours must be an integer.");
            }

            cout << "Allowance: ";
            cin >> employee.allowance;
            if (!cin) {
                throw runtime_error("Invalid input. Allowance must be a number.");
            }

            cout << "Deduction: ";
            cin >> employee.deduction;
            if (!cin) {
                throw runtime_error("Invalid input. Deduction must be a number.");
            }

            validInput = true;
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    *lastIndex += 1;
}

void addEmployeeToFile(Employee employee[], int lastIndex)
{
    ofstream file("D:\\Github\\Learn\\404\\csc404-group-project\\files\\employee.txt");

    for(int i = 0; i< lastIndex; i++)
    {
        file<<employee[i].id<<",";
        file<<employee[i].name<<",";
        file<<employee[i].designation<<",";
        file<<employee[i].hourlyRate<<",";
        file<<employee[i].hoursWorked<<",";
        file<<employee[i].overtimeHours<<",";
        file<<employee[i].allowance<<",";
        file<<employee[i].deduction<<endl;
    }

    file.close();
}

void removeEmployee(Employee employee[], int& lastIndex) {
    // Print the employee data
    printEmployeeData(employee, lastIndex);

    // Prompt for employee ID to remove
    int idToRemove;
    cout << "Enter the ID of the employee to remove: ";
    cin >> idToRemove;

    bool employeeFound = false;

    // Find the employee with the matching ID
    for (int i = 0; i < lastIndex; i++) {
        if (employee[i].id == idToRemove) {
            // Shift elements to remove the employee
            for (int j = i; j < lastIndex - 1; j++) {
                employee[j] = employee[j + 1];
            }

            lastIndex--;
            employeeFound = true;
            break;
        }
    }

    // Check if employee was found and removed
    if (employeeFound) {
        cout << "Employee with ID " << idToRemove << " has been removed." << endl;
        // Update the employee file
        addEmployeeToFile(employee, lastIndex);
    } else {
        cout << "Employee with ID " << idToRemove << " not found." << endl;
    }
}

void editEmployee(Employee employee[], int lastIndex) {
    // Print the employee data
    printEmployeeData(employee, lastIndex);

    // Prompt for employee ID to edit
    int idToEdit;
    cout << "Enter the ID of the employee to edit: ";
    cin >> idToEdit;

    bool employeeFound = false;
    int fieldToEdit;

    // Find the employee with the matching ID
    for (int i = 0; i < lastIndex; i++) {
        if (employee[i].id == idToEdit) {
            employeeFound = true;

            // Prompt for the field to edit
            cout << "Select the field to edit:" << endl;
            cout << "1. Name" << endl;
            cout << "2. Designation" << endl;
            cout << "3. Hourly Rate" << endl;
            cout << "4. Hours Worked" << endl;
            cout << "5. Overtime Hours" << endl;
            cout << "6. Allowance" << endl;
            cout << "7. Deduction" << endl;
            cout << "Enter your choice: ";
            cin >> fieldToEdit;

            // Edit the chosen field
            switch (fieldToEdit) {
                case 1:
                    cin.ignore();
                    cout << "Enter the new name: ";
                    getline(cin, employee[i].name);
                    break;
                case 2:
                    cin.ignore();
                    cout << "Enter the new designation: ";
                    getline(cin, employee[i].designation);
                    break;
                case 3:
                    cout << "Enter the new hourly rate: ";
                    cin >> employee[i].hourlyRate;
                    break;
                case 4:
                    cout << "Enter the new hours worked: ";
                    cin >> employee[i].hoursWorked;
                    break;
                case 5:
                    cout << "Enter the new overtime hours: ";
                    cin >> employee[i].overtimeHours;
                    break;
                case 6:
                    cout << "Enter the new allowance: ";
                    cin >> employee[i].allowance;
                    break;
                case 7:
                    cout << "Enter the new deduction: ";
                    cin >> employee[i].deduction;
                    break;
                default:
                    cout << "Invalid choice. No field updated." << endl;
                    break;
            }

            break;
        }
    }

    // Check if employee was found and edited
    if (employeeFound) {
        cout << "Employee with ID " << idToEdit << " has been edited." << endl;
        // Update the employee file
        addEmployeeToFile(employee, lastIndex);
    } else {
        cout << "Employee with ID " << idToEdit << " not found." << endl;
    }
}

void calculateMonthlySalary(Employee employee[], double salary[][5], int lastIndex) {
    ofstream file("D:\\Github\\Learn\\404\\csc404-group-project\\files\\payroll.txt");

    for (int i = 0; i < lastIndex; i++) {
        double regularPay = employee[i].hourlyRate * employee[i].hoursWorked;
        double overtimePay = employee[i].hourlyRate * 1.5 * employee[i].overtimeHours;
        double totalPay = regularPay + overtimePay + employee[i].allowance - employee[i].deduction;

        salary[i][0] = employee[i].id;
        salary[i][1] = regularPay;
        salary[i][2] = overtimePay;
        salary[i][3] = totalPay;
        salary[i][4] = totalPay / (employee[i].hoursWorked + employee[i].overtimeHours);
    }

    file<<"Monthly Salary"<<endl;
    file<<left<<setw(11)<<"Employee ID "<<setw(20)<<"Name"<<right<<setw(20)<<"Regular Pay "<<setw(20)<<"Overtime Pay "<<setw(20)<<"Total Pay "<<setw(20)<<"Average Pay Rate"<< endl;
    for(int i = 0; i<lastIndex; i++)
    {
        file<<left<<setw(11)<<employee[i].id<<" ";
        file<<setw(20)<<employee[i].name;
        for(int j = 1; j<=4; j++)
        {
            file<<right<<setw(20)<<fixed<<setprecision(2)<<salary[i][j];
        }
        file<<endl;
    }


}


int main(){
    //declare employee struct variable
    Employee employees[MAX_EMPLOYEE];

    int lastIndex = -1;
    int userInput = 0;

    //store data from employee.txt to employees array
    lastIndex = readEmployeeData(employees);

    while(userInput != -1){
        //TODO: add try catch
        cout<<"Choose what you want to do\n";
        cin>>userInput;




        //print employee data
        if(userInput == 1)
        {
            //display all the employee data
            printEmployeeData(employees, lastIndex);
        }
        //insert new employee details and update the file
        else if(userInput == 2)
        {
            //add an employee
            Employee* addEmp = &employees[lastIndex];
            addEmployee(*addEmp, &lastIndex);
            cout<<lastIndex;
            printEmployeeData(employees, lastIndex);
            addEmployeeToFile(employees, lastIndex);
        }
        //remove employee
        else if(userInput == 3)
        {
            removeEmployee(employees, lastIndex);
        }
        //edit employee
        else if(userInput == 4)
        {
            editEmployee(employees, lastIndex);
        }
        // Calculate monthly salary for each employee
        else if(userInput == 5)
        {
            double salary[MAX_EMPLOYEE][5];
            calculateMonthlySalary(employees, salary, lastIndex);
        }
        //exit
        else if(userInput == -1)
        {
            break;
        }
        //wrong input number
        else
        {
            cout<<"Invalid input: "<<userInput;
        }


    }

    cout<<"System is shutting down...";
    return 0;
}