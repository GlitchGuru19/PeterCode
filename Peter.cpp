#include <iostream> // for the basic input and output to the console
#include <fstream> // For writing to the text file
#include <conio.h>// for the getch() function
#include <filesystem> // For checking current path

#define green system ("color A") // defines the green color to be used in the system
#define red system ("color 4") // defines the red color to be used in the system
#define white system ("color f") // defines the white color to be used in the system

using namespace std;

struct Employee {
    string NRC_PassportNo;
    string firstName;
    string surName;
    int age;
    double basicSalary;
    string department;
    double TAX_amount;
    double NAPSA_contribution;
    double NHIMA_contribution;
    double netPay;
    string employmentStatus;
};

ifstream infile;
ofstream outFile;

Employee employee;

const int SIZE = 100;
Employee marketing[SIZE];
Employee development[SIZE];
double SALARY, TAX, NAPSA, NHIMA, NET;

void menu();
void managerLog(int);
void searchEmployee(Employee[SIZE]);
void managerMenu();
void addEmployee(int);
void saveEmployee(int, Employee);
double getTax(double);
void loadMarketingEmployees();
void loadDevelopmentEmployees();
void saveDataToFile (int);
void displayEmployees(Employee[SIZE]);
void deleteEmployee(int);
void editEmployee(int);

void loadDevelopmentEmployees(){ // Reads data from the Development department's text file
    infile.open("DevelopmentDepartment.txt");
    if(infile){
        for (int j = 0; j < SIZE; j++){
            if (infile >> development[j].firstName) {
                infile >> development[j].surName >> development[j].NRC_PassportNo >> development[j].age >> development[j].employmentStatus >> development[j].basicSalary >> development[j].NHIMA_contribution >> development[j].NAPSA_contribution
                >> development[j].TAX_amount >> development[j].netPay;
            }
            else
                break;
        }
    }
    infile.close();
}
void loadMarketingEmployees(){ // Reads data from the Marketing department's text file
    infile.open("MarketingDepartment.txt");
    if(infile){
        for (int j = 0; j < SIZE; j++){
            if (infile >> marketing[j].firstName) {
                infile >> marketing[j].surName >> marketing[j].NRC_PassportNo >> marketing[j].age >> marketing[j].employmentStatus >> marketing[j].basicSalary >> marketing[j].NHIMA_contribution >> marketing[j].NAPSA_contribution >> marketing[j].TAX_amount >> marketing[j].netPay;
            }
            else
                break;
        }
    }
    infile.close();
}
double getTax(double salary){ // Function that calculates the tax
    if (salary < 5101)
        return 0;
    else if (salary < 7101)
        return (0.20 * salary);
    else if (salary < 9200)
        return (0.30 * salary);
    else
        return (0.37 * salary);
}
void saveEmployee(int dept, Employee empToExport){ // Function that saves Employee details according to the department

    string fileName;

    if (dept == 1)
        fileName = "MarketingDepartment.txt";
    else if (dept == 2)
        fileName = "DevelopmentDepartment.txt";

    outFile.open(fileName, ios::app);

    if (outFile.is_open()){
        outFile << empToExport.firstName << endl;
        outFile << empToExport.surName << endl;
        outFile << empToExport.NRC_PassportNo << endl;
        outFile << empToExport.age << endl;
        outFile << empToExport.employmentStatus << endl;
        outFile << empToExport.basicSalary << endl;
        outFile << empToExport.NHIMA_contribution << endl;
        outFile << empToExport.NAPSA_contribution << endl;
        outFile << empToExport.TAX_amount << endl;
        outFile << empToExport.netPay << endl;
        cout << "\t\t\tEmployee Added Successfully!" << endl << endl;
        cout << "\t\t\tPress any key to continue..." << endl;
        getch();
    }
    else {
        cout << "\t\t\tError Saving Employee. Error Opening File: " << fileName << endl;
    }

    outFile.close();
}
void addEmployee(int dept){ // Function that adds Employee details according to the department
    cout << "\n\n\t\t\tAdd Employee Information" << endl;
    cout << "\t\t\tEnter First name: ";
    cin >> employee.firstName;
    cout << "\t\t\tEnter surname: ";
    cin >> employee.surName;
    cout << "\t\t\tEnter NRC NO/Passport No: ";
    cin >> employee.NRC_PassportNo;
    cout << "\t\t\tEnter age: ";
    cin >> employee.age;
    cout << "\t\t\tEnter Basic salary: ";
    cin >> employee.basicSalary;
    cout << "\t\t\tEnter employment status(Permanent/Contract): ";
    cin >> employee.employmentStatus;

    NHIMA = employee.basicSalary * 0.01;
    NAPSA = employee.basicSalary * 0.05;
    TAX = getTax(employee.basicSalary);
    NET = employee.basicSalary - (NHIMA + NAPSA + TAX);

    employee.NHIMA_contribution = NHIMA;
    employee.NAPSA_contribution = NAPSA;
    employee.TAX_amount = TAX;
    employee.netPay = NET;
    saveEmployee(dept, employee);
}
void managerMenu(){ // Displays a number of action to perform by the Hub Manager and Human Resource Officer
    loadDevelopmentEmployees();
    loadMarketingEmployees();
    int choice, department;
    while (true)
    {
        white;
        cout << "\n\n";
        cout << "\t\t\tMAIN MENU" << endl;
        cout << "\t\t\tPlease choose an option" << endl;
        cout << "\t\t\t1. ADD EMPLOYEE" << endl;
        cout << "\t\t\t2. DELETE EMPLOYEE" << endl;
        cout << "\t\t\t3. SEARCH FOR EMPLOYEE" << endl;
        cout << "\t\t\t4. EDIT EMPLOYEE RECORD" << endl;
        cout << "\t\t\t5. DISPLAY EMPLOYEES BY DEPARTMENT" << endl;
        cout << "\t\t\t6. EXIT" << endl;
        cout << "\t\t\tEnter your choice here => ";
        cin >> choice;
        if (choice > 0 && choice < 6) {
            cout << "\t\t\tPlease choose the department" << endl;
            cout << "\t\t\t1. Marketing\n\t\t\t2. Development" << endl;
            cout << "\t\t\tYour choice => ";
            cin >> department;
            if (department < 1 || department > 2) {
                cout << "\n\t\t\tInvalid Department Choice." << endl << endl;
                managerMenu();
            }
        }
        system("cls");
        switch (choice){
        case 1:
            addEmployee(department);
            break;
        case 2:
            deleteEmployee(department);
            saveDataToFile(department);
            break;
        case 3:
            if (department == 1)
             searchEmployee(marketing);
             else if (department == 2)
              searchEmployee(development);
            break;
        case 4:
            editEmployee(department);
            saveDataToFile(department);
            break;
        case 5:
            if (department == 1)
             displayEmployees(marketing);
            else if (department == 2)
             displayEmployees(development);
            break;
        case 6:
            {
                cout << "\n\nThank you for using the system" << endl;
                exit(0);
                break;
            }
        default:
            cout << "\t\t\tInvalid Option Selected. Try again!";
            break;
        }
    }
}
void managerLog(int manager){ //Function that allows to log in as Human Resource Officer or the Hub Manager
    string managerID, systemID, managerPassword, systemPassword;
    int n = 1;
    (manager == 1) ?
    (infile.open("HubManager.txt"), infile >> systemID >> systemPassword) :
    (infile.open("HROfficer.txt"), infile >> systemID >> systemPassword);

    if (infile)
    {
        while (n < 4){ // This loop gives the Hub Manager 2 attempts to enter the correct credentials
         cout << "\n\n";
         cout << "\t\t\tEMPLOYEE INFORMATION SYSTEM" << endl;
         cout << "\t\t\tMANAGER MENU" << endl;
         cout << "\t\t\tEnter the user ID: ";
         cin >> managerID;
         cout << "\t\t\tEnter Password: ";
         cin >> managerPassword;
         if (systemID == managerID && systemPassword == managerPassword){ // Compares the entered credentials with those in the file. If the details are the same,
             cout << "\t\t\tLogin successful!" << endl;
             green;
             cout << "\t\t\tPress any key to continue...";
             getch();
             system("cls");
             managerMenu();              // The function calls the Hub Manager's Menu.
            break;
         }
         else {
             cout << "\t\t\tWrong credentials. Please try again." << endl;
             red;
             n++;
         }
         if (n == 3) {
             cout << "\t\t\tOops. Too many attempts. SYSTEM LOCKED" << endl;
             red;
             exit(0);
         }
        }
    }
    else {
        cout << "\t\t\tError opening file." << endl;
    }
    infile.close();
}
void menu (){ // Function that allows the user to choose what they want to log in as.
    int response, department;
    white;
    cout << "\t\t\tWelcome. What do you wish to login as? " << endl;
    cout << "\t\t\t1. Hub Manager\n\t\t\t2. Human Resource Manager\n\t\t\t3. Employee\n\t\t\t4. Exit\n\t\t\tResponse => ";
    cin >> response;
    system("cls");
    if (response == 1)
        managerLog(1);
    else if (response == 2)
        managerLog(2);
    else if (response == 3) {
        cout << "\t\t\tPlease choose the department" << endl;
        cout << "\t\t\t1. Marketing\n\t\t\t2. Development" << endl;
        cout << "\t\t\tYour choice: ";
        cin >> department;
        if (department == 1)
         searchEmployee(marketing);
        else if (department == 2)
         searchEmployee(development);
         menu();
    }
    else if (response == 4)
    {
        cout << "\n\nExiting...\nThank you for using the program.";
        exit(0);
    }
    else {
        cout << "\t\t\tInvalid Option Chosen. Try again! \n\n";
        menu();
    }
}
void searchEmployee(Employee arr[]){ // Function that searches for the Employee according to the department entered
    int answer;
    string nrc_Passport_Entered;
    bool isFound = false;

    cout << "\t\t\tEnter NRC_PassportNo: ";
    cin >> nrc_Passport_Entered;

    for (int s = 0; s < SIZE; s++) {
        if (arr[s].NRC_PassportNo == nrc_Passport_Entered) {
            cout << "\t\t\tEmployee Found!" << endl << endl;
            cout << "\t\t\tFirst Name: " << arr[s].firstName << endl;
            cout << "\t\t\tSurname: " << arr[s].surName << endl;
            cout << "\t\t\tNRC/Passport Number: " << arr[s].NRC_PassportNo << endl;
            cout << "\t\t\tAge: " << arr[s].age << endl;
            cout << "\t\t\tEmployment Status(Permanent/Contract): " << arr[s].employmentStatus << endl;
            cout << "\t\t\tBasic salary: " << arr[s].basicSalary << endl;
            cout << "\t\t\tNHIMA Contribution: " << arr[s].NHIMA_contribution << endl;
            cout << "\t\t\tNAPSA Contribution: " << arr[s].NAPSA_contribution << endl;
            cout << "\t\t\tTax amount:" << arr[s].TAX_amount << endl;
            cout << "\t\t\tNet Pay: " << arr[s].netPay << endl << endl;
            isFound = true;
        }
      }
      if (!isFound){
        cout << "\n\t\t\tNo Employee record with entered  NRC/Passport Number exists." << endl;
        red;
      }
      cout << "\t\t\tPress any key to continue.." << endl;
      getch();
      system("cls");
}

void saveDataToFile (int dept) { // Function that saves the information according to the department
    if (dept == 1) {
        outFile.open("MarketingDepartment.txt");
        for (int i = 0; i < SIZE; i++){

            if (marketing[i].firstName != "\0") {
            outFile << marketing[i].firstName << endl;
            outFile << marketing[i].surName << endl;
            outFile << marketing[i].NRC_PassportNo << endl;
            outFile << marketing[i].age << endl;
            outFile << marketing[i].employmentStatus << endl;
            outFile << marketing[i].basicSalary << endl;
            outFile << marketing[i].NHIMA_contribution << endl;
            outFile << marketing[i].NAPSA_contribution << endl;
            outFile << marketing[i].TAX_amount << endl;
            outFile << marketing[i].netPay << endl;
        }
        }
    }
    else if (dept == 2){
        outFile.open("DevelopmentDepartment.txt");
        for (int i = 0; i < SIZE; i++){
            if (development[i].firstName != "\0"){
            outFile << development[i].firstName << endl;
            outFile << development[i].surName << endl;
            outFile << development[i].NRC_PassportNo << endl;
            outFile << development[i].age << endl;
            outFile << development[i].employmentStatus << endl;
            outFile << development[i].basicSalary << endl;
            outFile << development[i].NHIMA_contribution << endl;
            outFile << development[i].NAPSA_contribution << endl;
            outFile << development[i].TAX_amount << endl;
            outFile << development[i].netPay << endl;
        }
        }
    }
    outFile.close();
}
void displayEmployees(Employee arr[]) { // Displays Employees according to department chosen
    loadDevelopmentEmployees();
    loadMarketingEmployees();
        if ((arr[0].NRC_PassportNo) == "\0"){
            cout << "\t\t\tNo Employees to display" << endl;
        }
        else {
            cout << "\t\t\tEmployees under Marketing!" << endl << endl;
            for (int m = 0; m < SIZE; m++) {
                if(arr[m].firstName == "\0")
                    break;
                cout << "\t\t\tFirst Name: " << arr[m].firstName << endl;
                cout << "\t\t\tSurname: " << arr[m].surName << endl;
                cout << "\t\t\tNRC_Passport Number: " << arr[m].NRC_PassportNo << endl;
                cout << "\t\t\tAge: " << arr[m].age << endl;
                cout << "\t\t\tEmployment Status(Permanent/Contract): " << arr[m].employmentStatus << endl;
                cout << "\t\t\tBasic salary: " << arr[m].basicSalary << endl;
                cout << "\t\t\tNHIMA Contribution: " << arr[m].NHIMA_contribution << endl;
                cout << "\t\t\tNAPSA Contribution: " << arr[m].NAPSA_contribution << endl;
                cout << "\t\t\tTax amount:" << arr[m].TAX_amount << endl;
                cout << "\t\t\tNet Pay: " << arr[m].netPay << endl;
                cout << "\n\n";
            }
                cout << "\t\t\tPress any key to continue...";
                getch();
                system("cls");
        }
}

void editEmployee(int dept) // function that edits Employee's details for the Marketing Department
{
    loadDevelopmentEmployees();
    loadMarketingEmployees();
    int answer;
    string nrc_Passport_Entered;

    cout << "\t\t\tEnter NRC_PassportNo: ";
    cin >> nrc_Passport_Entered;

    if (dept == 1) {

        for (int e = 0; e < SIZE; e++) {
            if (marketing[e].NRC_PassportNo == nrc_Passport_Entered){
                cout << "\t\t\tEmployee Found!" << endl << endl;
                cout << "\t\t\tFirst Name: " << marketing[e].firstName << endl;
                cout << "\t\t\tSurname: " << marketing[e].surName << endl;
                cout << "\t\t\tNRC/Passport Number: " << marketing[e].NRC_PassportNo << endl;
                cout << "\t\t\tAge: " << marketing[e].age << endl;
                cout << "\t\t\tEmployment Status(Permanent/Contract): " << marketing[e].employmentStatus << endl;
                cout << "\t\t\tBasic salary: " << marketing[e].basicSalary << endl;
                cout << "\t\t\tNHIMA Contribution: " << marketing[e].NHIMA_contribution << endl;
                cout << "\t\t\tNAPSA Contribution: " << marketing[e].NAPSA_contribution << endl;
                cout << "\t\t\tTax amount:" << marketing[e].TAX_amount << endl;
                cout << "\t\t\tNet Pay: " << marketing[e].netPay << endl;

                cout << "\t\t\tWould you like to edit this Employee's details? \n\t\t\t1. Yes\n\t\t\t2.No \n";
                cout << "\t\t\tEnter your response here: ";
                cin >> answer;

                if (answer == 1) {
                    cout << "\t\t\tEdit Employee Details" << endl;
                    cout << "\t\t\tFirst name: ";
                    cin >> marketing[e].firstName;
                    cout << "\t\t\tSurname: ";
                    cin >> marketing[e].surName;
                    cout << "\t\t\tNRC/Passport Number: ";
                    cin >> marketing[e].NRC_PassportNo;
                    cout << "\t\t\tAge: ";
                    cin >> marketing[e].age;
                    cout << "\t\t\tEmployment Status(Permanent/Contract): ";
                    cin >> marketing[e].employmentStatus;
                    cout << "\t\t\tBasic salary: ";
                    cin >> marketing[e].basicSalary;
                    cout << "\t\t\tNHIMA Contribution: " << marketing[e].NHIMA_contribution << endl;
                    cout << "\t\t\tNAPSA Contribution: " << marketing[e].NAPSA_contribution << endl;
                    cout << "\t\t\tTax amount:" << marketing[e].TAX_amount << endl;
                    cout << "\t\t\tNet Pay: " << marketing[e].netPay << endl;
                    cout << "\t\t\tEmployee edited successfully!" << endl;
                }
                else {
                    cout << "\t\t\tRedirecting to Main Menu...\n\t\t\tPress any key to continue..." << endl;
                    getch();
                    system("cls");
                    managerMenu();
                }
            }
        }
    } else if (dept == 2) {
        for (int e = 0; e < SIZE; e++) {
            if (development[e].NRC_PassportNo == nrc_Passport_Entered){
                cout << "\t\t\tEmployee Found!" << endl << endl;
                cout << "\t\t\tFirst Name: " << development[e].firstName << endl;
                cout << "\t\t\tSurname: " << development[e].surName << endl;
                cout << "\t\t\tNRC/Passport Number: " << development[e].NRC_PassportNo << endl;
                cout << "\t\t\tAge: " << development[e].age << endl;
                cout << "\t\t\tEmployment Status(Permanent/Contract): " << development[e].employmentStatus << endl;
                cout << "\t\t\tBasic salary: " << development[e].basicSalary << endl;
                cout << "\t\t\tNHIMA Contribution: " << development[e].NHIMA_contribution << endl;
                cout << "\t\t\tNAPSA Contribution: " << development[e].NAPSA_contribution << endl;
                cout << "\t\t\tTax amount:" << development[e].TAX_amount << endl;
                cout << "\t\t\tNet Pay: " << development[e].netPay << endl;

                cout << "\t\t\tWould you like to edit this Employee's details? \n\t\t\t1. Yes\n\t\t\t2.No \n";
                cout << "\t\t\tEnter your response here: ";
                cin >> answer;

                if (answer == 1) {
                    cout << "\t\t\tEdit Employee Details" << endl;
                    cout << "\t\t\tFirst name: ";
                    cin >> development[e].firstName;
                    cout << "\t\t\tSurname: ";
                    cin >> development[e].surName;
                    cout << "\t\t\tNRC/Passport Number: ";
                    cin >> development[e].NRC_PassportNo;
                    cout << "\t\t\tAge: ";
                    cin >> development[e].age;
                    cout << "\t\t\tEmployment Status(Permanent/Contract): ";
                    cin >> development[e].employmentStatus;
                    cout << "\t\t\tBasic salary: ";
                    cin >> development[e].basicSalary;
                    cout << "\t\t\tNHIMA Contribution: " << development[e].NHIMA_contribution << endl;
                    cout << "\t\t\tNAPSA Contribution: " << development[e].NAPSA_contribution << endl;
                    cout << "\t\t\tTax amount:" << development[e].TAX_amount << endl;
                    cout << "\t\t\tNet Pay: " << development[e].netPay << endl;
                    cout << "\t\t\tEmployee edited successfully!" << endl;
                }
                else {
                    cout << "\t\t\tRedirecting to Main Menu...\n\t\t\tPress any key to continue..." << endl;
                    getch();
                    system("cls");
                    managerMenu();
                }
                break;
            }
        }
    }
}

void deleteEmployee(int dept) { // Deletes Employees according to department chosen
    loadDevelopmentEmployees();
    loadMarketingEmployees();
    int answer;
    string nrc_Passport_Entered;

    cout << "\t\t\tEnter NRC_PassportNo: ";
    cin >> nrc_Passport_Entered;

    if (dept == 1) {
        for (int e = 0; e < SIZE; e++) {
            if (marketing[e].NRC_PassportNo == nrc_Passport_Entered) {
                cout << "\t\t\tEmployee Found!" << endl << endl;
                cout << "\t\t\tFirst Name: " << marketing[e].firstName << endl;
                cout << "\t\t\tSurname: " << marketing[e].surName << endl;
                cout << "\t\t\tNRC/Passport Number: " << marketing[e].NRC_PassportNo << endl;
                cout << "\t\t\tAge: " << marketing[e].age << endl;
                cout << "\t\t\tEmployment Status " << marketing[e].employmentStatus << endl;
                cout << "\t\t\tBasic salary: " << marketing[e].basicSalary << endl;
                cout << "\t\t\tNHIMA Contribution: " << marketing[e].NHIMA_contribution << endl;
                cout << "\t\t\tNAPSA Contribution: " << marketing[e].NAPSA_contribution << endl;
                cout << "\t\t\tTax amount:" << marketing[e].TAX_amount << endl;
                cout << "\t\t\tNet Pay: " << marketing[e].netPay << endl << endl;

                cout << "\t\t\tWould you like to delete this Employee? \n\t\t\t1. Yes\n\t\t\t2.No \n";
                cout << "\t\t\tEnter your response here: ";
                cin >> answer;

                if (answer == 1) {
                    cout << "\t\t\tDeleting Employee's Details..." << endl; // we assign variables with doubles and integers to zero and string to empty string
                    marketing[e].firstName = "\0";
                    marketing[e].surName = "\0";
                    marketing[e].NRC_PassportNo = "\0";
                    marketing[e].age = 0;
                    marketing[e].employmentStatus = "\0";
                    marketing[e].basicSalary = 0;
                    marketing[e].NHIMA_contribution = 0;
                    marketing[e].NAPSA_contribution =0;
                    marketing[e].TAX_amount = 0;
                    marketing[e].netPay = 0;
                    cout << "\t\t\tEmployee deleted successfully!" << endl;
                    cout << "\t\t\tPress any key to continue...";
                    getch();
                    system("cls");
                }
                else {
                    cout << "\t\t\tRedirecting to Main Menu." << endl;
                    cout << "\t\t\tPress any key to continue...";
                    getch();
                    system("cls");
                    menu();
                }
            }
        }
    } else if (dept == 2) {
        for (int e = 0; e < SIZE; e++) {
            if (development[e].NRC_PassportNo == nrc_Passport_Entered) {
                cout << "\t\t\tEmployee Found!" << endl << endl;
                cout << "\t\t\tFirst Name: " << development[e].firstName << endl;
                cout << "\t\t\tSurname: " << development[e].surName << endl;
                cout << "\t\t\tNRC/Passport Number: " << development[e].NRC_PassportNo << endl;
                cout << "\t\t\tAge: " << development[e].age << endl;
                cout << "\t\t\tEmployment Status " << development[e].employmentStatus << endl;
                cout << "\t\t\tBasic salary: " << development[e].basicSalary << endl;
                cout << "\t\t\tNHIMA Contribution: " << development[e].NHIMA_contribution << endl;
                cout << "\t\t\tNAPSA Contribution: " << development[e].NAPSA_contribution << endl;
                cout << "\t\t\tTax amount:" << development[e].TAX_amount << endl;
                cout << "\t\t\tNet Pay: " << development[e].netPay << endl << endl;

                cout << "\t\t\tWould you like to delete this Employee? \n\t\t\t1. Yes\n\t\t\t2.No \n";
                cout << "\t\t\tEnter your response here: ";
                cin >> answer;

                if (answer == 1) {
                    cout << "\t\t\tDeleting Employee's Details..." << endl; // we assign variables with doubles and integers to zero and string to empty string
                    development[e].firstName = "\0";
                    development[e].surName = "\0";
                    development[e].NRC_PassportNo = "\0";
                    development[e].age = 0;
                    development[e].employmentStatus = "\0";
                    development[e].basicSalary = 0;
                    development[e].NHIMA_contribution = 0;
                    development[e].NAPSA_contribution =0;
                    development[e].TAX_amount = 0;
                    development[e].netPay = 0;
                    cout << "\t\t\tEmployee deleted successfully!" << endl;
                    cout << "\t\t\tPress any key to continue...";
                    getch();
                    system("cls");
                }
                else {
                    cout << "\t\t\tRedirecting to Main Menu." << endl;
                    cout << "\t\t\tPress any key to continue...";
                    getch();
                    system("cls");
                    menu();
                }
            }
        }
    }
}

int main () {
    loadDevelopmentEmployees();
    loadMarketingEmployees();
    menu();
    return 0;
}
