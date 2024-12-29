#ifndef CODE_HPP
#define CODE_HPP

#include <string>
#include <iostream>
#include <vector>

using namespace std;

// to define the status code of any operation
enum class StatusCode
{
    SUCCESS,
    INSUFFICIENT_BALANCE,
    INVALID_AMOUNT,
    INVALID_ACCOUNT,
    INVALID_PASSWORD,
    WEAK_PASSWORD
};

class Account
{
private:
    int m_account_number;
    string m_account_holder_name;
    double m_balance;
    vector<double> m_transaction_history;
    string m_password;

public:
    Account(int acc_num, const string& acc_holder, const string& pass);
    void updateTransactions(double amount);
    StatusCode deposit(double amount, const string& pass);
    StatusCode withdraw(double amount, const string& pass);
    StatusCode printBalance(const string& pass);
    StatusCode printTransactionHistory(const string& pass);

    friend class Bank;
};

class Bank
{
private:
    vector<Account> m_accounts{};
    int m_next_account_num{1000};

    bool passwordStrength(const string& pass);

public:
    int getLastAccountNumber();
    StatusCode addAccount(const string& acc_holder, const string& pass);
    StatusCode bankDeposit(int acc_num, double amount, const string& pass);
    StatusCode bankWithdraw(int acc_num, double amount, const string& pass);
    StatusCode balanceInquiry(int acc_num, const string& pass);
    StatusCode transactionHistory(int acc_num, const string& pass);
};

#endif // CODE_HPP
