#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <chrono>
#include <thread>

#define MAX_LICZBA_POZIOMOW 3


sf::Clock zegar;
float zegardt;

void update() {
	zegardt = zegar.getElapsedTime().asSeconds();
}

class Menu {

private:
	sf::Font font;
	sf::Text menu[MAX_LICZBA_POZIOMOW];
	int selectedItem = 0;

public:
	Menu(float width, float hegiht);
	~Menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow &window);
};

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		return;
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Nowa gra");
	menu[0].setPosition(sf::Vector2f(width / 3, height/ (MAX_LICZBA_POZIOMOW + 1) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Pomoc");
	menu[1].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 2));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Wyjscie");
	menu[2].setPosition(sf::Vector2f(width / 3, height / (MAX_LICZBA_POZIOMOW + 1) * 3));
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
		window.draw(menu[i]);
	}
};

void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MAX_LICZBA_POZIOMOW - 1;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MAX_LICZBA_POZIOMOW) {
		menu[selectedItem].setFillColor(sf::Color::White);
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MAX_LICZBA_POZIOMOW)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Cyan);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}

void myDelay(int opoznienie)
	{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
	}

	}

class wróg
{
private:
	sf::Vector2f position;
	sf::CircleShape ball;
	int maxW;

public:
	wróg(float x, float y);
	sf::CircleShape getWróg() { return ball; }
	sf::FloatRect getWrógBounds() { return ball.getGlobalBounds(); }
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y);

};

wróg::wróg(float x, float y) {
	position.x = x;
	position.y = y;

		ball.setRadius(10);
		ball.setFillColor(sf::Color(255, 0, 0));
		ball.setOutlineThickness(5);
		ball.setOutlineColor(sf::Color(0, 30, 255));
		ball.setPosition(position);
}

class hp
{
private:
	sf::Vector2f position;
	sf::CircleShape ball;
	int maxW;
	sf::RectangleShape kwadrat;

public:
	hp(float x, float y);
	sf::RectangleShape getHp() { return kwadrat; }
	sf::FloatRect getHpBounds() { return kwadrat.getGlobalBounds(); }
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y);

};

hp::hp(float x, float y) {
	position.x = x;
	position.y = y;

	kwadrat.setSize(sf::Vector2f(20, 20));
	kwadrat.setFillColor(sf::Color(255, 0, 0));
	kwadrat.setOutlineThickness(5);
	kwadrat.setOutlineColor(sf::Color(0, 30, 255));
	kwadrat.setPosition(position);
}

class zp
{
private:
	sf::Vector2f position;
	sf::CircleShape ball;
	int maxW;


public:
	zp(float x, float y);
	sf::RectangleShape getZp() { return kwadrat; }
	sf::FloatRect getZpBounds() { return kwadrat.getGlobalBounds(); }
	void draw(sf::RenderWindow& window);
	void setPosition(float x, float y);
	sf::RectangleShape kwadrat;
};

zp::zp(float x, float y) {
	position.x = x;
	position.y = y;

	kwadrat.setSize(sf::Vector2f(20, 20));
	kwadrat.setFillColor(sf::Color(255, 0, 0));
	kwadrat.setOutlineThickness(5);
	kwadrat.setOutlineColor(sf::Color(0, 30, 255));
	kwadrat.setPosition(position);
}

float randx()
{
	float a = rand() % 800;
	return a;
}
float randy()
{
	float b = rand() % 600;
	return b;
}

void wróg::draw(sf::RenderWindow& window) {
	for (int i = 0; i < maxW; i++) {
		window.draw(ball);
	};
}

void wróg::setPosition(float x, float y) {
	position.x = x;
	position.y = y;
}

class gracz
{
private:
	sf::Vector2f position;
	sf::RenderWindow* win;
	sf::Vector2f okno;
	sf::Texture tekstura;
	sf::Sprite statek;
public:
	gracz(float x, float y, sf::RenderWindow* win);
	void steruj();
	sf::Sprite getGracz() { return statek; }
	sf::FloatRect getGraczBounds() { return statek.getGlobalBounds(); }
};

gracz::gracz(float x, float y, sf::RenderWindow* w)
{
	tekstura.loadFromFile("statek.png");
	statek.setTexture(tekstura);
	win = w;
	okno.x = win->getSize().x;
	okno.y = win->getSize().y;
	position.x = x;
	position.y = y;
	statek.setPosition(position);
	statek.setOrigin(50, 50);
}

void gracz::steruj()
{
	position = statek.getPosition();
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) && (position.y > 0))
	{
		statek.move(0, -0.8);
		statek.setRotation(0.f);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) && (position.y < okno.y))
	{
		statek.move(0, 0.8);
		statek.setRotation(180.f);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) && (position.x > 0))
	{
		statek.move(-0.8, 0);
		statek.setRotation(270.f);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) && (position.x < okno.x))
	{
		statek.move(0.8, 0);
		statek.setRotation(90.f);
	}
}




int main()
{
	srand(time(NULL));
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Zjadanie Kolek w Kosmosie");
	sf::Texture t;
	t.setRepeated(true);
	t.loadFromFile("bg.png");
	sf::Sprite t³o;
	t³o.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
	t³o.setTexture(t);
	Menu menu(window.getSize().x, window.getSize().y);
	float posx = (window.getSize().x) / 2;
	float posy = (window.getSize().y) / 2;
	gracz g1(posx, posy, &window);
	int maxW = 0;
	int punkty = 0;
	int zycie = 10;

	std::vector< wróg > wrogowie = {
		wróg(randx(), randy()),
		wróg(randx(), randy()),
		wróg(randx(), randy()),
		wróg(randx(), randy()),
		wróg(randx(), randy()),
		wróg(randx(), randy()),
		wróg(randx(), randy()),
	};

	std::vector<hp> hp1 = {
		hp(randx(), randy())
	};

	std::vector<zp> zp1 = {
		zp(randx(), randy())
	};

	sf::Texture pomoctex;
	pomoctex.loadFromFile("pomoc.png");
	sf::Sprite pomoc;
	pomoc.setTexture(pomoctex);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(250);
					menu.przesunG();
				}

			if (event.key.code == sf::Keyboard::Down)
			{
				myDelay(250);
				menu.przesunG();
			}
			if (menu_selected_flag == 0)
			{
				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
				{
					std::cout << "Uruchamiam gre..." << std::endl;
					menu_selected_flag = 1;
				}
				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
				{
					std::cout << "Pomoc..." << std::endl;
					menu_selected_flag = 2;
				}
				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
				{
					std::cout << "Koniec gry..." << std::endl;
					menu_selected_flag = 3;
					window.close();
				}
			}


		}

		window.clear();
		if (menu_selected_flag == 0)
			window.draw(t³o);
			menu.draw(window);
		if (menu_selected_flag == 1)
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
				menu_selected_flag = 2;
			}
			window.draw(t³o);
			window.draw(g1.getGracz());
			g1.steruj();

			for (auto& i : wrogowie) {
				window.draw(i.getWróg());
			}
			for (auto& i : hp1) {
				window.draw(i.getHp());
			}
			for (auto& i : zp1) {
				window.draw(i.getZp());
			}

			for (size_t i = 0; i < wrogowie.size(); i++) {
				if (g1.getGraczBounds().intersects(wrogowie[i].getWrógBounds())) {
					wrogowie.erase(wrogowie.begin() + i);
					punkty += 1.f;
					std::cout << "Punkty:" << punkty << std::endl;


				}
			};

			for (size_t i = 0; i < hp1.size(); i++) {
				if (g1.getGraczBounds().intersects(hp1[i].getHpBounds())) {
					hp1.erase(hp1.begin() + i);
					zycie += 1.f;

				}
			};

			for (size_t i = 0; i < zp1.size(); i++) {
				if (g1.getGraczBounds().intersects(zp1[i].getZpBounds())) {
					zp1.erase(zp1.begin() + i);
					zycie -= 1.f;
				}
			};

			if (hp1.size() < 1) {

				hp1.push_back(hp(randx(), randy()));

				for (auto& i : hp1) {
					window.draw(i.getHp());
				}
			}

			if (zp1.size() < 1) {

				zp1.push_back(zp(randx(), randy()));

				for (auto& i : zp1) {
					window.draw(i.getZp());
				}
			}

			if (wrogowie.size() < 7) {

				wrogowie.push_back(wróg(randx(), randy()));
				for (auto& i : wrogowie) {
					window.draw(i.getWróg());
				}
			}

			sf::Text text;
			sf::Font font;
			font.loadFromFile("arial.ttf");
			text.setString("Punkty:");
			text.setFont(font);
			text.setFillColor(sf::Color::Red);
			text.setPosition(sf::Vector2f(20, 20));
			window.draw(text);
			std::string myString = std::to_string(punkty);
			sf::Text tekst;
			tekst.setString(myString);
			tekst.setFont(font);
			tekst.setFillColor(sf::Color::Red);
			tekst.setPosition(sf::Vector2f(120, 20));
			window.draw(tekst);
			sf::Text text2;
			text2.setString("Zycie:");
			text2.setFont(font);
			text2.setFillColor(sf::Color::Green);
			text2.setPosition(sf::Vector2f(670, 20));
			window.draw(text2);
			std::string myString1 = std::to_string(zycie);
			tekst.setString(myString1);
			tekst.setFont(font);
			tekst.setFillColor(sf::Color::Green);
			tekst.setPosition(sf::Vector2f(750, 20));
			window.draw(tekst);

			update();
			if (zegardt >= 1.5) {
				update();
				zycie--;
				zegar.restart();
			}

			if (zycie == 0) {
				menu_selected_flag = 4;
			};

			
		}

		if (menu_selected_flag == 2) {
			window.draw(pomoc);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				menu_selected_flag = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
				menu_selected_flag = 1;
			}
		}

		if (menu_selected_flag == 4) {
			window.draw(t³o);
			sf::Text koniec;
			sf::Font font;
			font.loadFromFile("arial.ttf");
			koniec.setString("Przegrales!!");
			koniec.setFont(font);
			koniec.setCharacterSize(50);
			koniec.setFillColor(sf::Color::Red);
			koniec.setPosition(sf::Vector2f(400, 0));

			//std::string s;
			//sf::Event event;
			//while (window.pollEvent(event)) {
			//	if (event.type == sf::Event::Closed)
			//		window.close();
			//	if (event.type == sf::Event::TextEntered) {
			//		if (event.KeyPressed == sf::Keyboard::BackSpace && s.size() != 0) {
			//			s.pop_back();
			//			std::cout << s << std::endl;
			//		}
			//		else if (event.text.unicode < 128) {
			//			s.push_back((char)event.text.unicode);
			//			std::cout << s << std::endl;
			//		}
			//	}
			//}

			window.draw(koniec);
		}
		window.display();
	}
	
	return 0;
}

