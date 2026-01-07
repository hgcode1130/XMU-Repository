package com.bank;

import java.util.Scanner;

public class AtmUserInterface {
    private Atm atm;
    private Scanner scanner;

    public AtmUserInterface(Atm atm) {
        this.atm = atm;
        this.scanner = new Scanner(System.in);
    }

    public void start() {
        System.out.println("Welcome to the ATM!");

        while (true) {
            System.out.println("\nPlease insert your card (enter card number):");
            String cardNum = scanner.nextLine();
            String response = atm.insertCard(cardNum);
            System.out.println(response);

            if (response.contains("accepted")) {
                handleCardSession();
            }

            System.out.println("\nDo you want to perform another transaction? (yes/no)");
            if (!scanner.nextLine().equalsIgnoreCase("yes")) {
                break;
            }
        }
        System.out.println("Thank you for using the ATM. Goodbye!");
    }

    private void handleCardSession() {
        while (true) {
            System.out.println("\nPlease enter your PIN:");
            String pin = scanner.nextLine();
            String response = atm.enterPin(pin);
            System.out.println(response);

            if (response.contains("successfully")) {
                handlePinSession();
                break;
            } else {
                System.out.println("Would you like to try entering your PIN again? (yes/no)");
                if (!scanner.nextLine().equalsIgnoreCase("yes")) {
                    atm.terminateSession();
                    break;
                }
            }
        }
    }

    private void handlePinSession() {
        while (true) {
            printMenu();
            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    handleWithdraw();
                    break;
                case "2":
                    handleDeposit();
                    break;
                case "3":
                    handleAccountStatus();
                    break;
                case "4":
                    atm.terminateSession();
                    System.out.println("Session ended.");
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void printMenu() {
        System.out.println("\n--- ATM Menu ---");
        System.out.println("1. Withdraw");
        System.out.println("2. Deposit");
        System.out.println("3. Check Account Status");
        System.out.println("4. Exit");
        System.out.print("Your choice: ");
    }

    private void handleWithdraw() {
        System.out.print("Enter amount to withdraw: ");
        try {
            double amount = Double.parseDouble(scanner.nextLine());
            String response = atm.withdraw(amount);
            System.out.println(response);
        } catch (NumberFormatException e) {
            System.out.println("Invalid amount format.");
        }
    }



    private void handleDeposit() {
        System.out.print("Enter amount to deposit: ");
        try {
            double amount = Double.parseDouble(scanner.nextLine());
            String response = atm.deposit(amount);
            System.out.println(response);
        } catch (NumberFormatException e) {
            System.out.println("Invalid amount format.");
        }
    }

    private void handleAccountStatus() {
        String status = atm.getAccountStatus();
        System.out.println("\n--- Account Status ---");
        System.out.println(status);
        System.out.println("--------------------");
    }

    public static void main(String[] args) {
        Bank bank = new Bank();
        // Pre-load an account for testing
        bank.createAccount("123456789", "1234", 1000.0, "debit", 0);

        Atm atm = new Atm(bank);
        AtmUserInterface ui = new AtmUserInterface(atm);
        ui.start();
    }
}
