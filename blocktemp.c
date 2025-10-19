#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Account structure
typedef struct account
{
    int accID;
    char name[50];
    float balance;
} account;

#define max_accounts 1000
account *accounts[max_accounts];
int accountcount = 0;

// User structure
typedef struct
{
    int id;
    char username[50];
    char password[50];
} user;

#define max_user 1000
user users[max_user];
int usercount = 0;

// ----------------- File Operations -----------------

void saveuserstofile()
{
    FILE *fp = fopen("users.dat", "wb");
    if (!fp)
    {
        printf("Error opening users file for writing.\n");
        return;
    }
    fwrite(&usercount, sizeof(int), 1, fp);
    fwrite(users, sizeof(user), usercount, fp);
    fclose(fp);
}

void loadusersfromfile()
{
    FILE *fp = fopen("users.dat", "rb");
    if (!fp)
    {
        printf("No previous users file found.\n");
        return;
    }
    fread(&usercount, sizeof(int), 1, fp);
    fread(users, sizeof(user), usercount, fp);
    fclose(fp);
}

void saveaccountstofile()
{
    FILE *fp = fopen("accounts.dat", "wb");
    if (!fp)
    {
        printf("Error opening accounts file for writing.\n");
        return;
    }
    fwrite(&accountcount, sizeof(int), 1, fp);
    for (int i = 0; i < accountcount; i++)
        fwrite(accounts[i], sizeof(account), 1, fp);
    fclose(fp);
}

void loadaccountsfromfile()
{
    FILE *fp = fopen("accounts.dat", "rb");
    if (!fp)
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
}

// ----------------- Account Operations -----------------

account *create_account()
{
    if (accountcount >= max_accounts)
    {
        printf("Maximum account limit reached.\n");
        return NULL;
    }

    int id;
    char name[50];
    float balance;

    printf("Enter Account ID: ");
    scanf("%d", &id);
    getchar(); // consume leftover newline

    printf("Enter Account Holder Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter Account Balance: ");
    scanf("%f", &balance);

    account *newacc = (account *)malloc(sizeof(account));
    newacc->accID = id;
    strcpy(newacc->name, name);
    newacc->balance = balance;

    accounts[accountcount++] = newacc;
    printf("Account created successfully!\n");
    return newacc;
}

account *findaccount(int id)
{
    for (int i = 0; i < accountcount; i++)
    {
        if (accounts[i]->accID == id)
            return accounts[i];
    }
    return NULL;
}

void deposit()
{
    int id;
    float amount;
    printf("Enter Account ID: ");
    scanf("%d", &id);

    account *acc = findaccount(id);
    if (!acc)
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
    if (!acc)
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
    if (!from)
    {
        printf("Sender not found!\n");
        return;
    }

    printf("Enter receiver Account ID: ");
    scanf("%d", &toID);
    account *to = findaccount(toID);
    if (!to)
    {
        printf("Receiver not found!\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    if (amount <= 0 || amount > from->balance)
    {
        printf("Invalid or insufficient balance!\n");
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
        printf("ID: %d, Name: %s, Balance: $%.2f\n",
               accounts[i]->accID, accounts[i]->name, accounts[i]->balance);
    }
}

void updateaccount()
{
    int id;
    printf("Enter Account ID to update: ");
    scanf("%d", &id);
    getchar(); // consume newline

    account *acc = findaccount(id);
    if (!acc)
    {
        printf("Account not found.\n");
        return;
    }

    printf("Current Name: %s\n", acc->name);
    printf("Enter new name: ");
    fgets(acc->name, sizeof(acc->name), stdin);
    acc->name[strcspn(acc->name, "\n")] = 0;

    printf("Account updated successfully!\n");
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
    if (!acc)
    {
        printf("Account not found.\n");
        return;
    }

    printf("--- Account Details ---\n");
    printf("Account ID: %d\n", acc->accID);
    printf("Holder Name: %s\n", acc->name);
    printf("Balance: $%.2f\n", acc->balance);
}

// ----------------- User Authentication -----------------

void registeruser()
{
    if (usercount >= max_user)
    {
        printf("User limit reached.\n");
        return;
    }

    user newuser;
    printf("Enter your existing Bank Account ID: ");
    scanf("%d", &newuser.id);

    int validacc = 0;
    for (int i = 0; i < accountcount; i++)
    {
        if (accounts[i]->accID == newuser.id)
        {
            validacc = 1;
            break;
        }
    }
    if (!validacc)
    {
        printf("Invalid Account ID.\n");
        return;
    }

    printf("Enter your username: ");
    scanf("%s", newuser.username);

    for (int i = 0; i < usercount; i++)
    {
        if (strcmp(users[i].username, newuser.username) == 0)
        {
            printf("Username already exists. Try a different one.\n");
            return;
        }
    }

    printf("Enter your password: ");
    getchar(); // consume leftover newline
    fgets(newuser.password, sizeof(newuser.password), stdin);
    newuser.password[strcspn(newuser.password, "\n")] = 0;

    users[usercount++] = newuser;
    saveuserstofile();
    printf("User registered successfully.\n");
}

int loginuser()
{
    int accid;
    char username[50], password[50];

    printf("Enter your Bank Account ID: ");
    scanf("%d", &accid);
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    getchar();
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < usercount; i++)
    {
        if (users[i].id == accid && strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            printf("Login successful. Welcome %s!\n", username);
            return 1;
        }
    }

    printf("Login failed. Please check your credentials.\n");
    return 0;
}

// Main Function

int main()
{
    int choice;
    int loggedIn = 0;

    loadaccountsfromfile();
    loadusersfromfile();

    printf("\n--- Welcome to Secure Bank System ---\n");

    while (1)
    {
        printf("\n--- Main Menu ---\n");
        printf("1. Create Bank Account (No login required)\n");
        printf("2. Login\n");
        printf("3. Register\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume leftover newline

        switch (choice)
        {
        case 1:
            create_account();
            saveaccountstofile();
            break;
        case 2:
            if (loginuser())
                loggedIn = 1;
            break;
        case 3:
            registeruser();
            break;
        case 4:
            printf("Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }

        // Bank menu after successful login
        while (loggedIn)
        {
            printf("\n--- Bank Menu ---\n");
            printf("1. Create Account\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Display Accounts\n6. Update Account\n7. Delete Account\n8. View Account\n9. Save & Exit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            getchar(); // consume leftover newline

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
    }

    return 0;
}
