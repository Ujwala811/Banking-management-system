#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    double balance;
} User;

User users[MAX_USERS];
int userCount = 0;

void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    User newUser;
    printf("-----User Registration-----");
    printf("\nEnter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    newUser.balance = 0.0;

    users[userCount++] = newUser;
    printf("User registered successfully!\n");
}

User* loginUser() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    printf("----User Login----");
    printf("\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return &users[i];
        }
    }

    printf("Invalid username or password.\n");
    return NULL;
}

void checkBalance(User* user) {
    printf("Current balance: $%.2f\n", user->balance);
}

void deposit(User* user) {
    double amount;
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);

    if (amount > 0) {
        user->balance += amount;
        printf("Deposit successful! New balance: $%.2f\n", user->balance);
    } else {
        printf("Invalid amount.\n");
    }
}

void withdraw(User* user) {
    double amount;
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);

    if (amount > 0 && amount <= user->balance) {
        user->balance -= amount;
        printf("Withdrawal successful! New balance: $%.2f\n", user->balance);
    } else {
        printf("Invalid amount or insufficient funds.\n");
    }
}

void transfer(User* user) {
    char recipientUsername[USERNAME_LENGTH];
    double amount;

    printf("Enter recipient username: ");
    scanf("%s", recipientUsername);
    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);

    if (amount > 0 && amount <= user->balance) {
        for (int i = 0; i < userCount; ++i) {
            if (strcmp(users[i].username, recipientUsername) == 0) {
                user->balance -= amount;
                users[i].balance += amount;
                printf("Transfer successful! New balance: $%.2f\n", user->balance);
                return;
            }
        }
        printf("Recipient not found.\n");
    } else {
        printf("Invalid amount or insufficient funds.\n");
    }
}

void userMenu(User* user) {
    int choice;

    do {
    	printf("---Banking Menu---");
        printf("\n1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(user);
                break;
            case 2:
                deposit(user);
                break;
            case 3:
                withdraw(user);
                break;
            case 4:
                transfer(user);
                break;
            case 5:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

int main() {
    int choice;
    User* loggedInUser = NULL;
    printf("-------Welcome to Banking Management System-------");

    do {
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedInUser = loginUser();
                if (loggedInUser != NULL) {
                    userMenu(loggedInUser);
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

