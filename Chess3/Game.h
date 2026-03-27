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
	void Update(sf::RenderWindow& window, std::optional<sf::Event> e);

	sf::Vector2f CenterPieceOnMouse(sf::Vector2f pos);
	void MouseBoardPos(sf::Vector2f pos);
	void SelectPiece(std::optional<sf::Event> e);
	void HoldingPiece(std::optional<sf::Event> e, sf::Vector2f mousePos);
	void MovePiece();
	bool Pawnlogic();

	std::vector<std::unique_ptr<Piece>> allPieces;
	Piece* selectedPiece = nullptr;
	Square* previousSq = nullptr;
	Square* mouseSq = nullptr;
	
	sf::Mouse::Button leftMouse  = sf::Mouse::Button::Left;
	sf::Mouse::Button rightMouse = sf::Mouse::Button::Right;
	bool mouseOnBoard  = false;
	bool mouse1Pressed = false;
	bool mouse2Pressed = false;

	int tileX = 0;
	int tileY = 0;
	int prevTileX = 0;
	int prevTileY = 0;
	
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

