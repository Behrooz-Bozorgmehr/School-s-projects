import java.awt.Color;

import hevs.graphics.FunGraphics;

public class HangMan1 {
	final int MAX_STEPS = 8;
	int current_step = 0;
	
	FunGraphics display = new FunGraphics(300, 300);

		
	WordManager w1 = new WordManager();
	char c = 0;
	String replay_p = "";
	
	boolean play()
	{	
	
		while (current_step < MAX_STEPS && w1.isWordComplete() == false)
		{	System.out.println(w1.userWord);
			System.out.print("Enter your guess: ");
			c = Input.readChar();
			if (w1.checkLetter(c)== false)
			{	current_step++;
				
			}
			updateGraphicsView();
		}	
			if (w1.isWordComplete() == true)
			{	
				System.out.println("WIN! WIN! WIN!");
			}
			System.out.println(w1.userWord);
			
			replay();
		return (current_step == MAX_STEPS) ? true : false;
	}
	
	boolean replay()
	{	if ( (current_step == MAX_STEPS)|| (w1.checkLetter(c)))
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
	{		String text = "word : ";
			display.clear();
			display.drawString(20, 60, text + w1.userWord, Color.blue, 20);
		
		
			
			 if (current_step >= 1)
				{	display.drawLine(110, 210, 120, 190);
					display.drawLine(130, 210, 120, 190);
				}
			 if (current_step >= 2)
				display.drawLine(120, 190, 120, 100);
				
			 if (current_step >= 3)
				display.drawLine(120, 100, 180, 100);
				
			 if (current_step >= 4)
				display.drawLine(180, 100, 180, 110);
				
			if (current_step >= 5)
				display.drawCircle(170, 110, 20);
			
			if (current_step >= 6)
				display.drawLine(180, 170, 180, 130);	
				
			if (current_step >= 7)
				{	display.drawLine(170, 190, 180, 170);	
					display.drawLine(190, 190, 180, 170);	
				}
			if (current_step == 8)
				display.drawLine(170, 150, 190, 150);	
				
				
			
		}
		
	public static void main(String args[])
	{	
		HangMan1 H1 = new HangMan1();
		H1.w1.askSecretWord();
		H1.play();
		
		
	}

}
