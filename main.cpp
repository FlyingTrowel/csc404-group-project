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

void addEmployee(Employee& employee, int* lastIndex)
{
    //TODO: ADD ERROR HANDLING HERE
    cin>>employee.id;
    cin.ignore();
    getline(cin, employee.name);
    getline(cin, employee.designation);
    cin>>employee.hourlyRate;
    cin>>employee.hoursWorked;
    cin>>employee.overtimeHours;
    cin>>employee.allowance;
    cin>>employee.deduction;

    *lastIndex +=1;
}

void addEmployeeData(Employee employee[], int lastIndex)
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

void removeEmployee(Employee (&employee)[MAX_EMPLOYEE], int lastIndex)
{
    printEmployeeData(employee, lastIndex);
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

void payroll(int lastIndex, Employee employee[]){



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
        //add employee to txt
        else if(userInput == 2)
        {
            //add an employee
            Employee* addEmp = &employees[lastIndex];
            addEmployee(*addEmp, &lastIndex);
            cout<<lastIndex;
            printEmployeeData(employees, lastIndex);
            addEmployeeData(employees, lastIndex);
        }
        //remove employee
        else if(userInput == 3)
        {
            removeEmployee(employees, lastIndex);
        }
        // Calculate monthly salary for each employee
        else if(userInput == 4)
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