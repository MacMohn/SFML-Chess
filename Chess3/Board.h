#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Piece.h"

struct Square
{
	sf::RectangleShape shape;
	Piece* piece;

};

class Board
{

public:
	Board(int winWidth, int winHeight);
	void GenerateBoard();
	void Draw(sf::RenderWindow& window);
	bool ContainsPoint(sf::Vector2f point);

	std::vector<std::vector<Square>> gameBoard{ 8, std::vector<Square>(8) };

	sf::Vector2f sqSize = { 100.f, 100.f };
	sf::Vector2f topLeftBoard;
	sf::Vector2f bottomRightBoard;
	sf::Vector2f boardSize = {sqSize.x * 8, sqSize.y * 8};

	sf::Color black = sf::Color::Black;
	sf::Color white = sf::Color::White;
	sf::Color yellow = sf::Color(238, 255, 160);
	sf::Color green = sf::Color(57, 143, 10);

};

