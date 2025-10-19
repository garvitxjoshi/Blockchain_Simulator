#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_user 1000
#define max_accounts 1000

// ------------------------------------------- STRUCTURES -------------------------------------------------------

typedef struct account
{
    int accID;
    char name[50];
    char phno[11]; // fixed: 10 digits + null terminator
    float balance;
} account;

account *accounts[max_accounts];
int accountcount = 0;

typedef struct
{
    int id;
    char username[50];
    char password[50];
} user;

user users[max_user];
int usercount = 0;

// ------------------------------------------- FILE FUNCTIONS ---------------------------------------------------

// Save users to file
void saveuserstofile()
{
    FILE *fp = fopen("users.dat", "wb");
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

// Load users from file
void loadusersfromfile()
{
    FILE *fp = fopen("users.dat", "rb");
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

// Save accounts to file
void saveaccountstofile()
{
    FILE *fp = fopen("accounts.dat", "wb");
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

// Load accounts from file
void loadaccountsfromfile()
{
    FILE *fp = fopen("accounts.dat", "rb");
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

// ------------------------------------------- AUTHENTICATION ----------------------------------------------------

// Register new user
void registeruser()
{
    if (usercount >= max_user)
    {
        printf("User limit reached.\n");
        return;
    }

    user newUser;

    printf("Enter User ID: ");
    if (scanf("%d", &newUser.id) != 1)
    {
        printf("Invalid input for User ID.\n");
        while (getchar() != '\n')
            ;
        return;
    }
    while (getchar() != '\n')
        ;

    printf("Enter Username: ");
    if (fgets(newUser.username, sizeof(newUser.username), stdin) == NULL)
    {
        printf("Error reading username.\n");
        return;
    }
    newUser.username[strcspn(newUser.username, "\n")] = 0;

    printf("Enter Password: ");
    if (fgets(newUser.password, sizeof(newUser.password), stdin) == NULL)
    {
        printf("Error reading password.\n");
        return;
    }
    newUser.password[strcspn(newUser.password, "\n")] = 0;

    users[usercount++] = newUser; // store in array
    printf("User registered successfully.\n");
}

// Login existing user
int loginuser()
{
    int accid;
    char username[50], password[50];

    printf("Enter your Bank Account ID: ");
    if (scanf("%d", &accid) != 1)
    {
        printf("Invalid input for Account ID.\n");
        while (getchar() != '\n')
            ;
        return 0;
    }
    while (getchar() != '\n')
        ;

    printf("Enter your username: ");
    if (fgets(username, sizeof(username), stdin) == NULL)
    {
        printf("Error reading username.\n");
        return 0;
    }
    username[strcspn(username, "\n")] = 0;

    printf("Enter your password: ");
    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        printf("Error reading password.\n");
        return 0;
    }
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < usercount; i++)
    {
        if (users[i].id == accid &&
            strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0)
        {
            printf("Login successful. Welcome %s!\n", username);
            return 1;
        }
    }

    printf("Login failed. Please check your credentials.\n");
    return 0;
}

// ------------------------------------------- ACCOUNT FUNCTIONS -------------------------------------------------

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
            fgets(acc->name, sizeof(acc->name), stdin);
            acc->name[strcspn(acc->name, "\n")] = 0;
            printf("Name updated successfully!\n");
            break;
        case 2:
            printf("Enter new phone number: ");
            fgets(acc->phno, sizeof(acc->phno), stdin);
            acc->phno[strcspn(acc->phno, "\n")] = 0;
            printf("Phone number updated successfully!\n");
            break;
        case 3:
            printf("Enter new amount: ");
            scanf("%f", &acc->balance);
            while (getchar() != '\n')
                ;
            printf("Balance updated successfully!\n");
            break;
        case 4:
            printf("Exiting update menu.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
}

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
                accounts[j] = accounts[j + 1];
            accountcount--;
            printf("Account deleted successfully!\n");
            break;
        }
    }
    if (!found)
        printf("Account not found!\n");
}

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
    printf("Phone Number: %s\n", acc->phno);
    printf("Balance: $%.2f\n", acc->balance);
}

// ------------------------------------------- MAIN FUNCTION ----------------------------------------------------

int main()
{
    int choice;
    int loggedIn = 0;

    loadaccountsfromfile();
    loadusersfromfile();

    printf("\n--- Welcome to Bank System ---\n");

    while (!loggedIn)
    {
        printf("\n1. Login\n2. Register\n3. Exit\nEnter choice: ");
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

    while (1)
    {
        printf("\n--- Bank Menu ---\n");
        printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n");
        printf("5. Display Accounts\n6. Update Account\n7. Delete Account\n8. View Account\n9. Save & Exit\n");
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