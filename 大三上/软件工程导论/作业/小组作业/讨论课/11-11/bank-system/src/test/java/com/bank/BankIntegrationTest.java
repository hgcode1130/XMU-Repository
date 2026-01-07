package com.bank;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import static org.junit.jupiter.api.Assertions.*;

public class BankIntegrationTest {

    private Bank bank;
    private Atm atm;
    private Cashier cashier;
    private final String testAccountNumber = "1122334455";
    private final String testPin = "9876";
    private final double initialBalance = 1500.0;

    @BeforeEach
    void setUp() {
        bank = new Bank();
        bank.createAccount(testAccountNumber, testPin, initialBalance, "debit", 0);
        atm = new Atm(bank);
        cashier = new Cashier(bank);
        
        // 预先插入卡并验证PIN，为多个测试做准备
        atm.insertCard(testAccountNumber);
        atm.enterPin(testPin);
    }

    @ParameterizedTest
    @CsvSource({
            "500.0, 1000.0, successful",  // 成功取款
            "2000.0, 1500.0, failed",      // 余额不足
            "0.0, 1500.0, successful",   // 取款为零
            "-100.0, 1500.0, failed"       // 取款为负数
    })
    void testWithdrawal_Parameterized(double withdrawalAmount, double expectedBalance, String expectedResult) {
        // 执行取款
        String withdrawResponse = atm.withdraw(withdrawalAmount);
        
        // 验证响应消息
        assertTrue(withdrawResponse.contains(expectedResult), "Response message should indicate " + expectedResult);
        
        // 验证账户余额
        assertEquals(expectedBalance, bank.findAccount(testAccountNumber).getBalance(), "Balance should be correct after operation.");
    }

    @Test
    void testOperationFailWithInvalidPin() {
        // 创建一个新的ATM会话来测试无效PIN
        Atm freshAtm = new Atm(bank);
        freshAtm.insertCard(testAccountNumber);
        String pinResponse = freshAtm.enterPin("0000"); // 错误的 PIN
        assertTrue(pinResponse.contains("Invalid PIN"), "Response should indicate an invalid PIN.");

        String withdrawResponse = freshAtm.withdraw(100.0);
        assertTrue(withdrawResponse.contains("PIN not verified"), "Withdrawal should be blocked if PIN is not verified.");
    }

    @Test
    void testSuccessfulDeposit() {
        double depositAmount = 300.0;
        String depositResponse = atm.deposit(depositAmount);
        assertTrue(depositResponse.contains("successful"), "Deposit should be successful.");

        double expectedBalance = initialBalance + depositAmount;
        assertEquals(expectedBalance, bank.findAccount(testAccountNumber).getBalance(), "Balance should be updated correctly after deposit.");
    }

    @Test
    void testCashierOpensAccount() {
        String newAccountNumber = "9988776655";
        String newPin = "5555";
        double initialDeposit = 50.0;

        cashier.openAccount(newAccountNumber, newPin, initialDeposit, "debit", 0);

        Account newAccount = bank.findAccount(newAccountNumber);
        assertNotNull(newAccount, "The new account should exist in the bank.");

        assertEquals(initialDeposit, newAccount.getBalance());
        assertTrue(newAccount.verifyPin(newPin));
    }

    @Test
    void testAccountInfoQuery() {
        String accountInfo = atm.getAccountStatus();
        assertNotNull(accountInfo, "Account info should not be null.");
        assertTrue(accountInfo.contains("Account Number: " + testAccountNumber), "Account info should contain the correct account number.");
        assertTrue(accountInfo.contains("Balance: 1500.0"), "Account info should contain the correct balance.");
    }
}
