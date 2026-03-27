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
        allPieces.push_back(std::make_unique<Piece>(pawnW, board.gameBoard[i][6].shape.getPosition(), PieceType::Pawn, PieceColor::White));
        board.gameBoard[i][6].piece = allPieces.back().get();
        allPieces.push_back(std::make_unique<Piece>(pawnB, board.gameBoard[i][1].shape.getPosition(), PieceType::Pawn, PieceColor::Black));
        board.gameBoard[i][1].piece = allPieces.back().get();
    }
    //Rook
    allPieces.push_back(std::make_unique<Piece>(rookW, board.gameBoard[0][7].shape.getPosition(), PieceType::Rook, PieceColor::White));
    board.gameBoard[0][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(rookW, board.gameBoard[7][7].shape.getPosition(), PieceType::Rook, PieceColor::White));
    board.gameBoard[7][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(rookB, board.gameBoard[0][0].shape.getPosition(), PieceType::Rook, PieceColor::Black));
    board.gameBoard[0][0].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(rookB, board.gameBoard[7][0].shape.getPosition(), PieceType::Rook, PieceColor::Black));
    board.gameBoard[7][0].piece = allPieces.back().get();
    //Knight
    allPieces.push_back(std::make_unique<Piece>(knightW, board.gameBoard[1][7].shape.getPosition(), PieceType::Knight, PieceColor::White));
    board.gameBoard[1][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(knightW, board.gameBoard[6][7].shape.getPosition(), PieceType::Knight, PieceColor::White));
    board.gameBoard[6][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(knightB, board.gameBoard[1][0].shape.getPosition(), PieceType::Knight, PieceColor::Black));
    board.gameBoard[1][0].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(knightB, board.gameBoard[6][0].shape.getPosition(), PieceType::Knight, PieceColor::Black));
    board.gameBoard[6][0].piece = allPieces.back().get();
    //Bishop
    allPieces.push_back(std::make_unique<Piece>(bishopW, board.gameBoard[2][7].shape.getPosition(), PieceType::Bishop, PieceColor::White));
    board.gameBoard[2][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(bishopW, board.gameBoard[5][7].shape.getPosition(), PieceType::Bishop, PieceColor::White));
    board.gameBoard[5][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(bishopB, board.gameBoard[2][0].shape.getPosition(), PieceType::Bishop, PieceColor::Black));
    board.gameBoard[2][0].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(bishopB, board.gameBoard[5][0].shape.getPosition(), PieceType::Bishop, PieceColor::Black));
    board.gameBoard[5][0].piece = allPieces.back().get();
    //Queen
    allPieces.push_back(std::make_unique<Piece>(queenW, board.gameBoard[3][7].shape.getPosition(), PieceType::Queen, PieceColor::White));
    board.gameBoard[3][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(queenB, board.gameBoard[3][0].shape.getPosition(), PieceType::Queen, PieceColor::Black));
    board.gameBoard[3][0].piece = allPieces.back().get();
    //King
    allPieces.push_back(std::make_unique<Piece>(kingW, board.gameBoard[4][7].shape.getPosition(), PieceType::King, PieceColor::White));
    board.gameBoard[4][7].piece = allPieces.back().get();
    allPieces.push_back(std::make_unique<Piece>(kingB, board.gameBoard[4][0].shape.getPosition(), PieceType::King, PieceColor::Black));
    board.gameBoard[4][0].piece = allPieces.back().get();

}

void Game::Draw(sf::RenderWindow& window)
{
	board.Draw(window);

    for (auto& p : allPieces)
    {
        p->Draw(window);
    }
}

void Game::Update(sf::RenderWindow& window, std::optional<sf::Event> e)
{
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    MouseBoardPos(mousePos);
    if(e && e->is<sf::Event::MouseButtonPressed>())
    {
        mouse1Pressed = e->getIf<sf::Event::MouseButtonPressed>()->button == leftMouse;
        mouse2Pressed = e->getIf<sf::Event::MouseButtonPressed>()->button == rightMouse;
    }
   
    SelectPiece(e);
    HoldingPiece(e, mousePos);
 
}

sf::Vector2f Game::CenterPieceOnMouse(sf::Vector2f pos)
{
    return sf::Vector2f{ pos.x - board.sqSize.x / 2, pos.y - board.sqSize.y / 2 };
}

void Game::MouseBoardPos(sf::Vector2f pos)
{

    tileX = floor((pos.x - board.topLeftBoard.x) / board.sqSize.x);
    tileY = floor((pos.y - board.topLeftBoard.y) / board.sqSize.y);

    if (tileX >= 0 && tileX <= 7
        && tileY >= 0 && tileY <= 7)
    {
        mouseOnBoard = true;
    }
    else
    {
        mouseOnBoard = false;
    }
}

void Game::SelectPiece(std::optional<sf::Event> e)
{
    if (!selectedPiece && mouseOnBoard)
    {
        if (e && e->is<sf::Event::MouseButtonPressed>())
        {
            previousSq = &board.gameBoard[tileX][tileY];
            selectedPiece = board.gameBoard[tileX][tileY].piece;
            prevTileX = tileX;
            prevTileY = tileY;
        }
    }
}

void Game::HoldingPiece(std::optional<sf::Event> e, sf::Vector2f mousePos)
{
    if (selectedPiece)
    {
        selectedPiece->sprite.setPosition(CenterPieceOnMouse(mousePos));
        if (mouse2Pressed)
        {
            selectedPiece->sprite.setPosition(previousSq->shape.getPosition());
            selectedPiece = nullptr;
        }
        else if ((e && e->is<sf::Event::MouseButtonPressed>()) && mouseOnBoard)
        {
            if (board.gameBoard[tileX][tileY].piece == nullptr && mouse1Pressed)
            {
                std::cout << "TileX: " << tileX << "\nTileY: " << tileY << std::endl;
                if (selectedPiece->type == PieceType::Pawn)
                {
                    if (Pawnlogic())
                    {
                        MovePiece();
                    }
                    else
                    {
                        std::cout << "false\n";
                    }
                }
            }
        }
    }
}

void Game::MovePiece()
{
    board.gameBoard[tileX][tileY].piece = selectedPiece;
    selectedPiece->sprite.setPosition(board.gameBoard[tileX][tileY].shape.getPosition());
    selectedPiece = nullptr;
    previousSq->piece = nullptr;
}

bool Game::Pawnlogic()
{
    if (tileY == prevTileY - 1 && tileX == prevTileX)
    {
        return true;
    }
    else
    {
        return false;
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