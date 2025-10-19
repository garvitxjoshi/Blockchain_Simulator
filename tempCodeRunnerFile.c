#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct account
{
    int accID;
    char name[50];
    float balance;
} account;

#define max_accounts 1000
account *accounts[max_accounts];
int accountcount = 0;
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
    float balance;
    printf("Enter Account ID: ");
    scanf("%d", &id);
    getchar();
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
    printf("Deposit successful. New balance: ₹%.2f\n", acc->balance);
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
    printf("Withdrawal successful. New balance: ₹%.2f\n", acc->balance);
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
    printf("₹%.2f transferred from %s to %s\n", amount, from->name, to->name);
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
        printf("ID: %d, Name: %s, Balance: ₹%.2f\n",
               accounts[i]->accID, accounts[i]->name, accounts[i]->balance);
    }
}
// Function to update account details
void updateaccount()
{
    int id;
    printf("Enter Account ID to update: ");
    scanf("%d", &id);
    account *acc = findaccount(id);
    if (acc == NULL)
    {
        printf("Account not found.\n");
        return;
    }
    printf("Current Name: %s", acc->name);
    printf("Enter new name: ");
    getchar();
    fgets(acc->name, sizeof(acc->name), stdin);
    acc->name[strcspn(acc->name, "\n")] = 0;
    printf("Account updated successfully!\n");
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
    printf("Balance: ₹%.2f\n", acc->balance);
}
// Function to save accounts to file
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
// Main Function
int main()
{
    int choice;
    loadaccountsfromfile();
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
        printf("9. Exit\n");

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
            printf("Exiting...\n");
            for (int i = 0; i < accountcount; i++){
                free(accounts[i]);
        }
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    saveaccountstofile();
    return 0;
}
