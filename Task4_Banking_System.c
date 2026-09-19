#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "accounts.dat"

typedef struct {
    long accountNo;
    char name[50];
    double balance;
} Account;

void createAccount(void);
void deposit(void);
void withdrawMoney(void);
void checkBalance(void);
void displayAccounts(void);

int main(void) {
    int choice;

    do {
        printf("\n===== Bank Account Management System =====\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: displayAccounts(); break;
            case 6: printf("Thank you for using the banking system.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}

void createAccount(void) {
    FILE *fp;
    Account a;

    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%ld", &a.accountNo);

    printf("Enter Account Holder Name: ");
    scanf(" %49[^\n]", a.name);

    printf("Enter Initial Deposit: ");
    scanf("%lf", &a.balance);

    if (a.balance < 0) {
        printf("Initial deposit cannot be negative.\n");
        fclose(fp);
        return;
    }

    fwrite(&a, sizeof(Account), 1, fp);
    fclose(fp);

    printf("Account created successfully.\n");
}

void deposit(void) {
    FILE *fp;
    Account a;
    long accountNo;
    double amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%ld", &accountNo);

    printf("Enter Deposit Amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Deposit amount must be positive.\n");
        return;
    }

    fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        if (a.accountNo == accountNo) {
            a.balance += amount;

            fseek(fp, -(long)sizeof(Account), SEEK_CUR);
            fwrite(&a, sizeof(Account), 1, fp);

            printf("Deposit successful. New Balance = %.2lf\n", a.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Account not found.\n");
}

void withdrawMoney(void) {
    FILE *fp;
    Account a;
    long accountNo;
    double amount;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%ld", &accountNo);

    printf("Enter Withdrawal Amount: ");
    scanf("%lf", &amount);

    if (amount <= 0) {
        printf("Withdrawal amount must be positive.\n");
        return;
    }

    fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        if (a.accountNo == accountNo) {
            found = 1;

            if (amount > a.balance) {
                printf("Insufficient balance.\n");
            } else {
                a.balance -= amount;

                fseek(fp, -(long)sizeof(Account), SEEK_CUR);
                fwrite(&a, sizeof(Account), 1, fp);

                printf("Withdrawal successful. New Balance = %.2lf\n",
                       a.balance);
            }
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Account not found.\n");
}

void checkBalance(void) {
    FILE *fp;
    Account a;
    long accountNo;
    int found = 0;

    printf("Enter Account Number: ");
    scanf("%ld", &accountNo);

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No accounts found.\n");
        return;
    }

    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        if (a.accountNo == accountNo) {
            printf("\nAccount Number : %ld\n", a.accountNo);
            printf("Account Holder : %s\n", a.name);
            printf("Balance        : %.2lf\n", a.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("Account not found.\n");
}

void displayAccounts(void) {
    FILE *fp;
    Account a;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No accounts found.\n");
        return;
    }

    printf("\n%-15s %-25s %-12s\n",
           "Account No.", "Account Holder", "Balance");
    printf("--------------------------------------------------------\n");

    while (fread(&a, sizeof(Account), 1, fp) == 1) {
        printf("%-15ld %-25s %.2lf\n",
               a.accountNo, a.name, a.balance);
    }

    fclose(fp);
}
