#include <stdio.h>
#include <string.h>
#include <time.h>

#define ROUTING 063292855
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//Define Transaction Structure
struct Transaction{
    char date[50];
    double amount;
};
// User accounts structure
struct UserAccount {
    char username[50];
    char password[50];
    double balance;

    char name[20];
    char birthday[11];
    char socialSecurity[10];
    char phoneNum[11];
    char streetAddress[50];
    int pin;
    int accNum;
    //0-Unlocked 1-Locked
    int locked;
    //Nested structure to search transactions;
    struct Transaction transactions[10];
    int transactionNumber;
};

int checkUsername(FILE *file, char *username);
void getCurrentDate(char *print);
void viewTransactions(FILE *file, char* username);
void registerUser(FILE* file);
int login(FILE* file, char* username, char* password);
void transfer(FILE *file, char* username);
void viewBalance(FILE *file, char* username);
void viewAccount(FILE *file, char* username);
void lockcard(FILE *file, char* username);
void printLogo();

int main() {
    //Opens file to store structures
    FILE* userFile = fopen("user_data.txt", "a+");

    if (userFile == NULL) {
        printf("Error: Unable to open the user data file.\n");
        return 1;
    }

    int choice, exit = 0;
    struct UserAccount mainUser;
    char username[50], password[50];

    //While loop for entry screen
    while (1) {
        exit = 0;
        printLogo();
        printf(BLUE"\nWelcome to Mav Financials!\n"RESET);
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser(userFile);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                if (login(userFile, username, password) == 1) {

                    //Insert functions here
                    while(!exit){
                        printf("\n1. Transfer Money\n");
                        printf("2. View Balance\n");
                        printf("3. View Previous Transactions\n");
                        printf("4. View Account Information\n");
                        printf("5. Lock/Unlock Card\n");
                        printf("6. Logout\n");
                        scanf("%d", &choice);

                        switch(choice) {
                            case 1:
                                //Transfers money between users
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "rb+");
                                transfer(userFile, username);
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "a+");
                                break;

                            case 2:
                                viewBalance(userFile, username);
                                break;
                            
                            case 3:
                                viewTransactions(userFile, username);
                                break;
                            
                            case 4:
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "rb+");
                                viewAccount(userFile, username);
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "a+");
                                break;
                            
                            case 5:
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "rb+");
                                lockcard(userFile, username);
                                fclose(userFile);
                                userFile = fopen("user_data.txt", "a+");
                                break;

                            case 6:
                                exit = 1;
                        } 
                    }
                }
                break;
            case 3:
                fclose(userFile);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}

//Returns 1 if Username exists
int checkUsername(FILE *file, char *username){
    struct UserAccount user;
    fseek(file, 0, SEEK_SET);

    while(fread(&user, sizeof(struct UserAccount), 1, file) == 1){
        if(strcmp(user.username, username) == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void printLogo(){
    printf(RED"   *                (                                         \n");
    printf(" (  `               )\\ )                                (     \n");
    printf(" )\\))(     )  )    (()/( (           )          (     ) )\\    \n");
    printf("((_)()\\ ( /( /((    /(_)))\\  (    ( /(  (     ( )\\ ( /(((_|   \n");
    printf("(_()((_))(_)|_))\\  (_))_((_) )\\ ) )(_)) )\\ )  )((_))(_))_ )\\  \n");
    printf(BLUE"|  \\/  ((_)__)((_) | |_  (_)_(_/(((_)_ _(_/( ((_|_|(_)_| ((_) \n");
    printf("| |\\/| / _` \\ V /  | __| | | ' \\)) _` | ' \\)) _|| / _` | (_-< \n");
    printf("|_|  |_\\__,_|\\_/   |_|   |_|_||_|\\__,_|_||_|\\__||_\\__,_|_/__/ \n"RESET);
}
//Returns month-day-year
void getCurrentDate(char *print){
    time_t t;
    struct tm* tm_info;

    time(&t);
    tm_info = localtime(&t);

    strftime(print, 20, "%m-%d-%Y", tm_info);
}

void viewTransactions(FILE *file, char* username){
    struct UserAccount user;

    fseek(file, 0, SEEK_SET);
    while(fread(&user, sizeof(struct UserAccount), 1, file) ==1 ){
        if(strcmp(user.username, username) == 0){
            printf("DATE\tAMOUNT\n");
            for(int i=0; i < user.transactionNumber; i++){
               // printf("DATE\tAMOUNT");
               printf("%s\t%f\n", user.transactions[i].date, user.transactions[i].amount);
            }
        }
    }
}

void registerUser(FILE* file) {
    struct UserAccount user;
    int userExists = 1;
    //Creates user account
    printf("Enter username: ");
    scanf("%s", user.username);
    
    /*
    while(userExists){
        printf("Enter username: ");
        scanf("%s", user.username);
        //Checks if username already exists
        if(checkUsername(file, user.username) == 1){
            printf("Username Already Exists! Please Enter a Different Username.\n");
        }
        else{
            userExists = 0;
        }
    }
    */

    printf("Enter password: ");
    scanf("%s", user.password);

    //fwrite(&user, sizeof(struct UserAccount), 1, file);
    printf("Account created successfully!\n");

    getchar();
    
    //Setting up Personal Information
    printf("Enter your full name: ");
    fgets(user.name, 20, stdin);
    user.name[strcspn(user.name, "\n")] = '\0';
    printf("Enter your birthday in the formath MM/DD/YYYY: ");
    scanf("%s", user.birthday);
    printf("Enter your 9 digit Social Security Number: ");
    scanf("%s", user.socialSecurity);
    printf("Enter your 10 digit Phone Number: ");
    scanf("%s", user.phoneNum);
    getchar();
    printf("Enter your full address: ");
    fgets(user.streetAddress, 30, stdin);
    user.streetAddress[strcspn(user.streetAddress, "\n")] = '\0';
    user.locked = 0;
    user.balance = 0.0;
    user.transactionNumber = 0;
    printf("Account created successfully!\n");

    if (fwrite(&user, sizeof(struct UserAccount), 1, file) != 1) {
        perror("Error writing to file");
    } else {
        printf("Account created successfully!\n");
    }

}

int login(FILE* file, char* username, char* password) {
    struct UserAccount user;

    //Sets file pointer to beggining of file
    fseek(file, 0, SEEK_SET);
    
    while (fread(&user, sizeof(struct UserAccount), 1, file) == 1) {
        /*printf("%s", user.username);
        printf("%s", user.password);*/
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            printf("Login successful. Welcome, %s!\n", user.username);
            return 1;
        }//Insert Invalid Password else
    
    }

    printf("Invalid username or password. Please try again.\n");
    return 0;
}

void transfer(FILE *file, char* username){
    struct UserAccount user, user2;
    double transferAmount;
    char reciever[20];

    printf("Enter the username of the person you wish to send money to \n");
    scanf("%s", reciever);
    printf("How much would you like to send to %s \n", reciever);
    scanf("%d", &transferAmount);
    
    //Sets file pointer to beggining of file
    fseek(file, 0, SEEK_SET);

    
    while (fread(&user, sizeof(struct UserAccount), 1, file) == 1) {
        if (strcmp(user.username, username) == 0) {

            fseek(file, 0, SEEK_SET);
            
            while (fread(&user2, sizeof(struct UserAccount), 1, file) == 1) {
                if (strcmp(user2.username, reciever) == 0) {

                    //if(user.locked == 0)
                    //Adjust the balance for each account
                    user.balance -= transferAmount;
                    user2.balance += transferAmount;
                    printf("Stops 1\n");

                    //Adjust Transaction Details(In progress)
                    user.transactions[user.transactionNumber].amount = transferAmount;
                    getCurrentDate(user.transactions[user.transactionNumber].date);
                    user.transactionNumber++;

                    user2.transactions[user2.transactionNumber].amount = transferAmount;
                    getCurrentDate(user2.transactions[user2.transactionNumber].date);
                    user2.transactionNumber++;
                    
                    printf("Stops 2\n");

                    //Send information to file
                   // fseek(file, 0, SEEK_SET);
                    fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                    fwrite(&user, sizeof(struct UserAccount), 1, file);

                    //fseek(file, 0, SEEK_SET);
                    fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                    fwrite(&user2, sizeof(struct UserAccount), 1, file);

                    
                    printf("Stops 3\n");
                    printf("Money Transferred Succesfully\n");
                    return;

                }
                else
                    printf("Reciever not found\n");

            }
        }
    }
}

void viewBalance(FILE *file, char* username){

    struct UserAccount u;
    fseek(file, 0, SEEK_SET);

    while(fread(&u, sizeof(struct UserAccount), 1, file) == 1)
        if(strcmp(u.username, username) == 0)
            printf("%d", u.balance);
}

void viewAccount(FILE *file, char* username){
    
    int input;
    int choice, exit=0;

    struct UserAccount user;
    fseek(file, 0, SEEK_SET);

    while(fread(&user, sizeof(struct UserAccount), 1, file) == 1){
        if(strcmp(user.username, username) == 0){
            
            //printf("Card: %d\n", user.accNum);
            printf("Name: %s\n", user.name);
            printf("Username: %s\n", user.username);
            printf("Password: %s\n", user.password);
            printf("Birthday: %s\n", user.birthday);
            printf("Phone Number: %s\n", user.phoneNum);
            printf("Social Security %s\n", user.socialSecurity);
            printf("Address: %s\n", user.streetAddress);
            printf("Would you like to change this information?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            while(1){
                scanf(" %d", &input);
                if(input == 1){
                    printf("Select The Information to be Edited\n");
                    while(!exit){
                        printf("1. Username\n");
                        printf("2. Password\n");
                        printf("3. Birthday\n");
                        printf("4. Phone Number\n");
                        printf("5. Address\n");
                        printf("6. Exit\n");

                        scanf("%d", &choice);
                        switch(choice){
                            case 1:
                                printf("Enter New Username: ");
                                scanf("%s", user.username);
                                break;
                            case 2:
                                printf("Enter New Password: ");
                                scanf("%s", user.password);
                                break;
                            case 3: 
                                printf("Edit your Birthday: ");
                                scanf("%s", user.birthday);
                                break;
                            case 4:
                                printf("Enter New Phone Number: ");
                                scanf("%s", user.phoneNum);
                                break;
                            case 5:
                                printf("Enter New Address: ");
                                getchar();
                                fgets(user.streetAddress, 30, stdin);
                                user.streetAddress[strcspn(user.streetAddress, "\n")] = '\0';
                                break;
                            case 6:
                                exit = 1;
                                break;
                            default:
                                printf("Invalid Choice\n");
                                break;
                        }  
                    }

                    fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                    if (fwrite(&user, sizeof(struct UserAccount), 1, file) != 1) {
                        perror("Error writing to file");
                    } else {
                        printf("Information Edited successfully!\n");
                    }
                    return;
                }
                else if(input == 2){
                    return;
                }
                else{
                    printf("Invalid Choice\n");
                }
            }
        }
    }
}

void lockcard(FILE *file, char* username){
    struct UserAccount user;
    fseek(file, 0, SEEK_SET);

    while(fread(&user, sizeof(struct UserAccount), 1, file)== 1){
        if(strcmp(user.username, username) == 0){
            if(user.locked == 1){
                user.locked = 0;
                printf("Card is now unlocked.");
                fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                fwrite(&user, sizeof(struct UserAccount), 1, file);
                printf("%d", user.locked);
                return;
            }
            else if(user.locked == 0){
                user.locked = 1;
                printf("Card is now locked.");
                fseek(file, -(long)sizeof(struct UserAccount), SEEK_CUR);
                fwrite(&user, sizeof(struct UserAccount), 1, file);
                printf("%d", user.locked);
                return;
            }
        }
    }
}



