# MavFinancial
## MavFinancial Overview Summary
The code implements a simple banking system, Mav Financials, enabling users to register, log in, and manage their accounts. User data, including personal details, balances, and transactions, is stored persistently in a file (user_data.txt). After logging in, users can transfer money, view their balance, check transaction history, and edit personal information. The system also allows users to lock or unlock their account cards for added security. Transactions are logged with dates and amounts, and a menu-driven interface ensures easy navigation. The program uses modular functions for tasks like login validation, file operations, and transaction processing, but could benefit from improvements in security, error handling, and scalability.

## Key Features of MavFinancial
### User Registration

-Users can create an account by providing details such as username, password, full name, birthday, social security number, phone number, and address.

-The new account is saved to a file (user_data.txt) as a binary structure, ensuring user data persistence across program runs.
### User Login

-Users can log in by entering their username and password.

-The system verifies the credentials by reading user data from the file.

### Transfer Money
-Users can transfer money to another registered user by specifying the recipient's username and transfer amount.

-The system updates both users' balances and logs the transaction details (date and amount) for each account.

### View Balance
-Users can view their current account balance.
### View Transaction History
-Users can view up to 10 previous transactions (date and amount).
### View/Edit Account Information
-Users can view all their stored personal information.

-Users are given the option to edit specific details such as username, password, phone number, or address.

### Lock/Unlock Card
-Users can lock or unlock their card to prevent unauthorized access to their account.

### Data Persistence

-User data, including account details, transactions, and lock status, is stored in a file (user_data.txt) and retrieved when needed.

-This enables the program to retain user information across multiple runs.

