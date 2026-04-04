#include "Board.h"


Board::Board(int winWidth, int winHeight) 
{
	topLeftBoard = {(winWidth - boardSize.x) / 2.f, (winHeight - boardSize.y) / 2.f};
	GenerateBoard();
}

void Board::GenerateBoard()
{
	for (col = 0; col < 8; col++)
	{
		for (row = 0; row < 8; row++)
		{
			Square& sq = gameBoard[col][row];

			if ((row + col) % 2 == 0)
			{
				sq.shape.setFillColor(yellow);
			}
			else
			{
				sq.shape.setFillColor(green);
			}
			
				sq.shape.setOutlineColor(sf::Color::Black);

			sq.shape.setOutlineThickness(-1.5f);
			sq.shape.setSize(sqSize);
			sq.shape.setPosition({ topLeftBoard.x + sqSize.x * col, topLeftBoard.y + sqSize.y * row });
		}
	}

}

void Board::Draw(sf::RenderWindow& window)
{
	for (auto& col : gameBoard)
	{
		for(auto& sq : col)
		{
			window.draw(sq.shape);
		}
	}
}

bool Board::ContainsPoint(sf::Vector2f point)
{
	bottomRightBoard = { topLeftBoard.x + boardSize.x, topLeftBoard.y + boardSize.y };
	
	return	point.x > topLeftBoard.x &&
		point.x < bottomRightBoard.x &&
		point.y > topLeftBoard.y &&
		point.y < bottomRightBoard.y;
}

void Board::pOnBoardIndication()
{
	for (auto& col : gameBoard)
	{
		//for (auto row : col)
		//{
		//	if (gameBoard[col][row])
		//}
	}
}

