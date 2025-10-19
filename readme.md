🏦 Secure Bank Management System

A C-based Banking Management System that provides secure login, user registration, and full account management with file persistence using binary files (.dat).
It allows users to create, update, view, transfer, deposit, and withdraw money from bank accounts — all through a command-line interface.

📋 Features
🧑‍💼 User Management

Register new users with unique ID, username, and password.

Login using credentials (ID + username + password).

Saves and loads users securely from users.dat.

💰 Account Management

Create multiple bank accounts.

Store account holder name, phone number, and balance.

Deposit and withdraw money.

Transfer funds between accounts.

Update account details (name, phone, balance).

Delete existing accounts.

View details of a specific account or display all accounts.

Save and load accounts automatically from accounts.dat.

💾 File Storage
File	Purpose
users.dat	Stores registered user credentials
accounts.dat	Stores all account information

Both are stored in binary format for compact and secure data handling.

⚙️ How It Works

When the program starts, it loads users and accounts (if saved before).

User must Login or Register to continue.

Once logged in, user can access all banking operations through a menu-driven interface.

On exit, all users and accounts are saved back to file automatically.

🧠 Program Flow
Start
│
├── Load users and accounts from file
│
├── Authentication Menu
│   ├── 1. Login
│   ├── 2. Register
│   └── 3. Exit
│
├── If login successful → Main Banking Menu
│   ├── 1. Create Account
│   ├── 2. Deposit
│   ├── 3. Withdraw
│   ├── 4. Transfer
│   ├── 5. Display All Accounts
│   ├── 6. Update Account
│   ├── 7. Delete Account
│   ├── 8. View Single Account
│   └── 9. Save & Exit
│
└── End

🛠️ How to Compile and Run
🧩 Requirements

GCC compiler or any standard C compiler

OS: Windows, Linux, or macOS

💻 Compilation
gcc bank_system.c -o bank_system

▶️ Run
./bank_system

📁 Project Structure
📂 SecureBankSystem
├── bank_system.c        # Main C source code
├── users.dat            # Binary file storing user credentials
├── accounts.dat         # Binary file storing account records
└── README.md            # Project documentation

🧾 Example Usage
--- Welcome to Secure Bank System ---
1. Login
2. Register
3. Exit
Enter choice: 2
Enter User ID: 101
Enter Username: John
Enter Password: 1234
User registered successfully.

--- Bank Menu ---
1. Create Account
2. Deposit
3. Withdraw
4. Transfer
...
Enter choice: 1
Enter Account ID: 5001
Enter Account Holder Name: John Doe
Enter User's Phone Number: 9876543210
Enter Account Balance: 1000
Account created successfully!

⚠️ Important Notes

Use unique Account IDs and User IDs to avoid conflicts.

Data persists automatically between runs using .dat files.

To reset data, delete users.dat and accounts.dat.

🧑‍💻 Author

Crypton Parkour
💡 Designed and developed as a console-based C project demonstrating:

File handling

Structures

Dynamic memory allocation

Menu-driven user interaction

Authentication system