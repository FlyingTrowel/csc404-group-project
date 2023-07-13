/**
 * MINIMUM REQUIREMENT: C++11
 *
 * TODO: 1. Applying \pointers concepts
 * TODO: 2. Applying \function concepts
 * TODO: 3. Applying file \i \o concepts
 * TODO: 4. Applying \1-d and \2-d array concepts
 * TODO: 5. Applying \text files concepts
 * TODO: 6. Integrating \pointers, \function, \arrays and \text files in the system
 * TODO: 7. \Interactivity
 * TODO: 8. \Calculation
 * TODO: 9. \Exception handling
 *
 * TODO: https://stackoverflow.com/questions/49775560/how-to-create-standalone-exe-in-clion
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <stdexcept>


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
string employeetxt = "D:\\Github\\Learn\\404\\csc404-group-project\\files\\employee.txt";
string payrolltxt = "D:\\Github\\Learn\\404\\csc404-group-project\\files\\payroll.txt";

//function prototypes
int readEmployeeData(Employee[]);
void printEmployeeData(const Employee[], int);
void addEmployee(Employee&, int*, const Employee[]);
void sortEmployeesById(Employee[], int);
void addEmployeeToFile(const Employee[], int);
void removeEmployee(Employee[], int&);
void editEmployee(Employee[], int);
void calculateMonthlySalary(const Employee[], double[][5], int);


int main() {
    Employee employees[MAX_EMPLOYEE];
    int lastIndex = -1;
    int userInput = 0;

    lastIndex = readEmployeeData(employees);

    while (userInput != -1) {
        try {
            cout << "\nChoose an option:\n";
            cout << "1. Print employee data\n";
            cout << "2. Insert new employee details\n";
            cout << "3. Remove an employee\n";
            cout << "4. Edit an employee\n";
            cout << "5. Calculate monthly salary for each employee\n";
            cout << "-1. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> userInput)) {
                throw runtime_error("Invalid input. Please enter a number.");
            }

            switch (userInput) {
                case 1:
                    printEmployeeData(employees, lastIndex);
                    break;
                case 2: {
                    Employee *addEmp = &employees[lastIndex];
                    //addEmployee(*addEmp, &lastIndex, employees);
                    addEmployee(*addEmp, &lastIndex, employees);
                    sortEmployeesById(employees, lastIndex);
                    cout << "New employee added:\n";
                    printEmployeeData(employees, lastIndex);
                    addEmployeeToFile(employees, lastIndex);
                }
                    break;
                case 3:
                    removeEmployee(employees, lastIndex);
                    break;
                case 4:
                    editEmployee(employees, lastIndex);
                    break;
                case 5: {
                    double salary[MAX_EMPLOYEE][5];
                    calculateMonthlySalary(employees, salary, lastIndex);
                    cout << "Monthly salary calculated and stored in payroll.txt.\n";
                }
                    break;
                case -1:
                    break;
                default:
                    cout << "Invalid input. Please enter a valid option.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
            }

            if (userInput != -1) {
                cout << "Operation completed.\n";
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "System is shutting down...\n";
    return 0;
}

int readEmployeeData(Employee employee[])
{
    ifstream file(employeetxt);
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

void printEmployeeData(const Employee employee[], int lastIndex) {
    cout<<endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(6) << "ID" << " | " << setw(20) << "Name" << " | " << setw(12) << "Designation" <<" | "<< setw(11) << "Hourly Rate" << " | " << setw(13) << "Hours Worked" << " | " << setw(10) << "Allowance" << " | " << setw(9) << "Deduction" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < lastIndex; i++) {
        cout << left << setw(6) << employee[i].id << " | "
             << setw(20) << employee[i].name << " | "
             << setw(12) << employee[i].designation << " | "
             << right << setw(11) << fixed << setprecision(2) << employee[i].hourlyRate << " | "
             << setw(13) << employee[i].hoursWorked << " | "
             << setw(10) << fixed << setprecision(2) << employee[i].allowance << " | "
             << setw(9) << fixed << setprecision(2) << employee[i].deduction << endl;
    }

    cout << "-----------------------------------------------------------------------------------------------------" << endl;
}

void addEmployee(Employee& employee, int* lastIndex, const Employee employees[]) {
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

            //non negative ID
            if(employee.id<=0)
            {
                throw runtime_error("Invalid input. Employee ID must be in positive integer range");
            }

            //unique employee ID
            for(int i = 0; i<*lastIndex; i++)
            {
                if(employee.id == employees[i].id)
                    throw runtime_error("Invalid input. Employee ID must be unique");
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

            if(employee.hourlyRate<0){
                throw runtime_error("Invalid input. Hourly rate cannot be negative");
            }

            cout << "Hours Worked: ";
            cin >> employee.hoursWorked;
            if (!cin) {
                throw runtime_error("Invalid input. Hours worked must be an integer.");
            }

            if(employee.hoursWorked<0){
                throw runtime_error("Invalid input. Hours worked cannot be negative");
            }

            cout << "Overtime Hours: ";
            cin >> employee.overtimeHours;
            if (!cin) {
                throw runtime_error("Invalid input. Overtime hours must be an integer.");
            }

            if(employee.overtimeHours<0){
                throw runtime_error("Invalid input. Overtime hours cannot be negative");
            }

            cout << "Allowance: ";
            cin >> employee.allowance;
            if (!cin) {
                throw runtime_error("Invalid input. Allowance must be a number.");
            }

            if(employee.allowance<0){
                throw runtime_error("Invalid input. Allowance cannot be negative");
            }

            cout << "Deduction: ";
            cin >> employee.deduction;
            if (!cin) {
                throw runtime_error("Invalid input. Deduction must be a number.");
            }

            if(employee.deduction<0){
                throw runtime_error("Invalid input. Deduction cannot be negative");
            }

            validInput = true;
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    *lastIndex += 1;
}

void sortEmployeesById(Employee employee[], int lastIndex) {
    for (int i = 0; i < lastIndex - 1; i++) {
        for (int j = 0; j < lastIndex - i - 1; j++) {
            if (employee[j].id > employee[j + 1].id) {
                // Swap employees
                Employee temp = employee[j];
                employee[j] = employee[j + 1];
                employee[j + 1] = temp;
            }
        }
    }
}

void addEmployeeToFile(const Employee employee[], int lastIndex)
{
    ofstream file(employeetxt);

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
    bool validInput = false;
    bool employeeFound = false;

    while(!validInput)
    {
        try {
            cout << "Enter the ID of the employee to remove: ";
            cin >> idToRemove;

            if (!cin || idToRemove <= 0) {
                throw runtime_error("Invalid ID");
            }

            validInput = true;

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
        }
        catch (const runtime_error &e) {
            cout << "Error: " << e.what() << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    bool validInput = false;

    while(!validInput){
        cout << "Enter the ID of the employee to edit: ";
        try{
            cin >> idToEdit;

            if(!cin || idToEdit <= 0)
                throw runtime_error("Invalid ID");

            validInput = true;
        }
        catch (const runtime_error& e){
            cout << "Error: " << e.what() << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }

    validInput = false;


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

                while(!validInput) {
                    cout << "Enter your choice: ";

                    try {
                        cin >> fieldToEdit;

                        if (!cin) {
                            throw runtime_error("Please input a number based on the choice above!");
                        }

                        // Edit the chosen field
                        while (!validInput) {
                            switch (fieldToEdit) {
                                case 1:
                                    cin.ignore();
                                    cout << "Enter the new name: ";
                                    getline(cin, employee[i].name);
                                    validInput = true;
                                    break;
                                case 2:
                                    cin.ignore();
                                    cout << "Enter the new designation: ";
                                    getline(cin, employee[i].designation);
                                    validInput = true;
                                    break;
                                case 3:
                                    cout << "Enter the new hourly rate: ";
                                    try {
                                        cin >> employee[i].hourlyRate;
                                        if (!cin || employee[i].hourlyRate < 0)
                                            throw runtime_error("Please input a valid number");
                                        validInput = true;
                                        break;
                                    }
                                    catch (const runtime_error &e) {
                                        cout << "Error: " << e.what() << endl << endl;
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                case 4:
                                    cout << "Enter the new hours worked: ";
                                    try {
                                        cin >> employee[i].hoursWorked;
                                        if (!cin || employee[i].hoursWorked < 0)
                                            throw runtime_error("Please input a valid integer");
                                        validInput = true;
                                        break;
                                    }
                                    catch (const runtime_error &e) {
                                        cout << "Error: " << e.what() << endl << endl;
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                case 5:
                                    cout << "Enter the new overtime hours: ";
                                    try {
                                        cin >> employee[i].overtimeHours;
                                        if (!cin || employee[i].overtimeHours < 0)
                                            throw runtime_error("Please input a valid integer");
                                        validInput = true;
                                        break;
                                    }
                                    catch (const runtime_error &e) {
                                        cout << "Error: " << e.what() << endl << endl;
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                case 6:
                                    cout << "Enter the new allowance: ";
                                    try {
                                        cin >> employee[i].allowance;
                                        if (!cin || employee[i].allowance < 0)
                                            throw runtime_error("Please input a valid number");
                                        validInput = true;
                                        break;
                                    }
                                    catch (const runtime_error &e) {
                                        cout << "Error: " << e.what() << endl << endl;
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                case 7:
                                    cout << "Enter the new deduction: ";
                                    try {
                                        cin >> employee[i].deduction;
                                        if (!cin || employee[i].deduction < 0)
                                            throw runtime_error("Please input a valid number");
                                        validInput = true;
                                        break;
                                    }
                                    catch (const runtime_error &e) {
                                        cout << "Error: " << e.what() << endl << endl;
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }
                                default:
                                    cout << "Invalid choice. No field updated." << endl;
                                    return;
                                    break;
                            }
                        }
                    }
                    catch (const runtime_error &e) {
                        cout << "Error: " << e.what() << endl << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
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

void calculateMonthlySalary(const Employee employee[], double salary[][5], int lastIndex) {
    ofstream file(payrolltxt);

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

    cout<<"Monthly Salary"<<endl;
    cout<<left<<setw(11)<<"Employee ID "<<setw(20)<<"Name"<<right<<setw(20)<<"Regular Pay "<<setw(20)<<"Overtime Pay "<<setw(20)<<"Total Pay "<<setw(20)<<"Average Pay Rate"<< endl;
    for(int i = 0; i<lastIndex; i++)
    {
        cout<<left<<setw(11)<<employee[i].id<<" ";
        cout<<setw(20)<<employee[i].name;
        for(int j = 1; j<=4; j++)
        {
            cout<<right<<setw(20)<<fixed<<setprecision(2)<<salary[i][j];
        }
        cout<<endl;
    }


}


