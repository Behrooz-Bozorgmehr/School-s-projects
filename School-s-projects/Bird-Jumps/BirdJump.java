package ch.hevs.gdx2d.hello;

import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.util.Random;
import java.util.Vector;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.math.Vector2;
import ch.hevs.gdx2d.components.audio.MusicPlayer;
import ch.hevs.gdx2d.components.bitmaps.BitmapImage;
import ch.hevs.gdx2d.desktop.PortableApplication;
import ch.hevs.gdx2d.lib.GdxGraphics;
import ch.hevs.gdx2d.lib.interfaces.DrawableObject;

public class BirdJump extends PortableApplication {
	// Modify window size
	public BirdJump() {
		super(450, 800);
	}
	// create related to moving up
	Vector<Brick> bricks = new Vector<Brick>();
	int max = 250;
	Random r = new Random(max);

	// create mobile character
	Bird bird1;
	Vector<Enemy> enemy = new Vector<Enemy>();
	// create images
	BitmapImage image;
	BitmapImage image1;
	BitmapImage[] images = new BitmapImage[5];
	int imageNo =0;
	// related to run/stop the game
	boolean begin = false;
	boolean escape = false;
	boolean space = false;
	// related to music
	private MusicPlayer[] music = new MusicPlayer[5];
	int track = 0;

	// related to scores
	int score = 0;
	Vector<Records> rankings = new Vector<Records>();
	TextField textBox = new TextField(20);

	// method for testing
	protected void createSingleBrick(int x, int y) {
		bricks.add(new Brick(x, y));
	}

	// create steps for moving up
	protected void createBricks(int x, int y) {
		bricks.add(new Brick(x, y));
		bricks.get(0).c = Color.GREEN;
		for (int i = 0; i < 300; i++) {
			y += 50;
			bricks.add(new Brick(40 + r.nextInt(150), y + 50));
			bricks.add(new Brick(r.nextInt(180) + 225, y));
		}
		for (int i = 0; i < 300; i++) {
			y += 75;
			bricks.add(new Brick(80 + r.nextInt(300), y));
			if (i % 3 == 1)
				bricks.add(new Brick(r.nextInt(180) + 225, y + 25));
		}
		for (int i = 0; i < 300; i++) {
			y += 100;
			bricks.add(new Brick(80 + r.nextInt(300), y + 20));
			if (i % 3 == 1)
				bricks.add(new Brick(r.nextInt(180) + 225, y));
		}
	}

	// create enemies
	protected void createEnemy(float x, float y) {
		enemy.add(new Enemy(x, y));
		for (int i = 0; i < 100; i++) {
			y += 600;
			enemy.add(new Enemy(50 + r.nextInt(350), y));
		}
	}

	@Override
	public void onInit() {
		setTitle("BIRD JUMP - Version 1");

		image = new BitmapImage("data/images/bg1.jpg");
		image1 = new BitmapImage("data/images/bg2.jpg");
		// define the initial position of the mobile character
		bird1 = new Bird(new Vector2(225, 225));
		createBricks(225, 150);// define the position of the steps
		createEnemy(150, 800);// define the position of the enemies
		// load images
		images[0] = new BitmapImage("data/images/bg15.gif");
		images[1] = new BitmapImage("data/images/bg16.gif");
		images[2] = new BitmapImage("data/images/bg17.gif");
		images[3] = new BitmapImage("data/images/bg19.gif");
		images[4] = new BitmapImage("data/images/bg20.gif");
		// Load the MP3 sound file
		music[0] = new MusicPlayer("data/music/LaIslaBonita.mp3");
		music[1] = new MusicPlayer("data/music/MyHeartWillGoOn.mp3");
		music[2] = new MusicPlayer("data/music/JeSuisMalade.mp3");
		music[3] = new MusicPlayer("data/music/WakaWaka.mp3");
		music[4] = new MusicPlayer("data/music/SoltaneGhalbhaa.mp3");
	}
	//draw everything
	@Override
	public void onGraphicRender(GdxGraphics g) {
		// Stay in menu screen
		if (!begin) {
			g.clear();
			imageNo = bird1.background;
			g.drawTransformedPicture(225, 400, 0, super.getWindowWidth(), g.getCamera().position.y + 400,
					images[4]);
			g.drawStringCentered(g.getCamera().position.y + 30, "Welcome to BIRDEJUMP");
			g.drawStringCentered(g.getCamera().position.y, "Press ENTER to begin");
			g.drawStringCentered(g.getCamera().position.y - 30, "Press ESCAPE to quit");
			if (escape)
				exit();
		}
		// Enter in game screen
		if (begin) {
			g.clear();
			g.drawTransformedPicture(225, 400, 0, super.getWindowWidth(), g.getCamera().position.y + 400, images[imageNo]);
			// Update the bird1 position
			bird1.update(0.2f, bricks);
			// Draw the bird1 image
			bird1.draw(g);
			// Draw bricks
			for (DrawableObject o : bricks) {
				o.draw(g);
			}
			//Draw enemies
			for (DrawableObject o : enemy) {
				o.draw(g);
			}
			//Stop the game in case of collision
			for (int i = 0; i < enemy.size(); i++) {
				enemy.get(i).bird = bird1.position;
				enemy.get(i).update(0.2f);
				if (enemy.get(i).collision) {
					music[track].stop();
					bird1.position.x = 225;
					bird1.position.y = 225;
				}
			}
			g.drawString(g.getCamera().position.x - 220, g.getCamera().position.y - 380, "Score : " + score());
			g.drawSchoolLogo();
			// change position of the camera
			g.moveCamera(0, bird1.maxPosition - 300);
			if (bird1.position.y < g.getCamera().position.y - g.getScreenHeight() / 2 - 50) {
				g.clear(Color.FOREST);
				g.drawStringCentered(g.getCamera().position.y + 30, "GAME OVER");
				g.drawStringCentered(g.getCamera().position.y, "Your Score :  " + score());
				bricks.removeAllElements();
				music[track].stop();
				// *this part is not completed - not enough familiar with TEXTFIELD
				g.drawStringCentered(g.getCamera().position.y - 30,
						"To save your record  write your name and press ENTER");
				text();
				// *
 				g.drawStringCentered(g.getCamera().position.y - 100, "Press SPACE to return to first page");
				// Return to menu screen
 				if (space) {
					begin = false;
					bird1.position.x = 225;
					bird1.position.y = 225;
					enemy.removeAllElements();
					onInit();
					space = false;
				}
			}
		}

	}
	// Take the input
	@Override
	public void onKeyUp(int keycode) {
		switch (keycode) {
		case Input.Keys.LEFT:// no left side move
			bird1.thrustLeft = 0;
			break;
		case Input.Keys.RIGHT:// no right side move
			bird1.thrustRight = 0;
			break;
		case Input.Keys.UP:	// no bullet shooting
			for (int i = 0; i < enemy.size(); i++) {
				enemy.get(i).thrustUp = 0;
			}
			break;
		case Input.Keys.SPACE:// no return to menu screen
			space = false;
			break;
		default:
			break;
		}
	}
	// Take the inputs, "begin, quit or continue the game, horizontal moves during the game"
	@Override
	public void onKeyDown(int keycode) {
		switch (keycode) {
		case Input.Keys.LEFT:// left side move
			bird1.thrustLeft = Bird.MAX_THRUST;
			bird1.thrustRight = 0;
			break;
		case Input.Keys.RIGHT://right side move
			bird1.thrustRight = Bird.MAX_THRUST;
			bird1.thrustLeft = 0;
			break;
			case Input.Keys.ENTER://Begin the game
			begin = true;
			escape = false;
			music[0].play();
			break;
		case Input.Keys.ESCAPE:// leave the game at any moment
			escape = true;
			begin = false;
			for (int i = 0; i < music.length; i++) {
				if (music[i].isPlaying())
					music[i].stop();
			}
			break;
		case Input.Keys.SPACE:// shoot the bullet or continue after a fail
			space = true;
			for (int i = 0; i < enemy.size(); i++) {
				enemy.get(i).b = new Bullet(bird1.position.x, bird1.position.y + 100);
				enemy.get(i).thrustUp = 1;
			}
			break;
		case Input.Keys.UP:// 2nd option for shooting the bullet
			for (int i = 0; i < enemy.size(); i++) {
				enemy.get(i).b = new Bullet(bird1.position.x, bird1.position.y + 100);
				enemy.get(i).thrustUp = 1;
			}
			break;
		default:
			break;
		}
	}
	@Override
	public void exit() {
		super.exit();
	}
	// Score calculation 
	public int score() {
		score = (int) (bird1.maxPosition) / 100 - 2;
		return score;
	}
	// To take the name of the player and put him in ranking list
	public void actionPerformed(ActionEvent event) {
		String text = textBox.getText();
		toGrade(text, score());
	}
	// Rearranging the ranking list
	public void toGrade(String name, int s) {
		rankings.add(new Records(name, s));
		for (int i = 0; i < rankings.size(); i++) {
			for (int j = 1; j < rankings.size() - i; j++) {
				if (rankings.elementAt(i).score < rankings.elementAt(j).score) {
					rankings.insertElementAt(rankings.elementAt(j), i);
					rankings.elementAt(i).grade = i + 1;
				}
			}
		}
		rankings.toString();
	}

	@Override
	public void onDispose() {
		super.onDispose();
		// We must release all the resources we got
		for (int i = 0; i < music.length; i++) {
			music[i].dispose();
		}

	}

	@Override
	// Music on/off and change track
	public void onClick(int x, int y, int button) {
		if (music[track].isPlaying()) {
			music[track].stop();
			track++;
		} else
			music[track].play();

		if (track >= music.length)
			track = 0;
	}
	// Related to TEXTEFIELD, to write player name for saving the score, NOT COMPLETE
	public void text() {
		textBox.setBounds(50, 400, 400, 20);

	}

	public static void main(String[] args) {
		new BirdJump();
	}
}
