#include "Game.h"
#include "Piece.h"

Game::Game(int winWidth, int winHeight) : board(winWidth, winHeight)
{
    LoadTextures();
    InitPieces();

    
}

void Game::InitPieces()
{
    //Pawn
    for (int i = 0; i < 8; i++)
    {
        allPieces.push_back(std::make_unique<Piece>(pawnW, board.gameBoard[6][i].shape.getPosition(), PieceType::Pawn, PieceColor::White));
        board.gameBoard[6][i].piece = allPieces.back().get();
        allPieces.push_back(std::make_unique<Piece>(pawnB, board.gameBoard[1][i].shape.getPosition(), PieceType::Pawn, PieceColor::Black));
        board.gameBoard[1][i].piece = allPieces.back().get();
    }
    //Rook
    allPieces.push_back(std::make_unique<Piece>(rookW, board.gameBoard[7][0].shape.getPosition(), PieceType::Rook, PieceColor::White));
    board.gameBoard[7][0].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(rookW, board.gameBoard[7][7].shape.getPosition(), PieceType::Rook, PieceColor::White));
    board.gameBoard[7][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(rookB, board.gameBoard[0][0].shape.getPosition(), PieceType::Rook, PieceColor::Black));
    board.gameBoard[0][0].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(rookB, board.gameBoard[0][7].shape.getPosition(), PieceType::Rook, PieceColor::Black));
    board.gameBoard[0][7].piece = allPieces.back().get();
    //Knight
    allPieces.push_back(std::make_unique<Piece>(knightW, board.gameBoard[7][1].shape.getPosition(), PieceType::Knight, PieceColor::White));
    board.gameBoard[7][1].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(knightW, board.gameBoard[7][6].shape.getPosition(), PieceType::Knight, PieceColor::White));
    board.gameBoard[7][6].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(knightB, board.gameBoard[0][1].shape.getPosition(), PieceType::Knight, PieceColor::Black));
    board.gameBoard[0][1].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(knightB, board.gameBoard[0][6].shape.getPosition(), PieceType::Knight, PieceColor::Black));
    board.gameBoard[0][6].piece = allPieces.back().get();
    //Bishop
    allPieces.push_back(std::make_unique<Piece>(bishopW, board.gameBoard[7][2].shape.getPosition(), PieceType::Bishop, PieceColor::White));
    board.gameBoard[7][2].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(bishopW, board.gameBoard[7][5].shape.getPosition(), PieceType::Bishop, PieceColor::White));
    board.gameBoard[7][5].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(bishopB, board.gameBoard[0][2].shape.getPosition(), PieceType::Bishop, PieceColor::Black));
    board.gameBoard[0][2].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(bishopB, board.gameBoard[0][5].shape.getPosition(), PieceType::Bishop, PieceColor::Black));
    board.gameBoard[0][5].piece = allPieces.back().get();
    //Queen
    allPieces.push_back(std::make_unique<Piece>(queenW, board.gameBoard[7][3].shape.getPosition(), PieceType::Queen, PieceColor::White));
    board.gameBoard[7][3].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(queenB, board.gameBoard[0][3].shape.getPosition(), PieceType::Queen, PieceColor::Black));
    board.gameBoard[0][3].piece = allPieces.back().get();
    //King
    allPieces.push_back(std::make_unique<Piece>(kingW, board.gameBoard[7][4].shape.getPosition(), PieceType::King, PieceColor::White));
    board.gameBoard[7][4].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(kingB, board.gameBoard[0][4].shape.getPosition(), PieceType::King, PieceColor::Black));
    board.gameBoard[0][4].piece = allPieces.back().get();

}

void Game::Draw(sf::RenderWindow& window)
{
	board.Draw(window);

    for (auto& p : allPieces)
    {
        p->Draw(window);
    }
}

void Game::Update(sf::RenderWindow& window)
{
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool mouse1Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    bool mouse2Pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
    int tileX = floor((mousePos.x - board.topLeftBoard.x) / board.sqSize.x);
    int tileY = floor((mousePos.y - board.topLeftBoard.y) / board.sqSize.y);
    
    if (tileX >= 0 && tileX <= 7
        && tileY >= 0 && tileY <= 7)
    {mouseOnBoard = true;}
    else
    {mouseOnBoard = false;}

    if (mouse1Pressed)
    {
        std::cout << "TileX: " << tileX << "\nTileY: " << tileY << std::endl;
    }
    
    if (!selectedPiece && mouseOnBoard)
    {
        if (mouse1Pressed)
        {
            previousSq = &board.gameBoard[tileY][tileX];
            selectedPiece = board.gameBoard[tileY][tileX].piece;
        }
    }
    if (selectedPiece)
    {
        selectedPiece->sprite.setPosition({mousePos.x - board.sqSize.x /2, mousePos.y - board.sqSize.y /2});
        if (mouse2Pressed)
        {
            selectedPiece->sprite.setPosition(previousSq->shape.getPosition());
            selectedPiece = nullptr;
        }
    }



}

void Game::LoadTextures()
{

    if (!pawnB.loadFromFile("Pieces/b-pawn.png"))
    {
        std::cerr << "Failed to load black pawn texture\n";
    }

    if (!pawnW.loadFromFile("Pieces/w-pawn.png"))
    {
        std::cerr << "Failed to load white pawn texture\n";
    }

    if (!knightB.loadFromFile("Pieces/b-knight.png"))
    {
        std::cerr << "Failed to load black knight texture\n";
    }

    if (!knightW.loadFromFile("Pieces/w-knight.png"))
    {
        std::cerr << "Failed to load white knight texture\n";
    }

    if (!bishopB.loadFromFile("Pieces/b-bishop.png"))
    {
        std::cerr << "Failed to load black bishop texture\n";
    }

    if (!bishopW.loadFromFile("Pieces/w-bishop.png"))
    {
        std::cerr << "Failed to load white bishop texture\n";
    }

    if (!rookB.loadFromFile("Pieces/b-rook.png"))
    {
        std::cerr << "Failed to load black rook texture\n";
    }

    if (!rookW.loadFromFile("Pieces/w-rook.png"))
    {
        std::cerr << "Failed to load white rook texture\n";
    }

    if (!queenB.loadFromFile("Pieces/b-queen.png"))
    {
        std::cerr << "Failed to load black queen texture\n";
    }

    if (!queenW.loadFromFile("Pieces/w-queen.png"))
    {
        std::cerr << "Failed to load white queen texture\n";
    }

    if (!kingB.loadFromFile("Pieces/b-king.png"))
    {
        std::cerr << "Failed to load black king texture\n";
    }

    if (!kingW.loadFromFile("Pieces/w-king.png"))
    {
        std::cerr << "Failed to load white king texture\n";
    }
}