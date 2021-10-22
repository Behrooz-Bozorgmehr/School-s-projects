import java.awt.Color;

import hevs.graphics.FunGraphics;

public class HangMan {
	final int MAX_STEPS = 8;
	int current_step = 0;
	
	
	
	
	WordManager w1 = new WordManager();
	char c = 0;
	String replay_p = "";
	
	boolean play()
	{	
		while (current_step < MAX_STEPS && w1.isWordComplete() == false)
		{	System.out.print("Enter your guess: ");
			c = Input.readChar();
			if (w1.checkLetter(c)== false)
			{	System.out.println(w1.userWord);
				current_step++;
			}
			if (w1.checkLetter(c))
			{	System.out.println(w1.userWord);
				System.out.println("WIN! WIN! WIN!");
			//	break;
			}
			 
			
		}
			replay();
		return (current_step == MAX_STEPS) ? true : false;
	}
	
	boolean replay()
	{if ( (current_step == MAX_STEPS)|| (w1.checkLetter(c)))
		{	 if (current_step == MAX_STEPS)
			{System.out.print(("You lost this party! Do you want to replay? if Yes write 'y': "));
			}
			if (w1.checkLetter(c))
		 	{System.out.print(("Do you want to replay? if Yes write 'y': "));
			}
		 replay_p = Input.readString();
		 replay_p.toLowerCase();
		 if (replay_p.equals("y"))
		 {	current_step = 0;	
		 	w1.userWord = "";
		 	w1.askSecretWord();
			play();
		 }
		 else
		 {
			 System.out.println("Thank you for your participation! Hope to see you soon!");
		 }

	 }
	return (replay_p == "y")? true : false;
	}
	
	void updateGraphicsView()
	{
		final int WIDTH = 300;
		final int HEIGHT = 300;

		// Create and set the windows up
		FunGraphics display = new FunGraphics(WIDTH, HEIGHT);

		//Set the drawing color to black
		display.setColor(Color.white);
		display.setPixel(200, 200,  Color.white);
		
		if (w1.checkLetter(c)== false)
		{
			switch (current_step)
			{ case 1:
				for (int i = 210; i > 190; i--) 
				{	for ( int k = 110 ; k < 130; k++)
					{display.setPixel(k, i, Color.black );
					}
					for ( int j = 130 ; j > 110; j++)
					{display.setPixel(j, i, Color.black );
					}
				}
				break;
				
			case 2:
				for (int i = 190; i > 100; i--) 
				{	
					display.setPixel(120, i, Color.black );
					
				}
				break;
			case 3:
				for (int i = 120; i < 180; i++) 
				{	
					display.setPixel(i, 100, Color.black );
					
				}
				break;
			case 4:
				for (int i = 110; i > 100; i--) 
				{	
					display.setPixel(180, i, Color.black );
					
				}
				break;
			case 5:
				int k = 181;
				int m = 180;
				for (int i = 110; i < 130; i++) 
				{	if ( i >= 110 && i <= 120)
					{	k--;
						m++;
					display.setPixel(k, i, Color.black );
					display.setPixel(m, i, Color.black);
					}
					if ( i >= 120 && i <= 130) 
					{ 	k++;
						m--;
						display.setPixel(k, i, Color.black);
						display.setPixel(m, i, Color.black);
					}
					
				}
			}
		}
		
		
		
	}
	
	
	
	
	
	public static void main(String args[])
	{	
		HangMan H1 = new HangMan();
		HangMan FunGraphics = new HangMan();
		FunGraphics.updateGraphicsView();
		H1.w1.askSecretWord();
		H1.play();
		
		
	}

}
