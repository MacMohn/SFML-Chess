#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

enum class PieceType
{
	Pawn, Rook, Knight, Bishop, King, Queen
};
enum class PieceColor
{
	White, Black
};

class Piece
{
	
public:
	Piece(sf::Texture& texture, sf::Vector2f position, PieceType t, PieceColor c);
	void Draw(sf::RenderWindow& window);

	PieceType type;
	PieceColor color;

	sf::Sprite sprite;

};

