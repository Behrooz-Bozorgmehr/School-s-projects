package ch.hevs.gdx2d.hello;

import com.badlogic.gdx.math.Vector2;
import ch.hevs.gdx2d.components.bitmaps.BitmapImage;
import ch.hevs.gdx2d.lib.GdxGraphics;
import ch.hevs.gdx2d.lib.interfaces.DrawableObject;

public class Enemy implements DrawableObject {
	//define related
	float positionX, positionY;
	static BitmapImage image;
	static int counter =0;
	//moves related
	Vector2 speed,  speedBullet;
	Vector2 bird;
	Bullet b;
	protected float thrustUp = 0;
	//elimination related
	boolean collision;
	boolean explosion;

	public Enemy(float x, float y) {
		this.positionX = x;
		this.positionY = y;
		image = new BitmapImage("data/images/spider.png");
		counter++;
		speed = new Vector2(10,0);
		speedBullet = new Vector2(0, 100);
	}//Update positions of elements mobile of the game
	public void update(float dt) {
		//enemy's position
		if (positionX <= 40 || positionX >= 410) {
			speed.x = -1 * speed.x;
		}
		positionX = positionX + (int) (speed.x * dt);
		// condition for eliminating of player
		collision = Math.sqrt(Math.pow(positionX - bird.x, 2) + Math.pow(positionY - bird.y, 2)) < 20 ? true : false;
		// bullet trajectory
		if (thrustUp > 0) {
			b.posY = b.posY + speedBullet.y*dt;
			// condition for eliminating of enemy
			explosion = (Math.sqrt(Math.pow(positionX - b.posX, 2) + Math.pow(positionY - b.posY, 2))) < 20 ? true
					: false;
			if (explosion) {
				positionY = -100;
			}
		}
	}
	@Override
	public void draw(GdxGraphics g) {
		// draw enemy and bullet
		g.drawTransformedPicture(positionX, positionY, 0, 0.2f, image);
		if (thrustUp > 0) {
			b.draw(g);
		}
	}
}
