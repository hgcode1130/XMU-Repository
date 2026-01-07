package com.bank;

public class Atm {
    private Bank bank;
    private String currentAccountNumber;
    private boolean pinVerified;

    public Atm(Bank bank) {
        this.bank = bank;
        this.pinVerified = false;
    }

    // Returns a status message
    public String insertCard(String cardNumber) {
        if (bank.authorizeCard(cardNumber)) {
            this.currentAccountNumber = cardNumber;
            this.pinVerified = false; // Reset PIN verification for new card
            return "Card accepted. Please enter your PIN.";
        } else {
            return "Card not authorized.";
        }
    }

    // Returns a status message
    public String enterPin(String pin) {
        if (this.currentAccountNumber == null) {
            return "Please insert your card first.";
        }
        if (bank.verifyPin(this.currentAccountNumber, pin)) {
            this.pinVerified = true;
            return "PIN verified successfully.";
        } else {
            this.pinVerified = false;
            return "Invalid PIN.";
        }
    }

    // Returns a status message
    public String deposit(double amount) {
        if (!pinVerified) {
            return "PIN not verified. Please verify your PIN.";
        }
        bank.deposit(this.currentAccountNumber, amount);
        return "Deposit successful. New balance: " + bank.findAccount(currentAccountNumber).getBalance();
    }

    // Returns a status message
    public String withdraw(double amount) {
        if (!pinVerified) {
            return "PIN not verified. Please verify your PIN.";
        }
        if (bank.withdraw(this.currentAccountNumber, amount)) {
            return "Withdrawal successful. Please take your cash. New balance: " + bank.findAccount(currentAccountNumber).getBalance();
        } else {
            return "Withdrawal failed. Insufficient funds or invalid amount.";
        }
    }

    public String getAccountStatus() {
        if (!pinVerified) {
            return "PIN not verified. Please verify your PIN.";
        }
        return bank.getAccountInfo(this.currentAccountNumber);
    }

    public void terminateSession() {
        this.currentAccountNumber = null;
        this.pinVerified = false;
        System.out.println("Session terminated. Please take your card.");
    }


}
