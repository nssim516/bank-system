#include "code.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{

    Bank bank;
    StatusCode status;

    // Adding accounts
    vector<string> names = {"Alice", "Bob", "Charlie", "Adam"};
    vector<string> password = {"Strong@123", "Password#123", "Secure#123", "Weak"};

    for (size_t i = 0; i < names.size(); ++i)
    {

        status = bank.addAccount(names[i], password[i]);

        if (status == StatusCode::SUCCESS)
        {

            cout << "Bank Account for " << names[i] << " created! Account Number: " << bank.getLastAccountNumber() << endl;
        }

        else if (status == StatusCode::WEAK_PASSWORD)
        {

            cout << "Bank Account for " << names[i] << " can not be created- Weak Password" << endl;
        }
    }

    cout << endl;

    // Depositing
    bank.bankDeposit(1000, 1000, "Strong@123");
    bank.bankDeposit(1001, 100, "Password#123");
    bank.bankDeposit(1002, 500, "Secure#123");

    // Withdrawal
    bank.bankWithdraw(1000, 500, "Strong@123");
    bank.bankWithdraw(1002, 100, "Secure#123");

    // Balance Inquiry
    bank.balanceInquiry(1000, "Strong@123");
    bank.balanceInquiry(1002, "Secure#123");
    cout << endl;

    // Printing transaction history
    bank.transactionHistory(1000, "Strong@123");
    bank.transactionHistory(1002, "Secure#123");


    return 0;
}
