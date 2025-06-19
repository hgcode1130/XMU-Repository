package ch14;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class NewMatcherTest {
public static void main(String[] args) {
	 Pattern p = Pattern.compile("cat");
	 Matcher m = p.matcher("one cat two cats in the yard");
	 StringBuffer strb = new StringBuffer();
	 while (m.find()) {
	     m.appendReplacement(strb, "dog");
	 }
	 m.appendTail(strb);
	 System.out.println(strb.toString());
	}
}
