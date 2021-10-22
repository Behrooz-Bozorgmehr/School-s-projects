package ch.hevs.gdx2d.hello;

import java.util.Vector;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.math.Vector2;
import ch.hevs.gdx2d.components.bitmaps.BitmapImage;
import ch.hevs.gdx2d.lib.GdxGraphics;
import ch.hevs.gdx2d.lib.interfaces.DrawableObject;

public class Bird implements DrawableObject {
	static final float MAX_THRUST = 1f;
	// Drawing related
	protected static BitmapImage birdImage;
	// Motor related
	protected float thrustLeft = 0, thrustRight = 0;
	protected float maxPosition = 200;
	protected float thrustUp = 0;
	Vector2 position, minPosition, speed0, speedF, speed, accel;
	int background = 0;

	public Bird(Vector2 position) {
		// The spaceship image
		birdImage = new BitmapImage("data/images/oiseau1.png");
		this.position = position;
		minPosition = position;
		speed0 = new Vector2(0, 45f);
		speedF = new Vector2(0, 45f);
		speed = new Vector2(0, 0f);
		accel = new Vector2(0, -10f);
	}
	// updates elements
	public void update(float dt, Vector<Brick> bricks) {
		if (maxPosition < position.y)
			maxPosition = position.y;

		speed.y = speed.y + accel.y * dt;
		for (int i = 0; i < bricks.size(); i++) {
			if (bricks.get(i).getNumber() > 600)
				background = 1;
			if (bricks.get(i).getNumber() > 1200)
				background = 2;
			if (bricks.get(i).getNumber() > 1800)
				background = 3;
			// Are we close to a platform in the up down direction?
			boolean ballNearUpDown = Math.abs(position.y - bricks.get(i).posy) < 10;

			if (ballNearUpDown) {
				// Are we close to a platform right left ?
				boolean ballNearRightLeft = (position.x >= bricks.get(i).posx - 35)
						&& (position.x < bricks.get(i).posx + 35);
				// Are we coming from below ?
				if (ballNearRightLeft && speed.y < 0) {
					// We just bumped into a brick and we must reverse y velocity
					position.y = bricks.get(i).posy;
					if (bricks.get(i).getColor() == Color.RED) {
						speed.y = 1.8f * speed0.y;
						speedF.y = speed.y;

					} else
						speed.y = speed0.y;
					if (bricks.get(i).getColor() == Color.BROWN || bricks.get(i).getColor() == Color.YELLOW)
						bricks.removeElementAt(i);
				}
			}
		}
		// x-velocity and moves
		if (thrustLeft > 0)
			speed.x = -25f;
		if (thrustRight > 0)
			speed.x = 25f;
		if (thrustLeft == 0 && thrustRight == 0)
			speed.x = 0;
		if (position.x <= 410 && position.x >= 40)
			position.x = position.x + speed.x * dt;
		if (position.x >= 410)
			position.x = 409;
		if (position.x <= 40)
			position.x = 41;
		// new y position of the player
		position.y = position.y + speed.y * dt;
	}

	@Override
	public void draw(GdxGraphics g) {
		// Draws the ship
		g.drawTransformedPicture(position.x, position.y + 20, 0, 0.04f, birdImage);
	}

}
