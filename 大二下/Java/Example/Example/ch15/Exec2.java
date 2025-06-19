package ch15;

public class Exec2 {
	public static void main(String[] args) {
		try {
			Process p = Runtime
					.getRuntime()
					.exec(
							"F:\\Program Files\\Microsoft Office\\OFFICE11\\winword.exe e:\\test.doc");
			p.waitFor();
		} catch (Exception e) {
		}
	}
}
