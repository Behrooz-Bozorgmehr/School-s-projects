package ch.hevs.gdx2d.hello;

public class Records {
	String name = "";
	int score =0;
	int grade= 0;
	Records(String n, int s){
		this.name = n;
		this.score = s;
		grade++;
	}
			
	public String toString(){
		String result ="";
		result+= grade +":  "+ name + "===>"+score+"\n";
		return result;
		}
}
