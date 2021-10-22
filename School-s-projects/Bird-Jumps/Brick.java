package ch.hevs.gdx2d.hello;

import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.math.Vector2;
import ch.hevs.gdx2d.lib.GdxGraphics;
import ch.hevs.gdx2d.lib.interfaces.DrawableObject;

public class Brick implements DrawableObject {
	//define related
	public int posx, posy;
	static int counter = 0;
	Color c = Color.GREEN;
	// brick position and color
	public Brick(int x, int y) {
		posx = x;
		posy = y;
		counter++;
		if ( counter%5==0)
			c = Color.RED;
		if ( counter%3==0)
			c= Color.YELLOW;
		if ( counter%7==0)
			c= Color.BROWN;
	}
	@Override
	public void draw(GdxGraphics g) {
		//draw brick
		g.drawFilledRectangle(posx, posy, 70, 15, 0, c);
	}
	//get brick position
	public Vector2 getPosition() {
	Vector2 position = new Vector2(posx, posy);
	return position;
	}
	//get brick color
	public Color getColor() {
		return c;
	}
	//get brick number
	public int getNumber() {
		return counter;
		}
	
}
