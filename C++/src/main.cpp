#include "main.h"


//Variable globales
int game = 1, dir = 0, speed = 200, Size =2;

struct SnakeBody {
	float x = 0;
	float y = 0;
}p[100];

int main()
{
	RenderWindow app;
	Event event;
	Font font;

	if (!font.loadFromFile("res/Poppins-Regular.ttf")) {
		cout << "Erreur lors du chargement de la police d'�criture";
	}

	app.create(VideoMode(APP_WIDTH, APP_HEIGHT), "My Snake Game in C++");

	Text scoreTxt;

	scoreTxt.setFillColor(Color::Cyan);
	scoreTxt.setCharacterSize(18);
	scoreTxt.setPosition(700, 25);
	scoreTxt.setFont(font);
	scoreTxt.setStyle(Text::Bold | Text::Underlined | Text::Italic);

	CircleShape head(24);
	CircleShape body(25);
	CircleShape apple(21);

	int randomx, randomy, isOne=0;
	
	head.setPosition(50, 0);
	head.setFillColor(Color(255, 100, 0));
	head.setPointCount(60000);

	body.setPosition(0, 0);
	body.setFillColor(Color(175, 255, 255));
	body.setPointCount(60000);

	apple.setFillColor(Color(175, 0, 25));
	apple.setPointCount(60000);

	while (app.isOpen()) 
	{
		while (app.pollEvent(event))
		{
			
			if (event.type == Event::Closed) 
			{
				app.close();
			}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up && dir != 3) dir = 2;
				if (event.key.code == Keyboard::Down && dir != 2) dir = 3;
				if (event.key.code == Keyboard::Left && dir != 0) dir = 1;
				if (event.key.code == Keyboard::Right && dir != 1) dir = 0;

			}



		}
		app.clear(Color(26, 26, 26));

		if (game == 1)
		{
			

			scoreTxt.setString("Score:" + to_string(Size));


			// Generate apple and randomize her position in the field
			if (isOne == 0)
			{
				randomx = (rand() % 16) *50;
				randomy = (rand() % 12) *50;

				while (checkIfIn(randomx, randomy))
				{
					randomx = (rand() % 16) * 50;
					randomy = (rand() % 12) * 50;
				}

				apple.setPosition(randomx, randomy);
				isOne = 1;






			}
			for (int i = Size; i > 0; i--)
			{
				p[i] = p[i - 1];
			}

			// Move head of the sneak
			if (dir == 1 && p[0].x != 0) p[0].x -= 50.f;
			if (dir == 0 && p[0].x != APP_WIDTH -50) p[0].x += 50.f;
			if (dir == 2 && p[0].y != 0) p[0].y -= 50.f;
			if (dir == 3 && p[0].y != APP_HEIGHT - 50) p[0].y += 50.f;

			head.setPosition(p[0].x, p[0].y);

			if (p[0].x == randomx && p[0].y == randomy)
			{
				isOne = 0;
				Size += 1;
				p[Size] = p[(Size - 1)];
			}
			app.draw(scoreTxt);
			app.draw(apple);

			//Draw body of the snake
			for (int i = Size; i > 0; i--)
			{
				body.setPosition(p[i].x, p[i].y);
				app.draw(body);
			}
			app.draw(head);


			app.display();
			for (int i = 1; i < Size; i++)
			{
				if (i != 0) {
					if (p[i].x == p[0].x && p[i].y == p[0].y)
					{
						game = 0;
					}
				}

			}
			Sleep(speed);

		}
		if (game == 0)
		{
			Text gameOver;

			gameOver.setFillColor(Color::Red);
			gameOver.setCharacterSize(38);
			gameOver.setPosition(300, 250);
			gameOver.setFont(font);
			gameOver.setStyle(Text::Bold | Text::Underlined | Text::Italic);
			gameOver.setString("Game Over!!");

			scoreTxt.setPosition(300, 350);
			scoreTxt.setFillColor(Color(255, 0, 0));
			app.draw(apple);
			//Move body of the Snake
			for (int i = Size; i > 0; i--)
			{
				body.setPosition(p[i].x, p[i].y);
				app.draw(body);
			}
			app.draw(head);

			app.draw(gameOver);
			app.draw(scoreTxt);

			app.display();

		}
	}


}

boolean checkIfIn(int randomx, int randomy)
{
	boolean found = false;
	for (int i = 0; i < Size; i++)
	{
		if (p[i].x == randomx && p[i].y == randomy)
		{
			found= true;
		}
	}
	return found;
}

