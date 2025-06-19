package ch11;

public class ReturnFinallyTest {

	public static void main(String[] args) {
		ReturnFinallyTest e = new ReturnFinallyTest();
		System.out.println(e.tryThis());
	}

	public int tryThis() {
		try {
			System.out.println("1");
			throw new Exception();
			// return 1;//Unreachable code
		} catch (Exception ex) {
			System.out.println("2");
			return 2;//
		} finally {
			System.out.println("4");
		//	return 3;
		}
	}
}
