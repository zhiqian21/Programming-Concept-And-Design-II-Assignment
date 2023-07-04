#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#pragma warning(disable:4996)
#define STAFF_FILENAME "staff.txt"
#define STOCK_FILENAME "stock.bin"
#define SALES_FILENAME "sales.txt"
#define MEMBER_FILENAME "member.dat"
#define MEMBER_SECOND_FILENAME "tmp.dat"
#define MAX_STAFF_SIZE 50
#define MAX_MEMBER_SIZE 100
#define MAX_STOCK_SIZE 100
#define MAX_SALES_SIZE 100

/* Stock Structure */
typedef struct {
    int sDay, sMonth, sYear;
}LastRestockDate;

struct Supplier {
    char company[60], personInCharge[30], contactNo[12];
};

typedef struct {
    char itemCode[6], itemName[60], itemDesc[30];
    double cost;
    int qtyInStock, minLvl, reorderQty;
    struct Supplier supplier;
    LastRestockDate restockDate;
}Stock;


/* Sales Structure */
typedef struct {
    int day, month, year;
}SalesDate;

struct Item {
    char itemCode[6];
    char name[50];
    int qtyOrder;
    double unitPrice;
};

typedef struct {
    SalesDate date;
    int orderId;
    int nItem;
    char memberId[10];
    struct Item item;
    double total;
}SalesOrder;


/* Member Structure */
struct Name {
    char fname[20];
    char lname[20];
}; struct Name name;

struct Address {
    int no;
    char street[15];
    int postCode;
    char state[15];
}; struct Address add;

typedef struct {
    char memberId[8];
    struct Name name;
    char gender;
    char iC[14];
    char phoneNo[14];
    char upLineId[8];
    char email[31];
    struct Address add;
}Member;


/* Staff Structure */
typedef struct {
    int day, month, year;
}Date;

typedef struct {
    char  staffId[4], name[21], position[31], department[21], contactNumber[12];
    double salary;
    Date birthDate;
}Staff;


/* Function Declaration */
void logo();
void mainMenu();

//staff function declaration
int staffMain();
int addStaff();
void modifyStaff(Staff staff[], int nStaffs);
void deleteStaff(Staff staff[], int* nStaffs);
int searchStaff(Staff staff[], int nStaffs);
void displayAllStaff();
void staffMenu(Staff staff[]);
void writeIntoFile(Staff staff[], int nStaffs);
void readFile(Staff staff[], int* nStaffs);
void appendFile(Staff staff[], int nStaffs);
void login(Staff staff[], int nStaffs);

//member function declaration
void memberMain();
int addMember(int* nQty);
void displayMember();
void editMember();
int deleteMember(int* dQty);
void searchMember();
void summaryReport(int nQty, int dQty, int oldTtl);
int validateInput(int field, char id[8], char fname[20], char lname[20], char gender, char ic[14], char phoneNo[14], char email[31], int no, int postCode);

//sales function declaration
void salesMain();
void salesMenu(SalesOrder order, int nOrder);
int isValidDate(order);
void printDetail(SalesOrder order);
void readOrder(SalesOrder order[], int* nOrder);
void displayOrder(SalesOrder order);
void searchOrder(SalesOrder order, int nOrder);
void deleteSalesOrder(int orderId, int nOrder);
void modifyOrder(int orderId, int nOrder);
void addOrder(SalesOrder order, int nOrder);
int validOrderId(int id, int nOrder);
void comUpLine(int nOrder);

//stock function declaration
void stockMain();
void stockMenu(Stock stockItem[]);
void addStock();
void calcReorderQty(int, int, int*);
void displayStock();
void displaySupplierDetails();
void getStock(Stock stockItem[], int* sCount);
void searchStock(Stock stockItem[]);
void viewSearchedStock(Stock stockItem[], char itemCode[6], int sCount);
void modifyStock(Stock stockItem[]);
void deleteStock(Stock stockItem[]);
void updateQtyInStock(char itemCode[6], int qtyOrder);
int validateItemCode(char itemCode[6]);
void stockReport();


void main() {
    int nStaffs = 0;
    Staff staff[MAX_STAFF_SIZE];
    logo();
    readFile(staff, &nStaffs);
    login(staff, nStaffs);
}

void logo() {
    printf("             _____                ____       _____                   ____     ______      __  __      __    __   \n");
    printf(" /'\\_/`\\    /\\___ \\              /\\  _`\\    /\\  __`\\     /'\\_/`\\    /\\  _`\\  /\\  _  \\    /\\ \\/\\ \\    /\\ \\  /\\ \\\n");
    printf("/\\      \\   \\/__/\\ \\             \\ \\ \\/\\_\\  \\ \\ \\/\\ \\   /\\      \\   \\ \\ \\L\\ \\\\ \\ \\L\\ \\   \\ \\ `\\\\ \\   \\ `\\`\\\\/'/\n");
    printf("\\ \\ \\__\\ \\     _\\ \\ \\             \\ \\ \\/_/\\  \\ \\ \\ \\ \\  \\ \\ \\__\\ \\   \\ \\ ,__/ \\ \\  __ \\   \\ \\ , ` \\   `\\ `\\/'\n");
    printf(" \\ \\ \\_/\\ \\   /\\ \\_\\ \\             \\ \\ \\L\\ \\  \\ \\ \\_\\ \\  \\ \\ \\_/\\ \\   \\ \\ \\/   \\ \\ \\/\\ \\   \\ \\ \\\\ \\ \\    `\\ \\ \\\n");
    printf("  \\ \\_\\\\ \\_\\  \\ \\____/              \\ \\____/   \\ \\_____\\  \\ \\_\\\\ \\_\\   \\ \\_\\    \\ \\_\\ \\_\\   \\ \\_\\\\ \\_\\     \\ \\_\\\n");
    printf("   \\/_/ \\/_/   \\/___/                \\/___/     \\/_____/   \\/_/ \\/_/    \\/_/     \\/_/\\/_/    \\/_/ \\/_/      \\/_/\n\n");
}

void mainMenu() {
    int choice;
    do {
        printf("+=======================================+\n");
        printf("|             Main Menu                 |\n");
        printf("+=======================================+\n");
        printf("| 1. Staff Information                  |\n");
        printf("| 2. Member Information                 |\n");
        printf("| 3. Sales Information                  |\n");
        printf("| 4. Stock Information                  |\n");
        printf("| 5. Exit                               |\n");
        printf("+=======================================+\n");
        printf("Enter Your Selection > ");

        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cls");
            staffMain();
            break;
        case 2:
            system("cls");
            memberMain();
            break;
        case 3:
            system("cls");
            salesMain();
            break;
        case 4:
            system("cls");
            stockMain();
            break;
        case 5:
            exit(-1);
        default:
            printf("Invalid Selection! Please enter (1 - 5).\n");
            break;
        }
    } while (choice != 5);
}


/* STAFF INFORMATION MODULE */

void login(Staff staff[], int nStaffs) {
    int index = -1;
    char password[7];

    printf("\n");
    printf("======================================\n");
    printf("=                                    =\n");
    printf("=              LOGIN PAGE            =\n");
    printf("=                                    =\n");
    printf("======================================\n\n");

    char staffId[4];
    printf("Enter your Staff ID to login ^.^ : ");
    rewind(stdin);
    gets(staffId);

    //validation for staff id
    while ((strlen(staffId) != 3) ||
        (staffId[0] != 'S') ||
        (!isdigit(staffId[1])) ||
        (!isdigit(staffId[2]))) {
        printf("\n");
        printf("======================================\n");
        printf("=                                    =\n");
        printf("=     INVALID USERNAME OR PASSWORD   =\n");
        printf("=                                    =\n");
        printf("======================================\n\n");
        printf("Enter your Staff ID to login ^.^ : ");
        rewind(stdin);
        gets(staffId);
    }

    //compare staff id key in with the staff id in the txt file
    for (int i = 0; i < nStaffs; i++)
    {
        if (strcmp(staff[i].staffId, staffId) == 0) {
            index = i;
            break;
        }
        if (i == nStaffs - 1) {
            printf("Staff ID not found.\n");

        }
    }
    //if staff id found, enter pw
    if (index != -1) {
        printf("Enter password: ");
        rewind(stdin);
        gets(password);
        if (strcmp(password, "090909") == 0) {
            printf("\n");
            printf("======================================\n");
            printf("=                                    =\n");
            printf("=         LOGIN SUCCESSFUL           =\n");
            printf("=                                    =\n");
            printf("======================================\n\n");
            mainMenu();
        }
        else {
            printf("Invalid password. Please try again.\n");
        }
    }
}

int staffMain() {
    int nStaffs = 0;
    Staff staff[MAX_STAFF_SIZE];

    readFile(staff, &nStaffs);
    staffMenu(staff);

    system("pause");
    return 0;

}

void writeIntoFile(Staff staff[], int nStaffs) {
    FILE* fptr = fopen(STAFF_FILENAME, "w");

    if (fptr == NULL) {
        printf("File Not Found\n\n");
        return;
    }
    //write into file
    for (int i = 0; i < nStaffs; i++) {
        fprintf(fptr, "%s|%s|%02d-%02d-%d|%s|%s|%s|%.2lf\n",
            staff[i].staffId, staff[i].name, staff[i].birthDate.day,
            staff[i].birthDate.month, staff[i].birthDate.year, staff[i].position,
            staff[i].department, staff[i].contactNumber, staff[i].salary);
    }

    if (fclose(fptr) == 0) {
        printf("File written successfully.\n");
    }
    else {
        printf("Error writing to file.\n");
    }
}

void readFile(Staff staff[], int* nStaffs) {
    FILE* fptr = fopen(STAFF_FILENAME, "r");

    if (fptr == NULL) {
        printf("File Not Found\n\n");
        return;
    }
    int i = 0;
    while (fscanf(fptr, "%[^|]|%[^|]|%d-%d-%d|%[^|]|%[^|]|%[^|]|%lf\n", &staff[i].staffId, &staff[i].name,
        &staff[i].birthDate.day, &staff[i].birthDate.month, &staff[i].birthDate.year,
        &staff[i].position, &staff[i].department, &staff[i].contactNumber, &staff[i].salary) != EOF) {
        i++;
        *nStaffs = i;
    }
    fclose(fptr);
}

void appendFile(Staff staff[], int nStaffs) {
    FILE* fptr = fopen(STAFF_FILENAME, "a");

    if (fptr == NULL) {
        printf("File Not Found\n\n");
        return;
    }
    for (int i = 0; i < nStaffs; i++) {
        fprintf(fptr, "%s|%s|%02d-%02d-%d|%s|%s|%s|%.2lf\n",
            staff[i].staffId, staff[i].name, staff[i].birthDate.day,
            staff[i].birthDate.month, staff[i].birthDate.year, staff[i].position,
            staff[i].department, staff[i].contactNumber, staff[i].salary);
    }
    fclose(fptr);
}

void staffMenu(Staff staff[]) {
    int nStaffs = 0;
    int selection;
    char validation;
    do {
        printf("==========================================\n");
        printf("|              MENU                      |\n");
        printf("==========================================\n");
        printf("|   1.  Add    Staff Detail              |\n");
        printf("|   2.  Modify Staff Detail              |\n");
        printf("|   3.  Delete Staff Record              |\n");
        printf("|   4.  Search Staff Detail              |\n");
        printf("|   5.  Display Staff Detail             |\n");
        printf("|   6.  Exit                             |\n");
        printf("==========================================\n");
        do {
            printf("Please enter your selection: ");
            rewind(stdin);
            scanf("%d%c", &selection, &validation);
        } while (selection <= 0 || validation != '\n');
        readFile(staff, &nStaffs);
        switch (selection)
        {
        case 1:
            system("cls");
            addStaff();
            break;
        case 2:
            system("cls");
            modifyStaff(staff, nStaffs);
            break;
        case 3:
            system("cls");
            deleteStaff(staff, nStaffs);
            break;
        case 4:
            system("cls");
            searchStaff(staff, nStaffs);
            break;
        case 5:
            system("cls");
            displayAllStaff();
            break;
        case 6:
            system("cls");
            mainMenu();
            break;
        default:
            printf("\n\n\nNVALID INPUT,PLEASE TRY AGAIN ^.^\n\n");
            break;
        }
    } while (selection != 6);


}

int addStaff() {
    Staff staff[MAX_STAFF_SIZE];
    int nStaffs = 0;
    char continueAdd;
    char validation;
    if (nStaffs < MAX_STAFF_SIZE) {
        do {
            printf("Add Staff Information(Y=Yes/N=No)?");
            rewind(stdin);
            continueAdd = tolower(getchar());
            if (continueAdd == 'y') {
                printf("Staff ID (eg.S09) : ");
                scanf("%s", staff[nStaffs].staffId);
                if (
                    strlen(staff[nStaffs].staffId) == 3 &&
                    staff[nStaffs].staffId[0] == 'S' &&
                    isdigit(staff[nStaffs].staffId[1]) &&
                    isdigit(staff[nStaffs].staffId[2]))
                {
                    printf("NAME:");
                    rewind(stdin);
                    gets(staff[nStaffs].name);

                    printf("Birth Of Date(DD-MM-YYYY):");
                    scanf("%d-%d-%d", &staff[nStaffs].birthDate.day, &staff[nStaffs].birthDate.month, &staff[nStaffs].birthDate.year);
                    if (staff[nStaffs].birthDate.year >= 1900 &&
                        staff[nStaffs].birthDate.year <= 2100 &&
                        staff[nStaffs].birthDate.month >= 1 &&
                        staff[nStaffs].birthDate.month <= 12 &&
                        staff[nStaffs].birthDate.day <= 31)
                    {
                        printf("Position: ");
                        rewind(stdin);
                        scanf("%[^\n]", staff[nStaffs].position);
                        printf("Department:");
                        rewind(stdin);
                        scanf("%[^\n]", staff[nStaffs].department);
                        printf("Contact Number:");
                        rewind(stdin);
                        scanf("%s", staff[nStaffs].contactNumber);
                        if ((staff[nStaffs].contactNumber[0] == '0') &&
                            (staff[nStaffs].contactNumber[1] == '1'))
                        {
                            printf("Salary:");
                            scanf("%lf", &staff[nStaffs].salary);
                            if (
                                staff[nStaffs].salary >= 1500)
                            {
                                printf("Record Successfully Added...\n");
                                (nStaffs)++;

                                appendFile(staff, nStaffs); //add to text file
                                displayAllStaff(); //display all include new added data

                            }
                            else
                            {
                                printf("\nInvalid Staff Salary.It must more than 1500\n\n");
                            }
                        }
                        else {
                            printf("Invalid Contact Input!\n");
                        }
                    }
                    else {
                        printf("Invalid Date Input.Please Try Again >.<\n");
                    }
                }
                else {
                    printf("Invalid Staff Input! Please try again\n");
                }
            }
        } while (continueAdd == 'y');

    }
    else {
        printf("\n\nMEMORY FULL, SORRY.\n");
    }

    return nStaffs;
}

void modifyStaff(Staff staff[], int nStaffs) {
    char nStaffId[7];
    char name[30], position[30], department[30], contactNumber[12];
    float salary;
    int bDay, bMonth, bYear;
    int option;
    printf("Enter staff ID : ");
    rewind(stdin);
    gets(nStaffId);
    if (
        (strlen(nStaffId) == 3) &&
        (nStaffId[0] == 'S') &&
        (isdigit(nStaffId[1])) &&
        (isdigit(nStaffId[2])))
    {
        readFile(staff, &nStaffs);
        for (int i = 0; i < nStaffs; i++) {
            if (strcmp(staff[i].staffId, nStaffId) == 0) {
                //update//
                printf("+--------------------------------+\n");
                printf("|         Staff Record           |\n");
                printf("+--------------------------------+\n");
                printf("| Staff Name     | %s\n", staff[i].name);
                printf("| Birth Of Date  | %d-%d-%d\n", staff[i].birthDate.day, staff[i].birthDate.month, staff[i].birthDate.year);
                printf("| Position       | %s\n", staff[i].position);
                printf("| Department     | %s\n", staff[i].department);
                printf("| Contact Number | %s\n", staff[i].contactNumber);
                printf("| Salary         | %.2lf\n", staff[i].salary);
                printf("+--------------------------------+\n");

                printf("Which record you want to modify (^_^)?\n");
                do {
                    printf("+----------------------------------+\n");
                    printf("|          Modify Staff Record     |\n");
                    printf("+----------------------------------+\n");
                    printf("| 1. Modify Staff Name             |\n");
                    printf("| 2. Modify Staff Birthday         |\n");
                    printf("| 3. Modify Staff Position         |\n");
                    printf("| 4. Modify Staff Department       |\n");
                    printf("| 5. Modify Contact Number         |\n");
                    printf("| 6. Modify Staff Salary           |\n");
                    printf("| 7. Exit                          |\n");
                    printf("+----------------------------------+\n");

                    printf("Please enter your option: ");
                    rewind(stdin);
                    scanf("%d", &option);

                    switch (option) {
                    case 1:
                        printf("Enter new staff name: ");
                        rewind(stdin);
                        gets(name);
                        strcpy(staff[i].name, name);
                        printf("Modify Successfully ^.^\n");
                        break;
                    case 2:
                        printf("Enter new Birth Of Date for staff:");
                        scanf("%d-%d-%d", &bDay, &bMonth, &bYear);
                        if ((bYear >= 1900) &&
                            (bYear <= 2100) &&
                            (bMonth >= 1) &&
                            (bMonth <= 12) &&
                            (bDay >= 1) &&
                            (bDay <= 31))
                        {
                            staff[i].birthDate.day = bDay;
                            staff[i].birthDate.month = bMonth;
                            staff[i].birthDate.year = bYear;
                            printf("Modify Successfully ^.^\n");
                        }
                        else {
                            printf("Invalid Date Input.Please Try Again >.<\n");
                        }
                        break;
                    case 3:
                        printf("Enter new position:");
                        rewind(stdin);
                        scanf("%[^\n]", &position);
                        strcpy(staff[i].position, position);
                        printf("Modify Successfully ^.^\n");
                        break;
                    case 4:
                        printf("Enter new department:");
                        rewind(stdin);
                        scanf("%[^\n]", &department);
                        strcpy(staff[i].department, department);
                        printf("Modify Successfully ^.^\n");
                        break;
                    case 5:
                        printf("Enter new contact number:");
                        rewind(stdin);
                        scanf("%s", &contactNumber);
                        if (
                            strlen(contactNumber) <= 11 &&
                            strlen(contactNumber) >= 10 &&
                            (contactNumber[0] == '0') &&
                            (contactNumber[1] == '1'))
                        {
                            strcpy(staff[i].contactNumber, contactNumber);
                            printf("Modify Successfully ^.^\n");
                        }
                        else {
                            printf("Invalid Contact Number!\n");
                        }
                        break;
                    case 6:
                        printf("Enter new salary:");
                        scanf("%f", &salary);
                        if (salary >= 1500)
                        {
                            staff[i].salary = salary;
                            printf("Modify Successfully ^.^\n");
                        }
                        else {
                            printf("Invalid Input\n");
                        }
                        break;
                    case 7:
                        printf("\nSee You Next Time ^3^\n");
                        break;
                    default:
                        printf("\n\nINVALID INPUT,PLEASE TRY AGAIN ^.^\n\n");
                        break;
                    }
                } while (option != 7);
                writeIntoFile(staff, nStaffs); //write all the successfully modify data into txt file
            }
        }

    }
    else {
        printf("Invalid Staff Input! Please try again\n");
    }
}

int searchStaff(Staff staff[], int nStaffs) {
    char staffId[7];
    int index = -1;

    printf("Enter Staff ID: ");
    rewind(stdin);
    gets(staffId);
    if (
        (strlen(staffId) == 3) &&
        (staffId[0] == 'S') &&
        (isdigit(staffId[1])) &&
        (isdigit(staffId[2])))
    {

        int numberOfMatching = 0;
        int nStaff = 0;

        Staff matchingStaff[MAX_STAFF_SIZE];

        for (int i = 0; i < nStaffs; i++) {
            if (strcmp(staff[i].staffId, staffId) == 0) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            printf("\t\t\t\t\t---Record Found---\t");
            printf("\n");
            printf("==============================================================================================================================\n");
            printf("%-10s|%-20s|%-11s|%-30s|%-20s|%-20s|%-8s\n", "Staff ID", "Staff Name", "BirthOfDate", "Staff Position", "Department", "Contact Number", "Salary");
            printf("==============================================================================================================================\n");
            printf("%-10s|%-20s|%02d-%02d-%-05d|%-30s|%-20s|%-20s|%-8.2lf\n", staff[index].staffId, staff[index].name,
                staff[index].birthDate.day, staff[index].birthDate.month, staff[index].birthDate.year, staff[index].position,
                staff[index].department, staff[index].contactNumber, staff[index].salary);


        }
        else {
            printf("Record not found.\n");
        }
        return index;
    }
    else
        printf("Invalid Staff Input! Please try again\n");
}

void displayAllStaff() {
    Staff staff;

    printf("\t\t\t\t\t---Staff Details---\t");
    printf("\n");
    printf("==============================================================================================================================\n");
    printf("%-10s|%-20s|%-11s|%-30s|%-20s|%-20s|%-8s\n", "Staff ID", "Staff Name", "BirthOfDate", "Staff Position", "Department", "Contact Number", "Salary");
    printf("==============================================================================================================================\n");

    FILE* fptr = fopen(STAFF_FILENAME, "r");

    if (fptr == NULL) {
        printf("File Not Found\n\n");
        return;
    }

    while (fscanf(fptr, "%[^|]|%[^|]|%02d-%02d-%04d|%[^|]|%[^|]|%[^|]|%lf\n\n", &staff.staffId, &staff.name,
        &staff.birthDate.day, &staff.birthDate.month, &staff.birthDate.year,
        &staff.position, &staff.department, &staff.contactNumber, &staff.salary) != EOF) {

        printf("%-10s|%-20s|%02d-%02d-%-05d|%-30s|%-20s|%-20s|%-8.2lf\n", staff.staffId, staff.name,
            staff.birthDate.day, staff.birthDate.month, staff.birthDate.year, staff.position,
            staff.department, staff.contactNumber, staff.salary);

    }
    printf("\n");
    fclose(fptr);
}

void deleteStaff(Staff staff[], int* nStaffs) {
    printf("-----Enter the staffID to delete the record-----\n");

    char searchId[7];
    int index = 0;
    int nSta = 0;
    char confirmDelete;
    readFile(staff, &nSta);
    printf("Enter Staff ID: ");
    rewind(stdin);
    gets(searchId);
    for (int i = 0; i < nSta; i++) {
        if (strcmp(staff[i].staffId, searchId) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        printf("Record Found:\n");
        printf("==============================================================================================================================\n");
        printf("%-10s|%-20s|%-11s|%-30s|%-20s|%-20s|%-8s\n", "Staff ID", "Staff Name", "BirthOfDate", "Staff Position", "Department", "Contact Number", "Salary");
        printf("==============================================================================================================================\n");

        printf("%-10s|%-20s|%02d-%02d-%-05d|%-30s|%-20s|%-20s|%-8.2lf\n", staff[index].staffId, staff[index].name,
            staff[index].birthDate.day, staff[index].birthDate.month, staff[index].birthDate.year, staff[index].position,
            staff[index].department, staff[index].contactNumber, staff[index].salary);
    }

    printf("Confirm to delete this record?(Y-Yes):");
    rewind(stdin);
    confirmDelete = tolower(getchar());
    if (confirmDelete == 'y') {
        for (int i = 0; i < nSta + 1; i++) {
            if (strcmp(staff[i].staffId, searchId) == 0) {
                while (i < nSta + 1) {
                    staff[i] = staff[i + 1];
                    i++;
                }
                break;
            }

        }
        printf("Record successfully deleted ^.^\n");
        nSta = nSta - 1;
        writeIntoFile(staff, nSta);
        displayAllStaff();
    }
    else {
        printf("Invalid Input.Please try again.");
    }

    system("pause");
}


/* MEMBER INFORMATION MODULE */

void memberMain() {
    Member m;
    int ttlRecruit = 0;
    char id = "";
    int selection, newQty = 0, dropQty = 0, oldTtl = 0;
    FILE* fptr = fopen(MEMBER_FILENAME, "rb");
    while ((fread(&m, sizeof(Member), 1, fptr)) != 0) {
        oldTtl++;
    }
    fclose(fptr);

    do {
        printf("\n\n1.Add member.\n");
        printf("2.Dislay member.\n");
        printf("3.Edit member.\n");
        printf("4.Delete member.\n");
        printf("5.Search member.\n");
        printf("6.Summary report.\n");
        printf("7.Exit\n");
        printf("Enter your selection:");

        //Validation
        if (scanf("%d", &selection) != 1) {
            printf("Invalid input. Please enter a number.\n");
            selection = 0;
            rewind(stdin); // clear input buffer
        }
        else if (selection < 1 || selection > 7) {
            selection = 0;
        }

        switch (selection) {
        case 1:
            addMember(&newQty);//get new member qty
            break;
        case 2:
            displayMember();
            break;
        case 3:
            editMember(); break;
        case 4:
            deleteMember(&dropQty);//get dropped member qty
            break;
        case 5:
            searchMember(); break; // get the total recruitment of the member
        case 6:
            summaryReport(newQty, dropQty, oldTtl); break;
        case 7:
            system("cls");
            mainMenu();
            break;
        default:
            printf("Please enter a valid number(1-6).Thankyou.");
            break;
        }
    } while (selection != 7);
    return 0;
}

int validateInput(int field, char id[8], char fname[20], char lname[20], char gender, char ic[14], char phoneNo[14], char email[31], int no, int postCode) {
    Member member;

    int valid_input = 1;
    int count = 0;

    switch (field) {
    case 1: //Validation for member id
    {
        FILE* rptr = fopen(MEMBER_FILENAME, "rb");
        if (rptr == NULL) {
            printf("Not such file!\n");
            exit(-1);
        }
        while (fread(&member, sizeof(Member), 1, rptr) != 0) {
            if (strcmp(id, member.memberId) == 0) // if data same,return false 
            {
                valid_input = 0;
                printf("This member already exist!\n\n");
                break;
            }
            for (int i = 0; id[i] != '\0'; i++) {
                if (!isdigit(id[i])) {
                    valid_input = 0;
                    break;
                }
            }

            if (strlen(id) != 7) {
                valid_input = 0;
                printf("Invalid id size provided!\n\n");
                break;
            }
        }
        fclose(rptr);


        if (valid_input == 0) {
            printf("Please reenter 7 digit numeric id.\n\n");
        }
        break;
    }
    case 2://Validation for member name
    {
        for (int i = 0; fname[i] != '\0'; i++) {
            if (!isalpha(fname[i]) && !isspace(fname[i])) {
                valid_input = 0;
                break;
            }
        }
        for (int i = 0; lname[i] != '\0'; i++) {
            if (!isalpha(lname[i]) && !isspace(lname[i])) {
                valid_input = 0;
                break;
            }
        }
        if (valid_input == 0) {
            printf("Invalid input!Please reenter.\n\n");
        }
        break;
    }
    case 3://Validation for gender
    {
        if (gender != 'M' && gender != 'F') {
            valid_input = 0;
            printf("Invalid input. Please reenter.(M-male,F-female)\n\n");
        }
        break;
    }
    case 4://Validation for ic number
    {
        for (int i = 0; ic[i]; i++) {
            if (!isdigit(ic[i])) {
                valid_input = 0;
                break;
            }
        }

        if (strlen(ic) != 12) {
            valid_input = 0;
            printf("Invalid ic size provided! Please reenter 12 digit valid ic number.\n\n");
            break;
        }
        break;
    }
    case 5://Validation for phone number
    {
        for (int i = 0; phoneNo[i]; i++) {
            if (!isdigit(phoneNo[i])) {
                valid_input = 0;
                break;
            }
        }
        if (strlen(phoneNo) != 10 && (strlen(phoneNo) != 11)) {
            valid_input = 0;
            printf("Invalid phone number size provided! Please reenter.\n\n");
            break;
        }
        break;
    }
    case 6://Validation for upline id
    {
        for (int i = 0; id[i]; i++) {
            if (!isdigit(id[i]) && (id[i] != '-')) {
                valid_input = 0;
                break;
            }
        }
        if ((strlen(id) != 7) && (strlen(id) != 1)) {
            valid_input = 0;
            printf("Invalid id size provided!\n\n");
            break;
        }
        if (valid_input == 0) {
            printf("Please reenter 7 digit numeric id.\n\n");
        }
        break;
    }
    case 7://Validation for email address
    {
        int found = 0;
        for (int i = 0; email[i]; i++) {
            if (email[i] == '@') {
                found = 1;
                break;
            }
        }
        if (!found) {
            valid_input = 0;
            printf("Invalid input!Please reenter email in correct format.\n\n");
        }
        break;
    }

    case 8://Validation for address
    {
        int count = 0;
        do {
            postCode /= 10;
            ++count;
        } while (postCode != 0);
        if (count != 5) {
            valid_input = 0;
            printf("Invalid post code size provided!\n");
        }

        if (valid_input == 0) {
            printf("Please re-enter the address in the correct format.\n\n");
        }
        break;
    }
    default:
        break;
    }
    return valid_input;
}

int addMember(int* nQty) {
    Member m = { 0 };
    FILE* aptr = fopen(MEMBER_FILENAME, "ab");
    if (aptr == NULL) {
        printf("Invalid file!\n");
        return -1;
    }
    char continueAdd;
    int newQty = 0;
    int valid_input = 0;
    int field;
    do {
        while (valid_input == 0)
        {
            printf("Enter new member id: ");
            rewind(stdin); gets(m.memberId);
            field = 1;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        valid_input = 0;
        while (valid_input == 0)
        {
            printf("Member name> ");
            printf("\nEnter first name:");
            rewind(stdin); gets(m.name.fname);
            printf("Enter last name:");
            rewind(stdin); gets(m.name.lname);
            field = 2;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        valid_input = 0;
        while (valid_input == 0) {
            printf("Enter member gender(M/F):");
            rewind(stdin);
            m.gender = toupper(getchar());
            field = 3;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        valid_input = 0;
        while (valid_input == 0) {
            printf("Enter member IC number:");
            rewind(stdin); gets(m.iC);
            field = 4;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        valid_input = 0;
        while (valid_input == 0) {
            printf("Enter member phone number:");
            rewind(stdin); gets(m.phoneNo);
            field = 5;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        valid_input = 0;
        while (valid_input == 0) {
            printf("Enter member upline ID:");
            rewind(stdin); gets(m.upLineId);
            field = 6;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        valid_input = 0;
        while (valid_input == 0) {
            printf("Enter member email:");
            rewind(stdin); gets(m.email);
            field = 7;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        valid_input = 0;
        while (valid_input == 0) {
            printf("Member home address >\n");
            printf("Enter house number:");
            rewind(stdin); scanf("%d", &m.add.no);
            printf("Enter street name:");
            rewind(stdin); gets(m.add.street);
            printf("Enter postal code:");
            rewind(stdin); scanf("%d", &m.add.postCode);
            printf("Enter state:");
            rewind(stdin); gets(m.add.state);
            field = 8;
            valid_input = validateInput(field, m.memberId, m.name.fname, m.name.lname, m.gender, m.iC, m.phoneNo, m.email, m.add.no, m.add.postCode);
        }

        fwrite(&m, sizeof(Member), 1, aptr);
        printf("New member added...\n");
        newQty++;
        printf("Number of added members: %d\n", newQty);

        printf("Continue add (Y/N) ? ");
        continueAdd = toupper(getchar());

    } while (continueAdd == 'Y');
    *nQty = newQty;
    fclose(aptr);
    return 0;
}

void displayMember() {
    FILE* dptr = fopen(MEMBER_FILENAME, "rb");
    if (dptr == NULL) {
        printf("Invalid file!\n");
        return -1;
    }

    int noMember = 0;
    Member m;
    printf("\n\n");
    printf("***********************************************************************************************************************\n");
    printf("|%s|%-7s|%-20s|%-4s|%-13s|%-12s|%-7s|%-20s|%-24s|\n", "No", "ID", "Name", "M/F", "Ic.No", "Tel.No", "Upline", "Email address", "Home Address");
    printf("***********************************************************************************************************************\n");

    while (fread(&m, sizeof(Member), 1, dptr) != 0) {
        noMember++;
        printf("|%-2d|%-7s|%-20s|%-4c|%-13s|%-12s|%-7s|%-20s|%-5d, %-17s|\n", noMember, m.memberId, m.name.fname, m.gender, m.iC, m.phoneNo, m.upLineId, m.email, m.add.no, m.add.street);
        printf("|%-2s|%-7s|%-20s|%-4s|%-13s|%-12s|%-7s|%-20s|%-5d, %-17s|\n", " ", " ", m.name.lname, " ", " ", " ", " ", " ", m.add.postCode, m.add.state);
        printf("***********************************************************************************************************************\n");
    }
    printf("Total number of member: %d\n\n", noMember);

    fclose(dptr);
}

void editMember() {
    static Member m[MAX_MEMBER_SIZE];
    int count = 0;
    char id[8];
    char editField;
    char email[31], phoneNo[14], street[15], state[15];
    int number, postcode;
    char confirmModify, continueEdit;
    int found = 0;
    int valid_input = 0, field = 0;

    //Read binary file data into array
    FILE* rptr = fopen(MEMBER_FILENAME, "rb");
    if (rptr == NULL) {
        printf("Not such file!\n");
        exit(-1);
    }

    while (fread(&m[count], sizeof(m[count]), 1, rptr)) {
        count++;
    }
    fclose(rptr);

    //Prompt user for member id to edit
    while (valid_input == 0) {
        printf("\nEnter member Id:");
        rewind(stdin);
        gets(id);
        field = 6;
        valid_input = validateInput(field, id, name.fname, name.lname, m[MAX_MEMBER_SIZE].gender, m[MAX_MEMBER_SIZE].iC, m[MAX_MEMBER_SIZE].phoneNo, m[MAX_MEMBER_SIZE].email, add.no, add.postCode);
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(id, m[i].memberId) == 0) {
            do {
                printf("Phone number -> %s\n", m[i].phoneNo);
                printf("Email -> %s\n", m[i].email);
                printf("Address -> %d, %s, %d, %s\n", m[i].add.no, m[i].add.street, m[i].add.postCode, m[i].add.state);
                rewind(stdin);
                printf("Which data do you want to modify?(P-phone no, E-email, A-address):");
                editField = toupper(getchar());
                found = 1;

                switch (editField) {
                case 'P':
                    printf("Enter the new contact number: ");
                    scanf("%s", phoneNo);
                    printf("Sure to modify (Y/N)? ");
                    rewind(stdin);
                    confirmModify = toupper(getchar());
                    if (confirmModify == 'Y') {
                        strcpy(m[i].phoneNo, phoneNo);
                        printf("\nEdit successfully...\n\n");
                    }
                    break;

                case 'E':
                    printf("Enter the new email address: ");
                    scanf("%s", email);
                    printf("Sure to modify (Y/N)? ");
                    rewind(stdin);
                    confirmModify = toupper(getchar());
                    if (confirmModify == 'Y') {
                        strcpy(m[i].email, email);
                        printf("\nEdit successfully...\n\n");
                    }
                    break;

                case 'A':
                    printf("Enter the new address(no,street,postcode,state): ");
                    scanf("%d,%[^,],%d,%[^\n]", &number, street, &postcode, state);
                    printf("Sure to modify (Y/N)? ");
                    rewind(stdin);
                    confirmModify = toupper(getchar());
                    if (confirmModify == 'Y') {
                        m[i].add.no = number;
                        strcpy(m[i].add.street, street);
                        m[i].add.postCode = postcode;
                        strcpy(m[i].add.state, state);
                        printf("\nEdit successfully...\n\n");
                    }
                    break;

                default:
                    printf("Invalid entry.Please reenter...\n");
                }
                printf("Continue edit member %s?\n", id);
                rewind(stdin);
                continueEdit = toupper(getchar());
            } while (continueEdit == 'Y');

            //Write new data into binary file
            FILE* wptr = fopen(MEMBER_FILENAME, "wb");
            if (wptr == NULL) {
                printf("Not such file!\n");
                exit(-1);
            }
            fwrite(&m, sizeof(Member), count, wptr);
            fclose(wptr);
        }
    }
    if (!found)
    {
        printf("No records found for the requested member id: %s", id);
    }
}

int deleteMember(int* dQty) {
    FILE* fp;
    FILE* fp_tmp;
    int found = 0;
    Member record = { 0 };
    fp = fopen(MEMBER_FILENAME, "rb");
    if (!fp) {
        printf("Unable to open file.\n");
        return -1;
    }
    fp_tmp = fopen(MEMBER_SECOND_FILENAME, "wb");
    if (!fp_tmp) {
        printf("Unable to open file temp file.\n");
        return -1;
    }

    char id[8] = { 0 };
    char confirmDel;
    int dropQty = 0;
    int field = 0, valid_input = 0;
    //Validate member id
    while (valid_input == 0) {
        printf("\nEnter member Id:");
        rewind(stdin);
        gets(id);
        field = 6;
        valid_input = validateInput(field, id, record.name.fname, record.name.lname, record.gender, record.iC, record.phoneNo, record.email, record.add.no, record.add.postCode);
    }

    rewind(fp);
    while (fread(&record, sizeof(Member), 1, fp) != 0) {
        if (strcmp(id, record.memberId) == 0) {
            found = 1;
            printf("\n\n");
            printf("********************************************************************************************************************\n");
            printf("|%-7s|%-20s|%-4s|%-13s|%-12s|%-7s|%-20s|%-24s|\n", "ID", "Name", "M/F", "Ic.No", "Tel.No", "Upline", "Email address", "Home Address");
            printf("********************************************************************************************************************\n");
            printf("|%-7s|%-20s|%-4c|%-13s|%-12s|%-7s|%-20s|%-5d, %-17s|\n", record.memberId, record.name.fname, record.gender, record.iC, record.phoneNo, record.upLineId, record.email, record.add.no, record.add.street);
            printf("|%-7s|%-20s|%-4s|%-13s|%-12s|%-7s|%-20s|%-5d, %-17s|\n", " ", record.name.lname, " ", " ", " ", " ", " ", record.add.postCode, record.add.state);
            printf("********************************************************************************************************************\n");
            printf("Confirm to delete account?(Y/N)->");
            confirmDel = toupper(getchar());
            if (confirmDel == 'Y') {
                printf("A record with requested id found and deleted.\n\n");
                dropQty++;
            }
            else {
                fwrite(&record, sizeof(Member), 1, fp_tmp);
                printf("Deletion requirement unsuccesfully");
            }
        }
        else {
            fwrite(&record, sizeof(Member), 1, fp_tmp);
        }
    }

    if (!found) {
        printf("No record(s) found with the requested id: %s\n\n", id);
    }

    fclose(fp);
    fclose(fp_tmp);
    remove(MEMBER_FILENAME);
    rename(MEMBER_SECOND_FILENAME, MEMBER_FILENAME);
    *dQty += dropQty;
    return 0;
}

void searchMember() {
    FILE* sptr;
    Member record = { 0 };
    int found = 0;
    char id[8] = "";
    int total = 0;
    int field = 0, valid_input = 0;
    /*open binary file in read mode */
    sptr = fopen(MEMBER_FILENAME, "rb");
    if (!sptr)
    {
        printf("File could not open");
        exit(-1);
    }
    //Validate id
    while (valid_input == 0) {
        printf("\nEnter member Id:");
        rewind(stdin);
        gets(id);
        field = 6;
        valid_input = validateInput(field, id, record.name.fname, record.name.lname, record.gender, record.iC, record.phoneNo, record.email, record.add.no, record.add.postCode);
    }

    while ((fread(&record, sizeof(Member), 1, sptr) != 0))
    {
        if (strcmp(record.memberId, id) == 0)
        {
            found = 1;
            printf("\nRecord of Member With Id %s is as follows:", id);
            printf("\n\n");
            printf("**********************************************************************************************************************\n");
            printf("|%-7s|%-20s|%-4s|%-13s|%-12s|%-7s|%-20s|%-26s|\n", "ID", "Name", "M/F", "Ic.No", "Tel.No", "Upline", "Email address", "Home Address");
            printf("**********************************************************************************************************************\n");
            printf("|%-7s|%-20s|%-4c|%-13s|%-12s|%-7s|%-20s|%-5d, %-19s|\n", record.memberId, record.name.fname, record.gender, record.iC, record.phoneNo, record.upLineId, record.email, record.add.no, record.add.street);
            printf("|%-7s|%-20s|%-4s|%-13s|%-12s|%-7s|%-20s|%-5d, %-19s|\n", " ", record.name.lname, " ", " ", " ", " ", " ", record.add.postCode, record.add.state);
            printf("**********************************************************************************************************************\n");
            break;
        }
    }
    if (!found)
    {
        printf("No records found for the requested member id: %s", id);
    }
    else
    {
        rewind(sptr);
        while ((fread(&record, sizeof(Member), 1, sptr) != 0))
        {
            if (strcmp(id, record.upLineId) == 0)
            {
                total++;
            }
        }
        printf("Total recruitment of the member %s: %d", id, total);//return id and ttl and calculate comm
    }
    fclose(sptr);
}

void summaryReport(int nQty, int dQty, int oldTtl) {
    // Declare an array of Member structs
    Member m[MAX_MEMBER_SIZE];
    SalesOrder order[MAX_SALES_SIZE];
    // Initialize a counter variable
    int nMember = 0;
    int nOrder = 0, ttlRecruit = 0;
    double ttlOrder = 0;
    char id[8] = " ";
    // Open the binary file for reading
    FILE* fptr = fopen(MEMBER_FILENAME, "rb");
    // Check if the file was successfully opened
    if (fptr == NULL) {
        printf("File not found!\n");
        exit(-1);
    }

    // Read each Member struct from the file and store it in the array
    while (fread(&m[nMember], sizeof(m[nMember]), 1, fptr)) {
        nMember++;
    }
    fclose(fptr);

    // Calculate the number of new members, dropped members, and current total members
    int newCount = nQty;
    int droppedCount = dQty;
    int currentTotal = nMember;

    readOrder(&order, &nOrder);
    printf("\n\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Summary report ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("| %78s|", "");
    for (int j = 0; j < nMember; j++) {
        strcpy(id, m[j].memberId);
        printf("\n|\t----------------------------------------------------------------\t|");
        printf("\n|\t| %-25s %-10s%25s|\t|\n", "Member ID: ", id, " ");
        ttlRecruit = 0;
        for (int k = 0; k < nMember; k++) {
            if (strcmp(m[k].upLineId, id) == 0) {
                ttlRecruit++;
            }
        }
        printf("|\t----------------------------------------------------------------\t|");
        printf("\n|\t| %-25s %-10d%25s|\t|", "Total recruitment :", ttlRecruit, "");
        for (int i = 0; i < nOrder; i++) {
            if (strcmp(order[i].memberId, id) == 0) {
                ttlOrder = (order[i].item.qtyOrder * order[i].item.unitPrice);
                printf("\n|\t| %-25s %-10.2f%25s|\t|", "Total price of order:", ttlOrder, "");
            }
        }
    }
    printf("\n|\t----------------------------------------------------------------\t|");
    // Calculate the percentage of new members and dropped members compared to the previous day
    float percentNewQty = ((float)newCount / (float)oldTtl) * 100;
    float percentDroppedQty = ((float)droppedCount / (float)oldTtl) * 100;
    // Get the current date and time
    time_t now;
    time(&now);

    // Print the summary report
    printf("\n| %78s|\n", "");
    printf("|\t%-35s %3d -> increase %6.2f%% of members  |\n", "Total of new member(s) today:", newCount, percentNewQty);
    printf("| %78s|\n", "");
    printf("|\t%-35s %3d -> decrease %6.2f%% of members  |\n", "Total of dropped member(s) today:", droppedCount, percentDroppedQty);
    printf("| %78s|\n", "");
    printf("|\t%-35s %3d %32s|\n", "Total of members:", currentTotal, "");
    printf("| %78s|\n", "");
    printf("|\t%-35s %3d %32s|\n", "New target:", nQty + 5, ""); //target is at least 5 members
    printf("| %78s|\n", "");
    printf("| %78s|\n", "");
    printf("|\tCurrent time is > %s", ctime(&now));
    printf("| %78s|\n", "");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}


/* SALES INFORMATION MODULE */

void salesMain() {
    SalesOrder order = { 0 };
    int nOrder = 0;
    salesMenu(order, nOrder);
}

void readOrder(SalesOrder order[], int* nOrder) {
    FILE* rptr = fopen(SALES_FILENAME, "r");
    if (rptr == NULL) {
        printf("Not such file!\n");
        exit(-1);
    }
    int i = 0;
    while (fscanf(rptr, "%d/%d/%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf|\n", &order[*nOrder].date.day, &order[*nOrder].date.month, &order[*nOrder].date.year, &order[*nOrder].orderId, &order[*nOrder].memberId, &order[*nOrder].item.itemCode, &order[*nOrder].item.name, &order[*nOrder].item.qtyOrder, &order[*nOrder].item.unitPrice) != EOF) {
        i++;
        *nOrder = i;

    }
    fclose(rptr);
}

void printDetail(SalesOrder order) {
    // Display Sales Order Details
    printf("+====================================================================================================+\n");
    printf("|Order No : #%04d                                            Order date    : %02d/%02d/%d              |\n", order.orderId, order.date.day, order.date.month, order.date.year);
    printf("|Member ID: %s %81s|\n", order.memberId, "");
    printf("+----------------------------------------------------------------------------------------------------+\n");
    printf("| %-12s | %-30s | %-20s | %-12s %-15s|\n", "Item Code", "Item Name", "Quantity Ordered", "Unit Price", "");
    printf("+--------------+--------------------------------+----------------------+-----------------------------+\n");
    // Display Order Items
    printf("| %-12s | %-30s | %-20d | %-12.2lf %15s|\n", order.item.itemCode, order.item.name, order.item.qtyOrder, order.item.unitPrice, "");
    order.total = order.item.qtyOrder * order.item.unitPrice;
    printf("+--------------+--------------------------------+----------------------+-----------------------------+\n");
    // Display Total
    printf("| %84s: %12.2lf |\n", "Total", order.total);
    printf("+====================================================================================================+\n\n");
}

int isValidDate(SalesOrder order) {
    if ((order.date.year % 4) == 0) {
        if (order.date.month > 0 && order.date.month <= 12) {
            if (order.date.month == 2) {
                if (order.date.day > 0 && order.date.day <= 29) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else if (order.date.month == 4 || order.date.month == 6 || order.date.month == 9 || order.date.month == 11) {
                if (order.date.day > 0 && order.date.day <= 30) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                if (order.date.day > 0 && order.date.day <= 31) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
        }
        else {
            return 0;
        }
    }
    else if ((order.date.year % 4) != 0) {
        if (order.date.month > 0 && order.date.month <= 12) {
            if (order.date.month == 2) {
                if (order.date.day > 0 && order.date.day <= 28) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else if (order.date.month == 4 || order.date.month == 6 || order.date.month == 9 || order.date.month == 11) {
                if (order.date.day > 0 && order.date.day <= 30) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                if (order.date.day > 0 && order.date.day <= 31) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

void salesMenu(SalesOrder order, int nOrder) {
    int select;
    char validation;
    do {
        printf("*********************************************************\n");
        printf("*                                                       *\n");
        printf("*                    SALES ORDER MENU                   *\n");
        printf("*                                                       *\n");
        printf("*********************************************************\n");
        printf("*                                                       *\n");
        printf("* 1. Display Sales Order                                *\n");
        printf("* 2. Search Sales Order                                 *\n");
        printf("* 3. Add Sales Order                                    *\n");
        printf("* 4. Calculate Commission of Upline                     *\n");
        printf("* 5. Exit                                               *\n");
        printf("*                                                       *\n");
        printf("*********************************************************\n");
        do {
            printf("\nEnter your selection:");
            rewind(stdin);
            scanf("%d%c", &select, &validation);
        } while (validation != '\n' || select <= 0);

        printf("\n\n");

        switch (select)
        {
        case 1:
            displayOrder(order);
            break;
        case 2:
            searchOrder(order, nOrder);
            break;
        case 3:
            addOrder(order, nOrder);
            break;
        case 4:
            comUpLine(nOrder);
            break;
        case 5:
            system("cls");
            mainMenu();
            break;
        default:
            break;
        }
    } while (select != 5);
}

void displayOrder(SalesOrder order) {
    system("cls");

    FILE* fptr = fopen(SALES_FILENAME, "r");
    if (fptr == NULL) {
        printf("Unable to open file\n");
        return;
    }

    printf("\n\n");
    printf("+-----------------------------+\n");
    printf("|      SALES ORDER DETAILS    |\n");
    printf("+-----------------------------+\n\n");
    //read data from file
    while (fscanf(fptr, "%d/%d/%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf|\n", &order.date.day, &order.date.month, &order.date.year, &order.orderId, &order.memberId, &order.item.itemCode, &order.item.name, &order.item.qtyOrder, &order.item.unitPrice) != EOF) {
        order.total = 0.0;
        order.total = order.item.qtyOrder * order.item.unitPrice;
        //Display Sales order details
        printDetail(order);
        printf("\n\n");
    }

    fclose(fptr);
}

void searchOrder(SalesOrder order, int nOrder) {
    int orderId, choice;

    printf("\nEnter Order ID to search for: ");
    scanf("%d", &orderId);

    // Validate order ID length
    while (orderId < 0 || orderId > 9999) {
        printf("Error: Invalid Sales Order Id.\n");
        printf("Sales Order Id:");
        scanf("%d", &orderId);
    }

    FILE* fptr = fopen(SALES_FILENAME, "r");
    if (fptr == NULL) {
        printf("File not found.\n");
        return;
    }

    int found = 0;
    while (fscanf(fptr, "%d/%d/%d|%d|%[^|]|%[^|]|%[^|]|%d|%lf|\n", &order.date.day, &order.date.month, &order.date.year, &order.orderId, &order.memberId, &order.item.itemCode, &order.item.name, &order.item.qtyOrder, &order.item.unitPrice) != EOF) {
        if (order.orderId == orderId) {
            found = 1;
            order.total = 0.0;
            // Display Sales Order Details
            printDetail(order);
            printf("\n\n");

            do {
                printf("\nSelect an action: \n");
                printf("1. Modify\n");
                printf("2. Delete\n");
                printf("3. Back\n");
                printf("Enter your choice : ");
                do {
                    rewind(stdin);
                    scanf("%d", &choice);

                    if (choice == 1) {
                        modifyOrder(orderId, nOrder);
                    }
                    else if (choice == 2) {
                        deleteSalesOrder(orderId, nOrder);
                        break;
                    }
                    else if (choice == 3) {
                        break;
                    }
                    else {
                        printf("Invalid input. Enter it again : ");
                    }
                } while (choice < 1 || choice > 4);

                if (choice == 2)
                    break;
            } while (choice != 3);
            break;
        }

    }
    if (!found) {
        printf("\nOrder not found.\n");
    }

    fclose(fptr);
}

void modifyOrder(int orderId, int nOrder) {
    SalesOrder order[MAX_SALES_SIZE];
    char confirmModify;
    char mItemCode[6] = { '\0' };
    char mItemName[20] = { '\0' };
    int mItemQty = 0;
    double mUnitPrice = 0.0;
    int valid_input = 0, found = 0;
    //read data from text file
    readOrder(order, &nOrder);
    for (int i = 0; i < nOrder; i++) {
        if (orderId == order[i].orderId) {
            //Validation 
            found = 1;
            do {
                printf("\nItem Code(Eg:VC002):");
                rewind(stdin);
                gets(mItemCode);
                if (strlen(mItemCode) == 5 && isalpha(mItemCode[0]) && isalpha(mItemCode[1]) && isdigit(mItemCode[2]) && isdigit(mItemCode[3]) && isdigit(mItemCode[4])) {
                    valid_input = 1;
                }
                else
                {
                    printf("Invalid input!Please reenter item code in correct format.\n");
                }
            } while (valid_input == 0);
            valid_input = 1;
            do {
                printf("\nItem Name:");
                rewind(stdin);
                gets(mItemName);
                for (int i = 0; mItemName[i] != '\0'; i++) {
                    if (!isalpha(mItemName[i]) && !isspace(mItemName[i])) {
                        valid_input = 0;
                        break;
                    }

                }
                if (valid_input == 0) {
                    printf("Invalid input!Please reenter.\n");
                    break;
                }
            } while (valid_input == 0);
            valid_input = 0;
            do {
                printf("\nItem Quantity:");
                rewind(stdin);
                scanf("%d", &mItemQty);
                if (mItemQty > 0) {
                    valid_input = 1;
                }
                else
                    printf("Invalid input!Please reenter.\n\n");
            } while (valid_input == 0);
            valid_input = 0;
            do {
                printf("\nUnit Price:");
                scanf("%lf", &mUnitPrice);
                printf("\n");
                if (mUnitPrice > 0) {
                    valid_input = 1;
                }
                else
                    printf("Invalid input!Please reenter\n\n");
            } while (valid_input == 0);

            do {
                printf("confirm modify(y/n)?");
                rewind(stdin);
                confirmModify = tolower(getchar());
            } while (confirmModify != 'y' && confirmModify != 'n');

            if (confirmModify == 'y') {
                strcpy(order[i].item.itemCode, mItemCode);
                strcpy(order[i].item.name, mItemName);
                order[i].item.qtyOrder = mItemQty;
                order[i].item.unitPrice = mUnitPrice;
                //print all the sales order details
                printDetail(order[i]);
            }
        }

    }
    if (!found)
        printf("The order already exist.Please reenter a new order id.\n\n");

    FILE* wptr = fopen(SALES_FILENAME, "w");
    if (wptr == NULL) {
        printf("Not such file!\n");
        exit(-1);
    }
    for (int i = 0; i < nOrder; i++) {
        //write into text file
        fprintf(wptr, "%02d/%02d/%d|%04d|%s", order[i].date.day, order[i].date.month, order[i].date.year, order[i].orderId, order[i].memberId);
        fprintf(wptr, "|%s|%s|%d|%.2lf|\n", order[i].item.itemCode, order[i].item.name, order[i].item.qtyOrder, order[i].item.unitPrice);
    }
    fclose(wptr);

}

void addOrder(SalesOrder order, int nOrder) {
    FILE* fptr = fopen(SALES_FILENAME, "a");
    if (fptr == NULL) {
        printf("Unable to open file");
        return;
    }
    char yesNo;
    int isvalidOrderId = 0;
    printf("+------------------------------------------+\n");
    printf("|           Add Sales Order Details        |\n");
    printf("+------------------------------------------+\n");

    do {
        printf("\nEnter order date(dd/mm/yyyy):");
        scanf("%02d/%02d/%4d", &order.date.day, &order.date.month, &order.date.year);
        //validate day,month,year
        while (isValidDate(order) == 0) {
            printf("Invalid date.\n");
            printf("Enter order date(dd/mm/yyyy):");
            scanf("%02d/%02d/%4d", &order.date.day, &order.date.month, &order.date.year);
        }
        //Add new sales order id
        while (isvalidOrderId == 0) {
            printf("\nSales Order Id:");
            scanf("%d", &order.orderId);
            //valid order id
            isvalidOrderId = validOrderId(order.orderId, nOrder);
        }

        //Add new order details
        printf("\nMember Id:");
        rewind(stdin);
        scanf("%s", order.memberId);
        order.total = 0;
        fprintf(fptr, "%02d/%02d/%d|%04d|%s", order.date.day, order.date.month, order.date.year, order.orderId, order.memberId);
        printf("\nItem Code:");
        rewind(stdin);
        scanf("%s", order.item.itemCode);
        printf("\nItem Name:");
        rewind(stdin);
        gets(order.item.name);
        rewind(stdin);
        printf("\nItem Quantity:");
        scanf("%d", &order.item.qtyOrder);
        printf("\nUnit Price:");
        scanf("%lf", &order.item.unitPrice);
        printf("\n");
        order.total = order.item.qtyOrder * order.item.unitPrice;
        fprintf(fptr, "|%s|%s|%d|%.2lf|", order.item.itemCode, order.item.name, order.item.qtyOrder, order.item.unitPrice);
        fprintf(fptr, "\n");
        printf("The order is added successfully.\n");
        updateQtyInStock(order.item.itemCode, order.item.qtyOrder);
        printf("\n\nAdd another record(y/n)? :");
        rewind(stdin);
        yesNo = tolower(getchar());
        //validate the input
        while (yesNo != 'y' && yesNo != 'n') {
            printf("Invalid input.Please enter again.");
            rewind(stdin);
            yesNo = tolower(getchar());
        }
    } while (yesNo == 'y');
    if (yesNo == 'n') {
        printf("No order is added\n");
    }
    fclose(fptr);
}

void deleteSalesOrder(int orderId, int nOrder) {
    SalesOrder order[MAX_SALES_SIZE];
    //read order details from text file
    readOrder(order, &nOrder);
    int index = -1;;
    for (int i = 0; i < nOrder; i++) {
        if (orderId == order[i].orderId) {
            //print all the sales order details
            printDetail(order[i]);
            index = i;
            break;
        }
    }
    //if the id is not existed
    if (index == -1) {
        printf("Order with ID %04d not found.\n", orderId);
        return;
    }
    char yesno;

    do {
        printf("Confirm to delete? (Y/N): ");
        rewind(stdin);
        yesno = toupper(getchar());
        switch (yesno) {
        case 'Y':
            //delete order from array of structure
            nOrder--;
            for (int i = index; i < nOrder; i++) {
                order[i] = order[i + 1];
            }
            FILE* fp = fopen(SALES_FILENAME, "w");
            if (fp == NULL) {
                printf("ERROR: Could not open sales file.\n");
                exit(-1);
            }

            for (int i = 0; i < nOrder; i++) {
                fprintf(fp, "%02d/%02d/%d|%04d|%s|%s|%s|%d|%.2lf|\n", order[i].date.day, order[i].date.month, order[i].date.year, order[i].orderId, order[i].memberId, order[i].item.itemCode, order[i].item.name, order[i].item.qtyOrder, order[i].item.unitPrice);
                //print all the sales order details
                printDetail(order[i]);
            }

            fclose(fp);
            printf("Order with Id %04d has been successfully deleted.\n", orderId);
            return;
        case 'N':
            printf("The order is not deleted successfully\n");
            return;
        default:
            printf("Incorrect input. Pls reenter.(y/n)\n");
            break;
        }

    } while (yesno != 'Y' && yesno != 'N');

}

int validOrderId(int id, int nOrder) {
    SalesOrder order[MAX_SALES_SIZE];
    //read sales order details
    readOrder(order, &nOrder);
    int isvalidOrderId = 1;
    int numDigits = 0;
    int temp = id;
    while (temp != 0) {
        numDigits++;
        temp /= 10; //temp=temp/10
    }
    if (numDigits != 4) {
        isvalidOrderId = 0;
        printf("Error: The order id must be 4 digits long.\n");
    }
    else {
        //validate the order id with the existed order id(the id must not same as other order id)
        for (int i = 0; i < nOrder; i++) {
            if (id == order[i].orderId) {
                printf("Error: The order id already exists.\n\n");
                isvalidOrderId = 0;
                break;
            }
        }
    }
    return isvalidOrderId;
}



void comUpLine(int nOrder) {
    FILE* mptr = fopen(MEMBER_FILENAME, "rb");
    if (mptr == NULL) {
        printf("Error.File not found\n");
        return;
    }
    static Member m[MAX_MEMBER_SIZE];
    SalesOrder order[MAX_SALES_SIZE];
    char member[8] = { '\0' };
    char uplineID[8];
    int nUpline = 0;
    double total = 0;
    int i = 0;
    int count = 0;
    while (fread(&m[i], sizeof(Member), 1, mptr) != 0) {
        nUpline++;
        i++;
    }
    printf("Enter upline Id:");
    scanf("%s", uplineID);
    //read sales sales order details
    readOrder(order, &nOrder);
    double com, ttlCom = 0;

    for (int i = 0; i < nUpline; i++) {
        if (!strcmp(uplineID, m[i].upLineId)) {//compare upline id from the binary file
            printf("\n|---------------|---------------|");
            printf("\n|%14s |%14s |", "Recruit", "Commission");
            printf("\n|---------------|---------------|");
            strcpy(member, m[i].memberId);//take the member id that the upline recruited
            for (int i = 0; i < nOrder; i++) {
                if (!strcmp(order[i].memberId, member)) {
                    total += (order[i].item.qtyOrder * order[i].item.unitPrice);
                    com = total * 0.05;
                    printf("\n|%14s |%14.2f |", order[i].memberId, com);
                    ttlCom += com;
                    count++;
                }
            }
            printf("\n|---------------|---------------|");
        }
    }

    if (count > 0) {
        printf("\n\nThe member has recruit %d member.\n\n", count);
        printf("Total commission=%.2f\n\n", ttlCom);
    }
    else if (count == 0) {
        printf("\n\nThis member is not an upline.\n\n");
    }
    fclose(mptr);
}


/* STOCK INFORMATION MODULE */

void stockMain() {
    static Stock stockItem[MAX_STOCK_SIZE];
    stockMenu(stockItem);
}

void stockMenu(Stock stockItem[]) {
    int selection;
    do {
        printf("\n");
        printf("+=================================================+\n");
        printf("|                   Stock Menu                    |\n");
        printf("+=================================================+\n");
        printf("| 1. New Stock Item                               |\n");
        printf("| 2. Display Stock Details                        |\n");
        printf("| 3. Search Stock Item                            |\n");
        printf("| 4. Modify Stock Item                            |\n");
        printf("| 5. Delete Stock Item                            |\n");
        printf("| 6. Generate Stock Daily Report                  |\n");
        printf("| 7. Back to Main Menu                            |\n");
        printf("+-------------------------------------------------+\n");

        printf("\nEnter selection > ");
        scanf("%d", &selection);

        switch (selection) {
        case 1:
            system("cls");
            addStock();	//add new stock
            break;
        case 2:
            system("cls");
            displayStock(); //display all stock details and choose to view supplier details
            break;
        case 3:
            system("cls");
            searchStock(stockItem); //search stock item code to view specific item
            break;
        case 4:
            system("cls");
            modifyStock(stockItem); //modify specific stock item by searching item code
            break;
        case 5:
            system("cls");
            deleteStock(stockItem); //delete stock item by searching item code
            break;
        case 6:
            system("cls");
            stockReport();  // display stock daily report
            break;
        case 7:
            system("cls");
            mainMenu();
            break;		//exit stock information module
        default:
            printf("Invalid option.\n");
        }
    } while (selection != 7);
}

void addStock() {
    system("cls");	//clear screen

    //variable declaration
    Stock stock = { 0 };
    char continueAdd, confirmAdd;
    int countAdd = 0, validate = 0;

    FILE* fptr = fopen(STOCK_FILENAME, "ab");		//open stock file to read data

    /*Display Header*/
    printf("\n\n");
    printf("+------------------------+\n");
    printf("|     ADD STOCK ITEM     |\n");
    printf("+------------------------+\n\n");

    do {
        printf("\nStock Item Details\n");
        printf("==========================\n");
        //validation for item code
        validate = 0;
        while (validate == 0) {
            printf("Item Code (Eg. VC001) > ");
            rewind(stdin);
            gets(stock.itemCode);
            validate = validateItemCode(stock.itemCode);
        }
        while ((strlen(stock.itemCode) != 5) ||!isalpha(stock.itemCode[0]) ||!isalpha(stock.itemCode[1]) ||!isdigit(stock.itemCode[2]) ||!isdigit(stock.itemCode[3]) ||!isdigit(stock.itemCode[4]))
        {
            printf("Error: Invalid Stock Item Code.\n");
            printf("Please Enter Item Code Again (Eg. VC0001) > ");
            rewind(stdin);
            gets(stock.itemCode);
        }

        printf("Item Name > ");
        rewind(stdin);
        gets(stock.itemName);

        printf("Item Description > ");
        rewind(stdin);
        gets(stock.itemDesc);

        printf("Item Cost (RM) > ");
        scanf("%lf", &stock.cost);

        // cost validation
        while (stock.cost <= 0) {
            printf("Error: Invalid cost. Please Reenter.\n");
            printf("Item Cost (RM) > ");
            scanf("%lf", &stock.cost);
        }

        printf("Stock Quantity > ");
        scanf("%d", &stock.qtyInStock);

        // validation for quantity in stock
        while (stock.qtyInStock < 0) {
            printf("Error: Invalid Quantity. Please Reenter.\n");
            printf("Quantity In Stock > ");
            scanf("%d", &stock.qtyInStock);
        }

        printf("Minimum Stock Level > ");
        scanf("%d", &stock.minLvl);

        // min stock lvl validation
        while (stock.minLvl < 0) {
            printf("Error: Invalid minimum level of stock. Please Reenter.\n");
            printf("Minimum Stock Level > ");
            scanf("%d", &stock.minLvl);
        }

        /* Calculation of Reorder Quantity */
        calcReorderQty(stock.qtyInStock, stock.minLvl, &stock.reorderQty);

        printf("\nSupplier Details\n");
        printf("==========================\n");

        printf("Supplier > ");
        rewind(stdin);
        gets(stock.supplier.company);

        printf("Person In Charge > ");
        rewind(stdin);
        gets(stock.supplier.personInCharge);

        printf("Supplier Contact No > ");
        rewind(stdin);
        gets(stock.supplier.contactNo);

        while (((stock.supplier.contactNo[0] != '0') || (stock.supplier.contactNo[1] != '1')) || 
            (strlen(stock.supplier.contactNo) < 10) || (strlen(stock.supplier.contactNo) > 11)) {
            printf("Error: Invalid Contact Number.\n");
            printf("Supplier Contact No (eg. 0108073347) > ");
            rewind(stdin);
            gets(stock.supplier.contactNo);
        }

        printf("Last Restock Date (DD/MM/YYYY) > ");
        scanf("%d/%d/%d", &stock.restockDate.sDay, &stock.restockDate.sMonth, &stock.restockDate.sYear);

        //date validation
        while (stock.restockDate.sDay <= 0 ||
            stock.restockDate.sDay > 31 ||
            stock.restockDate.sMonth <= 0 ||
            stock.restockDate.sMonth > 12 ||
            stock.restockDate.sYear <= 0)
        {
            printf("Error: Invalid Date.\n");
            printf("Last Restock Date (DD/MM/YYYY) > ");
            scanf("%d/%d/%d", &stock.restockDate.sDay, &stock.restockDate.sMonth, &stock.restockDate.sYear);
        }

        printf("Confirm Add Stock? (Y/N) > ");
        rewind(stdin);
        confirmAdd = toupper(getchar());

        while (!isalpha(confirmAdd) || (confirmAdd != 'Y' && confirmAdd != 'N')) {
            printf("Error: Please Enter Y/N (Yes - Y|No - N).\n");
            printf("Confirm Add Stock? (Y/N) > ");
            rewind(stdin);
            continueAdd = toupper(getchar());
        }

        if (confirmAdd == 'Y') {
            fwrite(&stock, sizeof(stock), 1, fptr);		//write the user key in value into the stock file
            printf("Item Add Successfully!\n");
            countAdd++;
        }
        else
            break;
        
        /* Ask user want to continue add stock */
        printf("\n\n");
        printf("Continue Add ? (Y/N) > ");
        rewind(stdin);
        continueAdd = toupper(getchar());

        while (!isalpha(continueAdd) || (continueAdd != 'Y' && continueAdd != 'N')) {
            printf("Error: Please Enter Y/N (Yes - Y|No - N).\n");
            printf("Continue Add ? (Y/N) > ");
            rewind(stdin);
            continueAdd = toupper(getchar());
        }
        printf("\n");
    } while (continueAdd == 'Y');

    printf("%d stock item successfully added.\n", countAdd);

    fclose(fptr);
}

void calcReorderQty(int qtyInStock, int minLvl, int* reorderQty) {
    if (qtyInStock >= minLvl) {
        *reorderQty = 0;
    }
    else {
        *reorderQty = minLvl - qtyInStock;
    }
}

void displayStock() {
    Stock stock;

    FILE* fptr = fopen(STOCK_FILENAME, "rb");
    if (fptr == NULL) {
        printf("File not found.\n");
        exit(-1);
    }

    printf("\n\n++================================================================================================================================================================++\n");
    printf("||                                                                                                                                                                ||\n");
    printf("||                                                                    Stock Details                                                                               ||\n");
    printf("||                                                                                                                                                                ||\n");
    printf("|+============+==============================+===================+============+==========+=================+=================+================+===================+|\n");
    printf("||  Item Code |          Item Name           |     Description   |  Cost (RM) | Quantity | Min Stock Level |   Reorder Qty   |    Supplier    | Last Restock Date ||\n");
    printf("|+------------+------------------------------+-------------------+------------+----------+-----------------+-----------------+----------------+-------------------+|\n");
    while (fread(&stock, sizeof(stock), 1, fptr) != 0) {
        printf("|| %-10s | %-28s | %-17s | %10.2lf | %8d | %15d | %15d | %-14s |     %02d-%02d-%04d    ||\n",
            stock.itemCode, stock.itemName, stock.itemDesc, stock.cost, stock.qtyInStock, stock.minLvl, stock.reorderQty, stock.supplier.company, stock.restockDate.sDay, stock.restockDate.sMonth, stock.restockDate.sYear);
    }
    printf("++============+==============================+===================+============+==========+=================+=================+================+===================++\n");


    fclose(fptr);

    char confirmView;
    printf("\nDo You Want To View Supplier Details? (Y/N) > ");
    rewind(stdin);
    confirmView = toupper(getchar());
    if (confirmView == 'Y') {
        displaySupplierDetails();
    }
}

void displaySupplierDetails() {
    FILE* vptr = fopen(STOCK_FILENAME, "rb");
    if (vptr == NULL) {
        printf("Error. File not found.\n");
        exit(-1);
    }
    Stock stock;

    printf("\n\n++===============================================================================++\n");
    printf("||                                   Supplier Details                            ||\n");
    printf("|+=============================+===========================+=====================+|\n");
    printf("||        Supplier Name        |     Person In Charge      |    Contact Number   ||\n");
    printf("|+-----------------------------+---------------------------+---------------------+|\n");
    while (fread(&stock, sizeof(stock), 1, vptr) != 0) {
        printf("|| %-27s | %-25s | %-19s ||\n", stock.supplier.company, stock.supplier.personInCharge, stock.supplier.contactNo);
    }
    printf("++===============================================================================++\n\n\n");

    fclose(vptr);
}

void getStock(Stock stockItem[], int* sCount) {
    int i = 0;
    /* read data from binary file */
    FILE* fptr = fopen(STOCK_FILENAME, "rb");
    if (fptr == NULL) {
        printf("File not found.\n");
        exit(-1);
    }

    while (fread(&stockItem[i], sizeof(stockItem[i]), 1, fptr)) {
        i++;
        *sCount = i;
    }

    fclose(fptr);
}

void searchStock(Stock stockItem[]) {
    char itemCode[6] = { '\0' };
    int sCount;
    getStock(stockItem, &sCount);
    printf("\nEnter Item Code To Search > ");
    rewind(stdin);
    gets(itemCode);
    //validation of stock item code
    while (
        (strlen(itemCode) != 5) ||
        !isalpha(itemCode[0]) ||
        !isalpha(itemCode[1]) ||
        !isdigit(itemCode[2]) ||
        !isdigit(itemCode[3]) ||
        !isdigit(itemCode[4])
        )
    {
        printf("Error: Invalid Stock Item Code.\n");
        printf("Please Enter Item Code Again (Eg. VC0001) > ");
        rewind(stdin);
        gets(itemCode);
    }
    viewSearchedStock(stockItem, itemCode, sCount);
}

void viewSearchedStock(Stock stockItem[], char itemCode[6], int sCount) {
    printf("+-------------------------------------------------+\n");
    printf("|             Item Details for \"%-6s\"           |\n", itemCode);
    printf("+=================================================+\n");
    for (int i = 0; i < sCount; i++) {
        if (strcmp(itemCode, stockItem[i].itemCode) == 0) {
            printf("|  %-25s: %-19s |\n", "Item Name", stockItem[i].itemName);
            printf("|  %-25s: %-19s |\n", "Item Description", stockItem[i].itemDesc);
            printf("|  %-25s: %-19.2lf |\n", "Item Cost(RM)", stockItem[i].cost);
            printf("|  %-25s: %-19d |\n", "Quantity In Stock", stockItem[i].qtyInStock);
            printf("|  %-25s: %-19d |\n", "Minimum Level of Stock", stockItem[i].minLvl);
            printf("|  %-25s: %-19d |\n", "Reorder Quantity", stockItem[i].reorderQty);
            printf("|  %-25s: %-19s |\n", "Supplier", stockItem[i].supplier.company);
            printf("|  %-25s: %02d-%02d-%04d          |\n", "Last Restock Date", stockItem[i].restockDate.sDay, stockItem[i].restockDate.sMonth, stockItem[i].restockDate.sYear);
        }
    }
    printf("+-------------------------------------------------+\n\n\n");
}

void modifyStock(Stock stockItem[]) {
    int sCount, option;
    getStock(stockItem, &sCount);
    char itemCode[6] = { '\0' }, itemName[60] = { '\0' }, itemDesc[30] = { '\0' }, personInCharge[30] = { '\0' }, contactNo[12] = { '\0' };
    double cost;
    int confirmModify, lsDay, lsMonth, lsYear;

    // Get item code to modify
    printf("Enter Item Code To Modify > ");
    rewind(stdin);
    gets(itemCode);

    //validation of stock item code
    while ((strlen(itemCode) != 5) ||!isalpha(itemCode[0]) ||!isalpha(itemCode[1]) ||!isdigit(itemCode[2]) ||!isdigit(itemCode[3]) ||!isdigit(itemCode[4]))
    {
        printf("Error: Invalid Stock Item Code.\n");
        printf("Please Enter Item Code Again (Eg. VC0001) > ");
        rewind(stdin);
        gets(itemCode);
    }

    do {
        printf("+--------------------------------------------+\n");
        printf("|         Modify Stock Item Details          |\n");
        printf("+--------------------------------------------+\n");
        printf("| 1. Edit Item Name and Description          |\n");
        printf("| 2. Edit Cost of Stock Item                 |\n");
        printf("| 3. Edit Last Restock Date                  |\n");
        printf("| 4. Edit Supplier Details                   |\n");
        printf("| 5. Back                                    |\n");
        printf("+--------------------------------------------+\n");
        printf("Enter Selection (1-5) > ");

        scanf("%d", &option);

        printf("\n");

        // Search for the item code in the stock list
        for (int a = 0; a < sCount; a++) {
            if (strcmp(itemCode, stockItem[a].itemCode) == 0) {
                switch (option)
                {
                case 1:
                {
                    //Display current item name and prompt for new item name
                    printf("Item Name > %s\n", stockItem[a].itemName);
                    printf("Description > %s\n\n", stockItem[a].itemDesc);
                    printf("Enter New Item Name > ");
                    rewind(stdin);
                    gets(itemName);
                    printf("Enter New Item Description > ");
                    rewind(stdin);
                    gets(itemDesc);

                    // Prompt for confirmation to modify
                    printf("\nConfirm Modify? (Y/N) > ");
                    rewind(stdin);
                    confirmModify = toupper(getchar());
                    while (!isalpha(confirmModify) || (confirmModify != 'Y' && confirmModify != 'N')) {
                        printf("Error: Please Enter Y/N (Yes - Y|No - N).\n");
                        printf("Confirm Modify ? (Y/N) > ");
                        rewind(stdin);
                        confirmModify = toupper(getchar());
                    }

                    if (confirmModify == 'Y') {
                        strcpy(stockItem[a].itemName, itemName);
                        strcpy(stockItem[a].itemDesc, itemDesc);
                        break;
                    }

                }
                case 2:
                {
                    printf("Cost (RM) > %.2lf\n", stockItem[a].cost);
                    printf("\nEnter New Cost (RM) > ");
                    scanf("%lf", &cost);

                    while (cost <= 0) {
                        printf("Error: Invalid Cost\n");
                        printf("Enter New Cost (RM) > ");
                        scanf("%lf", &cost);
                    }

                    // Prompt for confirmation to modify
                    printf("\nConfirm Modify? (Y/N) > ");
                    rewind(stdin);
                    confirmModify = toupper(getchar());
                    while (!isalpha(confirmModify) || (confirmModify != 'Y' && confirmModify != 'N')) {
                        printf("Error: Please Enter Y/N (Yes - Y|No - N).\n");
                        printf("Confirm Modify ? (Y/N) > ");
                        rewind(stdin);
                        confirmModify = toupper(getchar());
                    }

                    if (confirmModify == 'Y') {
                        stockItem[a].cost = cost;
                        break;
                    }
                }
                case 3:
                {
                    // Display current quantity in stock and prompt for new quantity
                    printf("Last Restock Date (DD-MM-YYYY): %02d-%02d-%04d\n\n", stockItem[a].restockDate.sDay, stockItem[a].restockDate.sMonth, stockItem[a].restockDate.sYear);
                    printf("Enter Latest Restock Date (DD-MM-YYYY): ");
                    scanf("%d-%d-%d", &lsDay, &lsMonth, &lsYear);

                    //validation for last restock date
                    while (lsDay <= 0 || lsDay > 31 || lsMonth <= 0 || lsMonth > 12 || lsYear <= 0)
                    {
                        printf("Error: Invalid Date.\n");
                        printf("Enter Latest Restock Date (DD-MM-YYYY): ");
                        scanf("%d-%d-%d", &lsDay, &lsMonth, &lsYear);
                    }

                    // Prompt for confirmation to modify
                    printf("\nConfirm Modify? (Y/N) > ");
                    rewind(stdin);
                    confirmModify = toupper(getchar());
                    while (!isalpha(confirmModify) || (confirmModify != 'Y' && confirmModify != 'N')) {
                        printf("Error: Please Enter Y/N (Yes - Y|No - N).\n");
                        printf("Confirm Modify ? (Y/N) > ");
                        rewind(stdin);
                        confirmModify = toupper(getchar());
                    }

                    // Modify the quantity in stock if confirmed
                    if (confirmModify == 'Y') {
                        stockItem[a].restockDate.sDay = lsDay;
                        stockItem[a].restockDate.sMonth = lsMonth;
                        stockItem[a].restockDate.sYear = lsYear;
                        break;
                    }
                }
                case 4:
                {
                    printf("Supplier Person In Charge > %s\n", stockItem[a].supplier.personInCharge);
                    printf("Contact Number > %s\n\n", stockItem[a].supplier.contactNo);
                    printf("New Person In Charge > ");
                    rewind(stdin);
                    gets(personInCharge);
                    printf("New Contact Number > ");
                    rewind(stdin);
                    gets(contactNo);

                    while (((contactNo[0] != '0') || (contactNo[1] != '1')) ||
                        (strlen(contactNo) < 10) || (strlen(contactNo) > 11)) {
                        printf("Error: Invalid Contact Number.\n");
                        printf("Supplier Contact No (eg. 0108073347) > ");
                        rewind(stdin);
                        gets(contactNo);
                    }

                    // Prompt for confirmation to modify
                    printf("\nConfirm Modify? (Y/N) > ");
                    rewind(stdin);
                    confirmModify = toupper(getchar());
                    while (!isalpha(confirmModify) || (confirmModify != 'Y' && confirmModify != 'N')) {
                        printf("Error: Please Enter Y/N (Yes - Y|No - N).\n");
                        printf("Confirm Modify ? (Y/N) > ");
                        rewind(stdin);
                        confirmModify = toupper(getchar());
                    }

                    // Modify the quantity in stock if confirmed
                    if (confirmModify == 'Y') {
                        strcpy(stockItem[a].supplier.personInCharge, personInCharge);
                        strcpy(stockItem[a].supplier.contactNo, contactNo);
                        break;
                    }
                }
                default:
                    break;
                }

                // Modify the quantity in stock if confirmed
                if (confirmModify == 'Y') {
                    printf("\nStock Item \"%s\" Modified Successfully\n", stockItem[a].itemCode);
                    printf("=========================================\n");
                    printf("Item Name             : %s\n", stockItem[a].itemName);
                    printf("Item Description      : %s\n", stockItem[a].itemDesc);
                    printf("Item Cost(RM)         : %-10.2lf\n", stockItem[a].cost);
                    printf("Quantity In Stock     : %-10d\n", stockItem[a].qtyInStock);
                    printf("Minimum Level of Stock: %-10d\n", stockItem[a].minLvl);
                    printf("Reorder Quantity      : %-10d\n", stockItem[a].reorderQty);
                    printf("Supplier Name         : %s\n", stockItem[a].supplier.company);
                    printf("Latest Restock Date   : %02d-%02d-%04d\n\n", stockItem[a].restockDate.sDay, stockItem[a].restockDate.sMonth, stockItem[a].restockDate.sYear);
                }
                else {
                    printf("\nStock Item \"%s\" Modification Cancelled\n", stockItem[a].itemCode);
                }
            }
        }

    }while (option != 5);

    FILE* wptr = fopen(STOCK_FILENAME, "wb");
    fwrite(&stockItem[0], sizeof(Stock), sCount, wptr);
    fclose(wptr);
}

void deleteStock(Stock stockItem[]) {
    int sCount;
    getStock(stockItem, &sCount);
    char itemCode[6] = { '\0' }, confirmDelete;
    int deleteIndex;

    printf("Enter Item Code to Delete > ");
    rewind(stdin);
    gets(itemCode);

    //validation of stock item code
    while (
        (strlen(itemCode) != 5) ||
        !isalpha(itemCode[0]) ||
        !isalpha(itemCode[1]) ||
        !isdigit(itemCode[2]) ||
        !isdigit(itemCode[3]) ||
        !isdigit(itemCode[4])
        )
    {
        printf("Error: Invalid Stock Item Code.\n");
        printf("Enter Item Code to Delete > ");
        rewind(stdin);
        gets(itemCode);
    }

    for (int i = 0; i < sCount; i++) {
        if (strcmp(itemCode, stockItem[i].itemCode) == 0) {
            deleteIndex = i;
            printf("Item Details for \"%s\"\n", stockItem[i].itemCode);
            printf("=============================\n");
            printf("Item Name: %s\n", stockItem[i].itemName);
            printf("Item Description: %s\n", stockItem[i].itemDesc);
            printf("Confirm Delete Stock Item? (Y/N) > ");
            rewind(stdin);
            confirmDelete = toupper(getchar());
            while (!isalpha(confirmDelete) || (confirmDelete != 'Y' && confirmDelete != 'N')) {
                printf("Error: Please Enter Y/N (Yes - Y|No - N).\n");
                printf("Confirm Delete Stock Item? (Y/N) > ");
                rewind(stdin);
                confirmDelete = toupper(getchar());
            }
            if (confirmDelete == 'Y') {
                for (int i = deleteIndex; i < sCount; i++) {
                    stockItem[i] = stockItem[i + 1];
                }
                sCount--;
                printf("\nItem \"%s\" delete successfully.\n", itemCode);
            }
            
        }
    }

    FILE* wptr = fopen(STOCK_FILENAME, "wb");
    for (int i = 0; i < sCount; i++) {
        fwrite(&stockItem[i], sizeof(stockItem[i]), 1, wptr);
    }
    fclose(wptr);
    displayStock();
}

void updateQtyInStock(char itemCode[6], int qtyOrder) {
    static Stock stockItem[MAX_STOCK_SIZE];
    int sCount;
    getStock(stockItem, &sCount);
    for (int i = 0; i < sCount; i++) {
        if (strcmp(stockItem[i].itemCode, itemCode) == 0) {
            stockItem[i].qtyInStock -= qtyOrder;
        }
    }
    FILE* fptr = fopen(STOCK_FILENAME, "wb");

    //write new qty in stock when add new sales order
    fwrite(&stockItem[0], sizeof(Stock), sCount, fptr);

    fclose(fptr);
}

void stockReport() {
    system("cls");
    Stock stock;
    SYSTEMTIME t;
    GetLocalTime(&t);

    FILE* fptr = fopen(STOCK_FILENAME, "rb");

    if (fptr == NULL) {
        printf("File not found.\n");
        exit(-1);
    }
    printf("+--------------------------------------------------------------------------------------------------------------+\n");
    printf("|                                  Stock Daily Report - %02d/%02d/%d [%02d:%02d:%02d]                                  |\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond);
    printf("+--------------------------------------------------------------------------------------------------------------+\n");
    printf("| %-30s | %-19s | %-16s | %-16s | %-14s |\n", "Item Name", "Purchased Cost(RM)", "Quantity In Stock", "Reorder Quantity", "Supplier");
    printf("+--------------------------------------------------------------------------------------------------------------+\n");
    while (fread(&stock, sizeof(stock), 1, fptr) != 0) {
        printf("| %-30s | %-19.2lf | %-17d | %-16d | %-14s |\n", stock.itemName, stock.cost, stock.qtyInStock, stock.reorderQty, stock.supplier.company);
    }

    printf("+--------------------------------------------------------------------------------------------------------------+\n\n\n");

    fclose(fptr);
}

int validateItemCode(char itemCode[6]) {
    Stock stock;

    //Validation for item code
    FILE* fptr = fopen(STOCK_FILENAME, "rb");
    if (fptr == NULL) {
        printf("Error: File not found\n");
        exit(-1);
    }
    while (fread(&stock, sizeof(Stock), 1, fptr) != 0) {
        if (strcmp(itemCode, stock.itemCode) == 0)
        {
            fclose(fptr);
            printf("Error: Item code has already exist!\n\n");
            return 0; // indicate validation failure
        }
    }
    fclose(fptr);


    return 1; // indicate validation success
}
