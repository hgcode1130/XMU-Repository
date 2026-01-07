package com.bank;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class AccountTest {

    private Account account;
    private final String correctPin = "1234";

    @BeforeEach
    void setUp() {
        // 在每个测试前创建一个新的账户实例
        account = new Account("123456789", correctPin, 1000.0, "debit", 0);
    }

    @Test
    void testVerifyPin_CorrectPin() {
        assertTrue(account.verifyPin(correctPin), "PIN should be verified successfully with the correct PIN.");
    }

    @Test
    void testVerifyPin_IncorrectPin() {
        assertFalse(account.verifyPin("9999"), "PIN verification should fail with an incorrect PIN.");
    }

    @ParameterizedTest
    @CsvSource({
            "500.0, 1500.0",  // 正数金额
            "0.0, 1000.0",    // 零金额
            "-100.0, 1000.0"  // 负数金额 (假设业务逻辑不允许负数存款，余额不变)
    })
    void testDeposit_Parameterized(double depositAmount, double expectedBalance) {
        account.deposit(depositAmount);
        assertEquals(expectedBalance, account.getBalance(), "Balance should be updated correctly after deposit of " + depositAmount);
    }

    @ParameterizedTest
    @CsvSource({
            "500.0, 500.0, true",    // 成功取款
            "1000.0, 0.0, true",     // 取出全部余额
            "1500.0, 1000.0, false", // 余额不足
            "0.0, 1000.0, true",     // 取款为零
            "-100.0, 1000.0, false"  // 取款为负数
    })
    void testWithdraw_Parameterized(double withdrawAmount, double expectedBalance, boolean expectedResult) {
        boolean result = account.withdraw(withdrawAmount);
        assertEquals(expectedResult, result, "Withdrawal result for amount " + withdrawAmount + " should be " + expectedResult);
        assertEquals(expectedBalance, account.getBalance(), "Balance after withdrawing " + withdrawAmount + " should be " + expectedBalance);
    }
}
