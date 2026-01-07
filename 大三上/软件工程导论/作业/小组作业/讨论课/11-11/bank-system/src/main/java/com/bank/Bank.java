package com.bank;

import java.util.HashMap;
import java.util.Map;

public class Bank {
    private Map<String, Account> accounts;

    public Bank() {
        this.accounts = new HashMap<>();
    }

    public Account createAccount(String accountNumber, String pin, double initialDeposit, String accountType, double creditLimit) {
        if (!accounts.containsKey(accountNumber)) {
            Account newAccount = new Account(accountNumber, pin, initialDeposit, accountType, creditLimit);
            accounts.put(accountNumber, newAccount);
            return newAccount;
        }
        return null; // Account already exists
    }

    public Account findAccount(String accountNumber) {
        return accounts.get(accountNumber);
    }

    public boolean verifyPin(String accountNumber, String pin) {
        Account account = findAccount(accountNumber);
        if (account != null) {
            return account.verifyPin(pin);
        }
        return false;
    }

    public void deposit(String accountNumber, double amount) {
        Account account = findAccount(accountNumber);
        if (account != null) {
            account.deposit(amount);
        }
    }

    public boolean withdraw(String accountNumber, double amount) {
        Account account = findAccount(accountNumber);
        if (account != null) {
            return account.withdraw(amount);
        }
        return false;
    }

    public String getAccountInfo(String accountNumber) {
        Account account = findAccount(accountNumber);
        if (account != null) {
            return "Account Number: " + account.getAccountNumber() + "\n" +
                   "Account Type: " + account.getAccountType() + "\n" +
                   "Balance: " + account.getBalance() + "\n" +
                   "Credit Limit: " + account.getCreditLimit();
        }
        return "Account not found.";
    }

    public void closeAccount(String accountNumber) {
        Account account = findAccount(accountNumber);
        if (account != null) {
            account.close();
            accounts.remove(accountNumber);
        }
    }

    public boolean authorizeCard(String accountNumber) {
        // In a real system, this would involve more complex checks
        return accounts.containsKey(accountNumber);
    }
}
