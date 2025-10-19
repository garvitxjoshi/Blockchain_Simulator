#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_user 1000
#define max_accounts 1000

// ------------------------------------------- DEFINING STRUCTURES -------------------------------------------------------

// 1. User structure

typedef struct account
{
    int accID;
    char name[50];
    char phno[10];
    float balance;
} account;

account *accounts[max_accounts];
int accountcount = 0;

// 2. Authentication structure

typedef struct
{
    int id;
    char username[50];
    char password[50];
} user;

user users[max_user];
int usercount = 0;

// --------------------------------------------- HELPER FUNCTIONS TO SAVE DATA IN FILES --------------------------------------

// 1. For Save Data in users file

void saveuserstofile()
{
    FILE *fp = fopen("users.dat", "a+");
    if (fp == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&usercount, sizeof(int), 1, fp);
    fwrite(users, sizeof(user), usercount, fp);
    fclose(fp);
    printf("Users saved to file successfully.\n");
}

// 2. To load users from file

void loadusersfromfile()
{
    FILE *fp = fopen("users.dat", "a+");
    if (fp == NULL)
    {
        printf("No previous users file found.\n");
        return;
    }
    fread(&usercount, sizeof(int), 1, fp);
    fread(users, sizeof(user), usercount, fp);
    fclose(fp);
    printf("Users loaded from file successfully.\n");
}

// ACCOUNT FILE

// 1.To save accounts to file

void saveaccountstofile()
{
    FILE *fp = fopen("accounts.dat", "a+");
    if (fp == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&accountcount, sizeof(int), 1, fp);
    for (int i = 0; i < accountcount; i++)
    {
        fwrite(accounts[i], sizeof(account), 1, fp);
    }
    fclose(fp);
    printf("Accounts saved to file successfully.\n");
}

// 2. To Load Data from accounts File

void loadaccountsfromfile()
{
    FILE *fp = fopen("accounts.dat", "a+");
    if (fp == NULL)
    {
        printf("No previous accounts file found.\n");
        return;
    }
    fread(&accountcount, sizeof(int), 1, fp);
    for (int i = 0; i < accountcount; i++)
    {
        account *acc = (account *)malloc(sizeof(account));
        fread(acc, sizeof(account), 1, fp);
        accounts[i] = acc;
    }
    fclose(fp);
    printf("Accounts loaded from file successfully.\n");
}

// ---------------------------------------- To get in System FUNCTIONS --------------------------------------------------------

void registeruser()
{
    user newUser;

    printf("Enter User ID: ");
    if (scanf("%d", &newUser.id) != 1)
    {
        printf("Invalid input for User ID.\n");
        while (getchar() != '\n')
            ; // Clear input buffer
        return;
    }
    while (getchar() != '\n')
        ; // Clear trailing newline from input buffer

    printf("Enter Username: ");
    if (fgets(newUser.username, sizeof(newUser.username), stdin) == NULL)
    {
        printf("Error reading username.\n");
        return;
    }
    newUser.username[strcspn(newUser.username, "\n")] = 0; // Remove newline

    printf("Enter Password: ");
    if (fgets(newUser.password, sizeof(newUser.password), stdin) == NULL)
    {
        printf("Error reading password.\n");
        return;
    }
    newUser.password[strcspn(newUser.password, "\n")] = 0; // Remove newline

    // Open file in append binary mode to save user data
    FILE *file = fopen("users.dat", "ab");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&newUser, sizeof(user), 1, file);
    fclose(file);

    printf("User registered and data saved successfully.\n");
}

int loginuser()
{
    int accid;
    char username[50], password[50];
    user tempUser;

    printf("Enter your Bank Account ID: ");
    if (scanf("%d", &accid) != 1)
    {
        printf("Invalid input for Account ID.\n");
        while (getchar() != '\n')
            ; // Clear input buffer
        return 0;
    }
    while (getchar() != '\n')
        ; // Clear newline after scanf

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) == NULL)
    {
        printf("Error reading username.\n");
        return 0;
    }
    username[strcspn(username, "\n")] = 0; // Remove trailing newline

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        printf("Error reading password.\n");
        return 0;
    }
    password[strcspn(password, "\n")] = 0; // Remove trailing newline

    FILE *fp = fopen("users.dat", "rb");
    if (fp == NULL)
    {
        printf("Error opening users.dat file.\n");
        return 0;
    }

    while (fread(&tempUser, sizeof(user), 1, fp) == 1)
    {
        if (tempUser.id == accid &&
            strcmp(tempUser.username, username) == 0 &&
            strcmp(tempUser.password, password) == 0)
        {
            printf("Login successful. Welcome %s!\n", username);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    printf("Login failed. Please check your credentials.\n");
    return 0;
}

//--------------------------------------- After Getting Into System FUNCTIONS -----------------------------------------

// Function for creating a new account

account *create_account()
{
    if (accountcount >= max_accounts)
    {
        printf("Maximum account limit reached.\n");
        return NULL;
    }
    int id;
    char name[50];
    char phno[11]; 
    float balance;
    printf("Enter Account ID: ");
    scanf("%d", &id);
    getchar(); 
    printf("Enter Account Holder Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter User's Phone Number: ");
    fgets(phno, sizeof(phno), stdin);
    phno[strcspn(phno, "\n")] = 0;
    printf("Enter Account Balance: ");
    scanf("%f", &balance);

    account *newacc = (account *)malloc(sizeof(account));
    if (newacc == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newacc->accID = id;
    strcpy(newacc->name, name);
    strcpy(newacc->phno, phno);
    newacc->balance = balance;
    accounts[accountcount++] = newacc;

    printf("Account created successfully!\n");
    return newacc;
}


// Function to find an account by ID

account *findaccount(int id)
{
    for (int i = 0; i < accountcount; i++)
    {
        if (accounts[i]->accID == id)
        {
            return accounts[i];
        }
    }
    return NULL;
}

// Function to deposit money into an account

void deposit()
{
    int id;
    float amount;
    printf("Enter Account ID: ");
    scanf("%d", &id);
    account *acc = findaccount(id);
    if (acc == NULL)
    {
        printf("Account not found.\n");
        return;
    }
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    if (amount <= 0)
    {
        printf("Invalid amount.\n");
        return;
    }
    acc->balance += amount;
    printf("Deposit successful. New balance: $%.2f\n", acc->balance);
}

// Function to withdraw money from an account

void withdraw()
{
    int id;
    float amount;
    printf("Enter Account ID: ");
    scanf("%d", &id);
    account *acc = findaccount(id);
    if (acc == NULL)
    {
        printf("Account not found.\n");
        return;
    }
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);
    if (amount <= 0)
    {
        printf("Invalid amount.\n");
        return;
    }
    if (amount > acc->balance)
    {
        printf("Insufficient funds.\n");
        return;
    }
    acc->balance -= amount;
    printf("Withdrawal successful. New balance: $%.2f\n", acc->balance);
}

// Function to transfer amount between accounts

void transfer()
{
    int fromID, toID;
    float amount;
    printf("Enter sender Account ID: ");
    scanf("%d", &fromID);
    account *from = findaccount(fromID);
    if (from == NULL)
    {
        printf("Sender not found!\n");
        return;
    }
    printf("Enter receiver Account ID: ");
    scanf("%d", &toID);
    account *to = findaccount(toID);
    if (to == NULL)
    {
        printf("Receiver not found!\n");
        return;
    }
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > from->balance)
    {
        printf("Invalid or Insufficient balance!\n");
        return;
    }
    from->balance -= amount;
    to->balance += amount;
    printf("$%.2f transferred from %s to %s\n", amount, from->name, to->name);
}

// Function to display account detail

void displayaccount()
{
    if (accountcount <= 0)
    {
        printf("No account found!\n");
        return;
    }
    printf("\n--- Accounts ---\n");
    for (int i = 0; i < accountcount; i++)
    {
        printf("ID: %d, Name: %s, Phone Number: %s, Balance: $%.2f\n",
               accounts[i]->accID, accounts[i]->name, accounts[i]->phno, accounts[i]->balance);
    }
}

// Function to update account details

void updateaccount()
{
    int id, choice;
    printf("Enter Account ID to update: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid input for Account ID.\n");
        while (getchar() != '\n')
            ;
        return;
    }
    while (getchar() != '\n')
        ;

    account *acc = findaccount(id);
    if (acc == NULL)
    {
        printf("Account not found.\n");
        return;
    }

    do
    {
        printf("\nCurrent Info:\nName: %s\nPhone: %s\nBalance: %.2f\n", acc->name, acc->phno, acc->balance);
        printf("1. Change Name\n2. Change Phone Number\n3. Change Amount\n4. Exit\n");
        printf("Enter Choice To Update: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
            printf("Enter new name: ");
            if (fgets(acc->name, sizeof(acc->name), stdin) != NULL)
            {
                acc->name[strcspn(acc->name, "\n")] = 0;
                printf("Account holder name updated successfully!\n");
            }
            else
            {
                printf("Failed to update name.\n");
            }
            break;
        case 2:
            printf("Enter new phone number: ");
            if (fgets(acc->phno, sizeof(acc->phno), stdin) != NULL)
            {
                acc->phno[strcspn(acc->phno, "\n")] = 0;
                printf("Phone number updated successfully!\n");
            }
            else
            {
                printf("Failed to update phone number.\n");
            }
            break;
        case 3:
            printf("Enter new amount: ");
            if (scanf("%f", &acc->balance) != 1)
            {
                printf("Invalid input for balance.\n");
                while (getchar() != '\n')
                    ;
            }
            else
            {
                printf("Balance updated successfully!\n");
            }
            while (getchar() != '\n')
                ;
            break;
        case 4:
            printf("Exiting update menu.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    } while (choice != 4);
}

// Function to delete an account
void deleteaccount()
{
    int id, found = 0;
    printf("Enter Account ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < accountcount; i++)
    {
        if (accounts[i]->accID == id)
        {
            found = 1;
            free(accounts[i]);
            for (int j = i; j < accountcount - 1; j++)
            {
                accounts[j] = accounts[j + 1];
            }
            accountcount--;
            printf("Account deleted successfully!\n");
            break;
        }
    }
    if (!found)
    {
        printf("Account not found!\n");
    }
}
// Function to view account details
void viewaccount()
{
    int id;
    printf("Enter Account ID to view: ");
    scanf("%d", &id);
    account *acc = findaccount(id);
    if (acc == NULL)
    {
        printf("Account not found.\n");
        return;
    }
    printf("--- Account Details ---\n");
    printf("Account ID: %d\n", acc->accID);
    printf("Holder Name: %s\n", acc->name);
    printf("Balance: $%.2f\n", acc->balance);
    printf("Phone Number: %s\n", acc->phno);
}

// Main Function
int main()
{
    int choice;
    int loggedIn = 0;

    loadaccountsfromfile();
    loadusersfromfile();

    printf("\n--- Welcome to Secure Bank System ---\n");

    // Authentication
    while (!loggedIn)
    {
        printf("\n1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (loginuser())
                loggedIn = 1;
            break;
        case 2:
            registeruser();
            break;
        case 3:
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    // Bank operations menu after successful login
    while (1)
    {
        printf("\n--- Bank Menu ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Display Accounts\n");
        printf("6. Update Account\n");
        printf("7. Delete Account\n");
        printf("8. View Account\n");
        printf("9. Save & Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create_account();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            transfer();
            break;
        case 5:
            displayaccount();
            break;
        case 6:
            updateaccount();
            break;
        case 7:
            deleteaccount();
            break;
        case 8:
            viewaccount();
            break;
        case 9:
            saveaccountstofile();
            saveuserstofile();
            for (int i = 0; i < accountcount; i++)
                free(accounts[i]);
            printf("Accounts and users saved. Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
