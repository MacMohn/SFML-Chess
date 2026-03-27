#pragma once
#include "Board.h"
#include "Piece.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Game
{
	Board board;
public:
	Game(int winWidth, int winHeight);
	void InitPieces();
	void LoadTextures();
	
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);

	std::vector<std::unique_ptr<Piece>> allPieces;
	Piece* selectedPiece = nullptr;
	Square* previousSq = nullptr;
	Square* mouseSq = nullptr;
	
	bool mouseOnBoard = false;
#pragma region textures
	sf::Texture pawnB;
	sf::Texture pawnW;
	sf::Texture knightB;
	sf::Texture knightW;
	sf::Texture bishopB;
	sf::Texture bishopW;
	sf::Texture rookB;
	sf::Texture rookW;
	sf::Texture queenB;
	sf::Texture queenW;
	sf::Texture kingB;
	sf::Texture kingW;
#pragma endregion


};

