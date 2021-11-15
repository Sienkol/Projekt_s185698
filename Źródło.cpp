#include <SFML/Graphics.hpp>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 3

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
	menu[1].setString("Ostatnie wyniki");
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

int main()
{
	int menu_selected_flag = 0;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML demo");
	Menu menu(window.getSize().x, window.getSize().y);
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
					std::cout << "Najlepsze wyniki..." << std::endl;
					menu_selected_flag = 1;
				}
				if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
				{
					std::cout << "Koniec gry..." << std::endl;
					menu_selected_flag = 1;
				}
			}


		}

	window.clear();
	if (menu_selected_flag == 0)
		menu.draw(window);

	window.display();
}
	return 0;
}