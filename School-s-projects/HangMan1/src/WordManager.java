
public class WordManager {
		private String secretWord = "";
		String userWord = "";
		int swLength = 0;
		
		String lettre = "";
		void askSecretWord()
		{
			System.out.print("Enter your secret word: ");
			secretWord = Input.readString().toLowerCase();
			swLength = secretWord.length();
			for (int i = 0; i<swLength ; i++)
				{ userWord = userWord + "*";
				}
			//System.out.println(userWord);
		}
		
		boolean checkLetter (char c)
		{	String word = "";
			int result = 0;
			for (int i = 0; i<swLength; i++)
			{	
				if (c == secretWord.charAt(i) || c == secretWord.toUpperCase().charAt(i))
				{	word = word + c;
					
					result = 1;					
				}
				else 
				{	
				word = word + userWord.charAt(i);
				}
			}
			userWord = word.toLowerCase();
			
			
			return  (result == 1) ? true: false;
		}
		
		boolean isWordComplete()
		{	
			return (userWord.equals(secretWord))? true: false;
			
		}
}
