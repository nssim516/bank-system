#include "code.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Account Class
Account::Account(int acc_num, const string& acc_holder, const string& pass)
    : m_account_number(acc_num),
    m_account_holder_name(acc_holder),
    m_balance(0.0),
    m_password(pass){ }

// UPDATE TRANSACTIONS
void Account::updateTransactions(double amount)
{
    m_transaction_history.push_back(amount);
    m_balance = m_balance + amount;
}

// DEPOSIT
StatusCode Account::deposit(double amount, const string& pass)
{
    if (pass != m_password)
    {
        return StatusCode::INVALID_PASSWORD;
    }

    if (amount <= 0)
    {
        return StatusCode::INVALID_AMOUNT;
    }

    updateTransactions(amount);
    return StatusCode::SUCCESS;
}

// WITHDRAWAL   
StatusCode Account::withdraw(double amount, const string& pass)
{
    if (pass != m_password)
    {
        return StatusCode::INVALID_PASSWORD;
    }

    if (amount <= 0)
    {
        return StatusCode::INVALID_AMOUNT;
    }

    if (amount > m_balance)
    {
        return StatusCode::INSUFFICIENT_BALANCE;
    }

    updateTransactions(-amount);
    return StatusCode::SUCCESS;
}

// PRINT BALANCE
StatusCode Account::printBalance(const string& pass)
{
    if (pass != m_password)
    {
        return StatusCode::INVALID_PASSWORD;
    }

    cout << "Balance for Account Number " << m_account_number << ": $" << m_balance << endl;
    return StatusCode::SUCCESS;
}

// PRINT TRANSACTION HISTORY
StatusCode Account::printTransactionHistory(const string& pass)
{
    if (pass != m_password)
    {
        return StatusCode::INVALID_PASSWORD;
    }

    cout << "Transaction History for Account Number " << m_account_number << ":" << endl;
    for (auto it = m_transaction_history.rbegin(); it != m_transaction_history.rend(); ++it)
    {
        cout << *it << "\t";
    }
    cout << endl;
    return StatusCode::SUCCESS;
}

//BankSystem Class
bool Bank::passwordStrength(const string& pass)
{
    // minimum length
    if (pass.length() < 7)
    {
        return false;
    }

    // other conditions
    bool has_uppercase = false;
    bool has_digit = false;
    bool has_special = false;

    // checking each character
    for (char ch : pass)
    {
        if (isupper(ch))
        {
            has_uppercase = true;
        }

        if (isdigit(ch))
        {
            has_digit = true;
        }

        if (ch == '@' || ch == '#' || ch == '$' || ch == '%')
        {
            has_special = true;
        }
    }

    return has_uppercase && has_digit && has_special;
}

int Bank::getLastAccountNumber()
{
    return m_next_account_num - 1;
}

StatusCode Bank::addAccount(const string& acc_holder, const string& pass)
{
    // check strength
    if (!passwordStrength(pass))
    {
        return StatusCode::WEAK_PASSWORD;
    }

    // create new account
    Account new_account(m_next_account_num, acc_holder, pass);
    m_accounts.push_back(new_account);

    m_next_account_num++;

    return StatusCode::SUCCESS;
}

StatusCode Bank::bankDeposit(int acc_num, double amount, const string& pass)
{
    for (Account& account : m_accounts)
    {
        if (account.m_account_number == acc_num)
        {
            return account.deposit(amount, pass);
        }
    }

    return StatusCode::INVALID_ACCOUNT; // if the account isn't found
}

StatusCode Bank::bankWithdraw(int acc_num, double amount, const string& pass)
{
    for (Account& account : m_accounts)
    {
        if (account.m_account_number == acc_num)
        {
            return account.withdraw(amount, pass);
        }
    }

    return StatusCode::INVALID_ACCOUNT; // if the account isn't found
}

StatusCode Bank::balanceInquiry(int acc_num, const string& pass)
{
    for (Account& account : m_accounts)
    {
        if (account.m_account_number == acc_num)
        {
            return account.printBalance(pass);
        }
    }

    return StatusCode::INVALID_ACCOUNT; // if the account isn't found
}

StatusCode Bank::transactionHistory(int acc_num, const string& pass)
{
    for (Account& account : m_accounts)
    {
        if (account.m_account_number == acc_num)
        {
            return account.printTransactionHistory(pass);
        }
    }

    return StatusCode::INVALID_ACCOUNT; // if the account isn't found
}
