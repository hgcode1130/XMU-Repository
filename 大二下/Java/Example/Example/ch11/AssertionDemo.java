package ch11;


public class AssertionDemo {
	public static void main(String args[]){
		int i; 
		int sum = 0; 
		for(i = 0; i < 10; i++){
			sum += i;
		}
//		assert i != 10;
//		assert sum > 10 && sum < 5 * 10 : "sum is " + sum;
	
		try{
			assert i != 10;
			assert sum > 10 && sum < 5 * 10 : "sum is " + sum;
			
		}
		catch(AssertionError error){
			System.out.println("error");
		}
		System.out.println("continue...");
		
	}

}
