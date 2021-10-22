package ch.hevs.gdx2d.hello;

import com.badlogic.gdx.graphics.Color;
import ch.hevs.gdx2d.lib.GdxGraphics;
import ch.hevs.gdx2d.lib.interfaces.DrawableObject;

public class Bullet implements DrawableObject{	
		// define related
		float posX;
		float posY;
	Bullet(float x, float y){
		this.posX = x;
		this.posY = y;
	}
	//draw circular bullets
	public void draw(GdxGraphics g) {
		g.drawFilledCircle(posX, posY, 5, Color.YELLOW);
	}
}
