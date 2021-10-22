import hevs.graphics.*;
//import hevs.graphics.FunGraphics;
import java.awt.Color;
import java.awt.event.KeyEvent;
import java.awt.event.KeyAdapter ;
public class Coulisse4 {
	// creation of table and defining variables
	static int[][] grille = new int[6][7];
	static boolean[] fullC = new boolean[7];
	static int row = 6;
	static int column;
	static int inCol;
	public static int Nbrmove = 1;
	boolean winner = false;
	static String replayAnswer = ""; 
	static FunGraphics display = new FunGraphics(610, 600, 1100, 300, "PUISSANCE 4", true);
	
	
	Coulisse4() {		
		for (int i = 0; i < 6; i++) 
		{	for (int j = 0; j < 7; j++) 
			{	grille[i][j] = 0;
				fullC[j] = false;
			}
		}
	}

	// defining player turn
	public static boolean player() {
		boolean player1 = false;
		if ((Nbrmove % 2) == 1)
		{	player1 = true;
		}
		return player1;
	}

	// controling input value
	public static int askPlayer() {
		display.setColor(Color.blue);
		display.drawFillRect(0, 530, 610, 70);	
		display.drawString(10, 560, "Choose a column : "  , Color.white, 20);
		if (player()==true) 
		{	System.out.println("Player1 : " + "select a column");
		}
		if (player()== false)
		{	System.out.println("Player2 : " + "select a column");
		}
		inCol = Input.readInt();
		while (inCol < 1 || inCol > 7) 
		{	display.setColor(Color.blue);
			display.drawFillRect(0, 530, 610, 70);	
			display.drawString(10,550, "Not a valid column!",Color.white,20);
			display.drawString(10,570, "select a valid column",Color.white,20);
			System.out.println("Not a valid column!");
			System.out.println("select a column");
			inCol = Input.readInt();	
			while (inCol<8 && fullC[inCol - 1]) 
			{	display.setColor(Color.blue);
				display.drawFillRect(0, 530, 610, 70);	
				display.drawString(10,560, "This column is full. Choose another column.",Color.white,20);
				System.out.println("This column is full. Choose another column.");
				inCol = Input.readInt();
			}	
		}	
		while (inCol<8 && fullC[inCol - 1]) 
		{	display.setColor(Color.blue);
			display.drawFillRect(0, 530, 610, 70);	
			display.drawString(10,560, "This column is full. Choose another column.",Color.white,20);
			System.out.println("This column is full. Choose another column.");
			inCol = Input.readInt();
		}	
		column = inCol - 1;
		return column;
	}
	
	public static int checkCase() {
		for (int i = 5; i >= 0; i--) 
		{	if (grille[i][column] == 0) 
			{	row = i;
				i = 0;
			} 
			else
				continue;
		}
		return row;
	}
	// defining positions of players' pieces
	public static int[][] placeJetton() {
		askPlayer();
		checkCase();
		boolean condition = player();
		if (condition == true && fullC[column] == false) 
		{	grille[row][column] = 1;
		}
		if (condition == false && fullC[column] == false) 
		{	grille[row][column] = 2;
		}
		return grille;
	}
	// output values on console mode
	public static String playerSymboletoString() {
		String s = "\t";
		
		{	for (int i = 0; i < 6; i++)
			{	for (int j = 0; j < 7; j++)
				{	
						if (grille[i][j] == 0)
						{	s += "[]" + "   ";
						}
						if (grille[i][j] == 1)
						{	s += " X" + "   ";
						}
						if (grille[i][j] == 2) 
						{	s += " O" + "   ";
						}
						
				}
				s = s + "\n" + "\t";
			}
		}
		return s;
	}
	// checking for winner and end of the game
	public static boolean win() {
		boolean winner = false;
		for (int i = 0; i < 6; i++) 
		{	for (int j = 0; j < 7; j++) 
			{	if (grille[i][j] != 0 && j < 4)
				{	if ((grille[i][j] == grille[i][j + 1]) && (grille[i][j] == grille[i][j + 2])
							&& (grille[i][j] == grille[i][j + 3])) 
					{	display.setColor(Color.blue);
						display.drawFillRect(0, 530, 610, 70);
						if (grille[i][j]== 1)
						{	System.out.println("Game Over\n" + "Player1, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player1, You are the winner!",Color.white,20);
						} 
						if (grille[i][j]== 2)
						{	System.out.println("Game Over\n" + "Player2, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player2, You are the winner!",Color.white,20);
						}
						winner = true;
					}
				}
				if (grille[i][j] != 0 && i < 3) 
				{	if ((grille[i][j] == grille[i + 1][j]) && (grille[i][j] == grille[i + 2][j])
							&& (grille[i][j] == grille[i + 3][j])) 
					{	display.setColor(Color.blue);
						display.drawFillRect(0, 530, 610, 70);
						if (grille[i][j]== 1)
						{	System.out.println("Game Over:\n" + "Player1, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player1, You are the winner!",Color.white,20);
						} 
						if (grille[i][j]== 2) 
						{	System.out.println("Game Over:\n" + "Player2, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player2, You are the winner!",Color.white,20);
						}
						winner = true;
					}
				}
			
				if (grille[i][j] != 0 && i < 3 && j < 4) 
				{	if ((grille[i][j] == grille[i + 1][j + 1]) && (grille[i][j] == grille[i + 2][j + 2])
							&& (grille[i][j] == grille[i + 3][j + 3]))
					{	display.setColor(Color.blue);
						display.drawFillRect(0, 530, 610, 70);
						if (grille[i][j]== 1) 
						{	System.out.println("Game Over\n" + "Player1, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player1, You are the winner!",Color.white,20);
						}
						if (grille[i][j]== 2)
						{	System.out.println("Game Over\n" + "Player2, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player1, You are the winner!",Color.white,20);
						}
						winner = true;
					}
				}
				if (grille[i][j] != 0 && j > 2 && i < 3) 
				{	if ((grille[i][j] == grille[i + 1][j - 1]) && (grille[i][j] == grille[i + 2][j - 2])
							&& (grille[i][j] == grille[i + 3][j - 3])) 
					{	display.setColor(Color.blue);
						display.drawFillRect(0, 530, 610, 70);	
						if (grille[i][j]== 1)  
						{	System.out.println("Game Over\n" + "Player1, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player1, You are the winner!",Color.white,20);
						}
						if (grille[i][j]== 2)
						{	System.out.println("Game Over\n" + "Player2, You are the winner!");
							display.drawString(10,560, "Game Over\n" + "Player1, You are the winner!",Color.white,20);
						}
						winner = true;
					}
				}
			}
		}
		return winner;
	}
	// graphic mode 
	public static void gameFrame() {
		int partie = 1;
		do
		{	display.setColor(Color.white);
			for (int l = 0; l < 610; l++)
			{	for (int k = 0; k < 600; k++) 
				{	display.setPixel(l, k, Color.BLUE);
				}
			}
			display.drawString(10, 20, "Partie :" + partie++, Color.white, 20);
			replayAnswer = "";
			int x = 2 ;
			for (int i = 0; i < 6; i++) 
			{	for (int j = 0; j < 7; j++)
				{	display.drawFilledCircle((j + 1) * 30 + 50 * j, (i + 1) * 30 + 50 * i, 75);
				}
				display.drawString(65, 525 ,"" + 1 , Color.red, 20);
				display.drawString((i+1)*79+65, 525, ""+((int)(x++)), Color.red, 20);
				display.drawString((1)*79+65, 525, ""+((int)(2)), Color.yellow, 20);
				display.drawString((3)*79+65, 525, ""+((int)(4)), Color.yellow, 20);
				display.drawString((5)*79+65, 525, ""+((int)(6)), Color.yellow, 20);
			}
			play();
			
			replay();
		}while(replayAnswer.equalsIgnoreCase("yes"));

	}
	// combination of the functions for both mode graphic and console
	public static void play() {
		for (int i = 0; i < 6; i++) 
		{	for (int j = 0; j < 7; j++) 
			{	grille[i][j] = 0;
				fullC[j]= false;
			}
		}
		int jouer = 1;
		for (int k = 1; k < 43; k++) 
		{	if ( k%2==0)
			{	jouer =2;
				display.drawString(520, 20, "player " + jouer , Color.red, 20);
			}
			if ( k%2==1)
			{	jouer =1;
				display.drawString(520, 20, "player " + jouer , Color.yellow, 20);
			}
			
			placeJetton();
			System.out.println(playerSymboletoString());
			System.out.println(Nbrmove);
			Nbrmove = k + 1;
			if (row == 0) 
			{	fullC[column] = true;
			}
			for (int i = 0; i < 6; i++) 
			{	for (int j = 0; j < 7; j++)
				{	if (grille[i][j] == 0) 
					{	display.setColor(Color.white);
						display.drawFilledCircle((j + 1) * 30 + 50 * j, (i + 1) * 30 + 50 * i, 75);
					}
					if (grille[i][j] == 1)
					{	display.setColor(Color.yellow);
						display.drawFilledCircle((j + 1) * 30 + 50 * j, (i + 1) * 30 + 50 * i, 75);
					}
					if (grille[i][j] == 2)
					{	display.setColor(Color.red);
						display.drawFilledCircle((j + 1) * 30 + 50 * j, (i + 1) * 30 + 50 * i, 75);
					}
				}
			}
			if (win())
			{	break;
			}
			display.drawString(520, 20, "player " + jouer + ": ", Color.blue, 20);
		}
		
	}
	
	//asking for replay or announcing end of the game
	public static void replay() {
		if (!win())
		{	System.out.println("This partie has no winner.");
		}
		System.out.println("Would you like to replay? yes or no ?");
		boolean y = true;
		while (y) 
		{	String s = Input.readString();
			replayAnswer = s;
			if (s.equalsIgnoreCase("yes")) {
				Nbrmove = 1;
				break;

			}
			if (s.equalsIgnoreCase("no")) {
				System.out.println("Thank you for playing. bye bye");
				break;
			} else
				System.out.println("I SAID 'YES' OR 'NO' !");
			continue;
		}
	}
	
	
	public static void main(String[] args) {
		gameFrame();
		
	}

}
