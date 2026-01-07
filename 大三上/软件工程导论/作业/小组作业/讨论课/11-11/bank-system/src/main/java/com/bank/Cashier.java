package com.bank;

public class Cashier {
    private Bank bank;

    public Cashier(Bank bank) {
        this.bank = bank;
    }

    public Account openAccount(String accountNumber, String pin, double initialDeposit, String accountType, double creditLimit) {
        return bank.createAccount(accountNumber, pin, initialDeposit, accountType, creditLimit);
    }

    public boolean authorizeCard(String accountNumber) {
        return bank.authorizeCard(accountNumber);
    }

    public void deauthorizeCard(String accountNumber) {
        // In a real system, this might mean flagging the card as inactive
        System.out.println("Card for account " + accountNumber + " has been deauthorized by cashier.");
    }

    public void closeAccount(String accountNumber) {
        bank.closeAccount(accountNumber);
    }
}
