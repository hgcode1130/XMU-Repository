package com.bank;

public class Account {
    private String accountNumber;
    private String pin;
    private double balance;
    private String accountType;
    private double creditLimit;

    public Account(String accountNumber, String pin, double initialDeposit, String accountType, double creditLimit) {
        this.accountNumber = accountNumber;
        this.pin = pin;
        this.balance = initialDeposit;
        this.accountType = accountType;
        this.creditLimit = creditLimit;
    }

    public boolean verifyPin(String pinToVerify) {
        return this.pin.equals(pinToVerify);
    }

    public void deposit(double amount) {
        if (amount > 0) {
            this.balance += amount;
        }
    }

    public boolean withdraw(double amount) {
        if (amount >= 0 && this.balance >= amount) {
            this.balance -= amount;
            return true;
        } else if (this.accountType.equals("credit") && (this.balance + this.creditLimit) >= amount) {
            // Logic for credit accounts
            this.balance -= amount;
            return true;
        }
        return false;
    }

    public double getBalance() {
        return this.balance;
    }

    public String getAccountNumber() {
        return this.accountNumber;
    }

    public String getAccountType() {
        return this.accountType;
    }

    public double getCreditLimit() {
        return this.creditLimit;
    }

    public void close() {
        // In a real system, might involve archiving or other cleanup
        System.out.println("Account " + this.accountNumber + " is marked for closure.");
    }
}
