package ch11;

public class TestException {

	public TestException() {

	}// end of method TestException

	public static void main(String[] args) {

		TestException testException1 = new TestException();

		try {

			testException1.testEx();

		} catch (Exception e) {

			e.printStackTrace();

		}

	}// end of method main()

	boolean testEx() throws Exception {

		boolean ret = true;

		try {

			ret = testEx1();

		} catch (Exception e) {

			System.out.println("testEx, catch exception");

			ret = false;

			throw e;

		} finally {

			System.out.println("testEx, finally; return value=" + ret);

			return ret;

		}

	}// end of method testEx

	boolean testEx1() throws Exception {

		// l:{
		boolean ret = true;

		try {

			ret = testEx2();

			if (!ret) {

				return false;

			}

			System.out.println("testEx1, at the end of try");

			return ret;

		} catch (ArithmeticException arithException) {
			System.out.println("testEx1,catch ArithmeticException");
			ret = false;
			throw arithException;
		} catch (RuntimeException runException) {
			System.out.println("testEx1,catch runtime exception");
			ret = false;
			throw runException;
		}

		catch (Exception e) {

			System.out.println("testEx1, catch exception");

			ret = false;

			throw e;

		}

		finally {

			System.out.println("testEx1, finally; return value=" + ret);
			// break l;
			return ret;

		}
		// } return true;
	}// end of method testEx1

	boolean testEx2() throws Exception {

		boolean ret = true;

		try {

			int b = 12;

			int c;

			for (int i = 2; i >= -2; i--) {

				c = b / i;

				System.out.println("i=" + i);

			}

			return true;

		} catch (Exception e) {

			System.out.println("testEx2, catch exception");

			ret = false;

			throw new ArithmeticException();

		}

		finally {

			System.out.println("testEx2, finally; return value=" + ret);

			 return ret;
			//throw new RuntimeException();

		}

	}// end of method testEx2

}
