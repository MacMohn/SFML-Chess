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
    if (SelectPiece(e))
    {
        return;//ensure event isn't read by next function
    }
    HoldingPiece(e, mousePos);

    //for (int x = 0; x < 8; x++)
    //{
    //    for (int y = 0; y < 8; y++)
    //    {
    //        Square& sq = board.gameBoard[x][y];

    //        if (sq.piece != nullptr)
    //        {
    //            int yel = 150;
    //            // static darker shade
    //            if ((x + y) % 2 == 0)
    //            {
    //                sq.shape.setFillColor(sf::Color(yel, yel, 100));
    //            }
    //            else
    //            {
    //                sq.shape.setFillColor(sf::Color(80, 180, 0));
    //            }
    //        }
    //        else
    //        {
    //            // checkerboard original color
    //            if ((x + y) % 2 == 0)
    //                sq.shape.setFillColor(board.yellow);
    //            else
    //                sq.shape.setFillColor(board.green);
    //        }
    //    }
    //}
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

bool Game::SelectPiece(std::optional<sf::Event> e)
{
    if (!selectedPiece && mouseOnBoard)
    {
        if (e && e->is<sf::Event::MouseButtonPressed>())
        {
            previousSq = &board.gameBoard[tileX][tileY];
            selectedPiece = board.gameBoard[tileX][tileY].piece;
            prevTileX = tileX;
            prevTileY = tileY;

            return true;
        }
    }
    return false;
}

void Game::HoldingPiece(std::optional<sf::Event> e, sf::Vector2f mousePos)
{
    if (selectedPiece)
    {
        selectedPiece->sprite.setPosition(CenterPieceOnMouse(mousePos));
        if (e && e->is<sf::Event::MouseButtonPressed>())
        {
            auto* eventM = e->getIf<sf::Event::MouseButtonPressed>();
            if (eventM->button == rightMouse)
            {
                selectedPiece->sprite.setPosition(previousSq->shape.getPosition());
                selectedPiece = nullptr;
            }
            else if (mouseOnBoard && eventM->button == leftMouse)
            {
                std::cout << "TileX: " << tileX << "\nTileY: " << tileY << std::endl;

                if (AllPieceLogic() == true)
                {
                    MovePiece();
                    pieceOnTile = nullptr;
                }
            }
        }
    }
}

void Game::MovePiece()
{
    std::cout << "move Piece\n";
    board.gameBoard[tileX][tileY].piece = selectedPiece;
    selectedPiece->sprite.setPosition(board.gameBoard[tileX][tileY].shape.getPosition());
    selectedPiece = nullptr;
    previousSq->piece = nullptr;
}

bool Game::AllPieceLogic()
{
    pType = selectedPiece->type;
    switch (pType)
    {
    case PieceType::Pawn:
        return Pawnlogic();
    case PieceType::Bishop:
        return Bishoplogic();
    case PieceType::Knight:
        return Knightlogic();
    case PieceType::Rook:
        return Rooklogic();
    case PieceType::Queen:
        return Queenlogic();
    case PieceType::King:
        return Kinglogic();
    default: std::cout << "Piece type N/A\n";
        return false;
    }
    
}

bool Game::Pawnlogic()
{
    pieceOnTile = board.gameBoard[tileX][tileY].piece;
    if (selectedPiece->color == PieceColor::White)
    {
        if (tileY == prevTileY - 2 && tileX == prevTileX && selectedPiece->hasMoved == false)
        {
            std::cout << "Cond 1: \n";
            selectedPiece->hasMoved = true;
            return true;
        }
        else if (tileY == prevTileY - 1 && tileX == prevTileX && pieceOnTile == nullptr)
        {
            std::cout << "Cond 2: \n";

            selectedPiece->hasMoved = true;
            return true;
        }
        else if (pieceOnTile != nullptr && pieceOnTile->color == PieceColor::Black 
            && (tileY == prevTileY - 1)
            && (tileX == prevTileX + 1 || tileX == prevTileX - 1))
        {
            std::cout << "Cond 3: \n";
            board.gameBoard[tileX][tileY].piece->sprite.setScale({ .35, .35 });
            board.gameBoard[tileX][tileY].piece->sprite.setPosition({50, 900});
            board.gameBoard[tileX][tileY].piece = nullptr;
            selectedPiece->hasMoved = true;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (tileY == prevTileY + 2 && tileX == prevTileX && selectedPiece->hasMoved == false)
        {
            selectedPiece->hasMoved = true;
            return true;
        }
        else if (tileY == prevTileY + 1 && tileX == prevTileX && pieceOnTile == nullptr)
        {
            selectedPiece->hasMoved = true;
            return true;
        }
        else if (pieceOnTile != nullptr && pieceOnTile->color == PieceColor::White 
            && (tileY == prevTileY + 1
            && (tileX == prevTileX + 1 || tileX == prevTileX - 1)))
        {
            board.gameBoard[tileX][tileY].piece->sprite.setScale({ .35, .35 });
            board.gameBoard[tileX][tileY].piece->sprite.setPosition({ 50, 180 });
            board.gameBoard[tileX][tileY].piece = nullptr;
            selectedPiece->hasMoved = true;
            return true;

        }
        else
        {
            return false;
        }
    }
}

bool Game::Bishoplogic()
{
    return false;
}

bool Game::Knightlogic()
{

    if (((tileX == prevTileX + 1 || tileX == prevTileX - 1)
        && (tileY == prevTileY - 2) || tileY == prevTileY + 2) || 
        ((tileX == prevTileX + 2 || tileX == prevTileX - 2)
        && (tileY == prevTileY - 1 || tileY == prevTileY + 1)))
    {
        if (board.gameBoard[tileX][tileY].piece == nullptr)
        {
            return true;
        }
        else if (selectedPiece->color != board.gameBoard[tileX][tileY].piece->color)
        {
            board.gameBoard[tileX][tileY].piece->sprite.setPosition({ 300, 300 });
            return true;
        }
    }
    return false;
}

bool Game::Rooklogic()
{
    return true;
}

bool Game::Kinglogic()
{
    return true;
}

bool Game::Queenlogic() //TODO: I think up down and left right could each be in their own loop
{
    int maxTileUp = 0;
    int maxTileDown = 0;
    int maxTileRight = 0;
    int maxTileLeft = 0;

    int maxUpLeft = 0;
    int maxDownLeft = 0;
    int maxDownRight = 0;
    int maxUpRight = 0;

    
    for (int i = prevTileY - 1; i >= 0; i--)//moveUp
    {
        if (board.gameBoard[tileX][i].piece == nullptr)
        {
            maxTileUp++;
        }
        else { break; }
    }
    for (int i = prevTileY + 1; i < board.sqCount; i++)//moveDown
    {
        if (board.gameBoard[tileX][i].piece == nullptr)
        {
            maxTileDown++;
        }
        else { break; }
    }
    for (int i = prevTileX + 1; i < board.sqCount; i++)//moveRight
    {
        if (board.gameBoard[i][tileY].piece == nullptr)
        {
            maxTileRight++;
        }
        else { break; }
    }
    for (int i = prevTileX - 1; i >= 0; i--)//moveLeft
    {
        if (board.gameBoard[i][tileY].piece == nullptr)
        {
            maxTileLeft++;
        }
        else { break; }
    }

    for (sf::Vector2i i = {prevTileX - 1, prevTileY - 1}; i.y >= 0 && i.x >= 0; i.x--, i.y--)//upLeft
    {
        if (board.gameBoard[i.x][i.y].piece == nullptr)
        {
            maxUpLeft++;
        }
        else { break; }
    }
    for (sf::Vector2i i = { prevTileX + 1, prevTileY - 1}; i.y >= 0 && i.x < board.sqCount; i.y--, i.x++)//upRight
    {
        if (board.gameBoard[i.x][i.y].piece == nullptr)
        {
            maxUpRight++;
        }
        else { break; }
    }
    for (sf::Vector2i i = { prevTileX + 1, prevTileY + 1 }; i.x < board.sqCount && i.y < board.sqCount; i.x++, i.y++)//downRight
    {
        if (board.gameBoard[i.x][i.y].piece == nullptr)
        {

            maxDownRight++;
        }
        else { break; }
    }
    for (sf::Vector2i i = { prevTileX - 1, prevTileY + 1 }; i.x >= 0 && i.y < board.sqCount; i.x--, i.y++)
    {
        if (board.gameBoard[i.x][i.y].piece == nullptr)
        {
            maxDownLeft++;
        }
        else { break; }
    }

    bool upLeft = (prevTileX - tileX <= maxUpLeft && prevTileY - tileY <= maxUpLeft && tileX < prevTileX && tileY < prevTileY && (prevTileY - tileY == prevTileX - tileX));
    bool upRight = (tileX - prevTileX <= maxUpRight && prevTileY - tileY <= maxUpRight && tileX > prevTileX && tileY < prevTileY && (prevTileY - tileY == tileX - prevTileX));
    bool downRight = (tileX - prevTileX <= maxDownRight && tileY - prevTileY <= maxDownRight && tileX > prevTileX && tileY > prevTileY && (tileY - prevTileY == tileX - prevTileX));
    bool downLeft = (prevTileX - tileX <= maxDownLeft && tileY - prevTileY <= maxDownLeft && tileX < prevTileX && tileY > prevTileY && (tileY - prevTileY == prevTileX - tileX));
    if (tileX == prevTileX && prevTileY - tileY <= maxTileUp && tileY < prevTileY)//up
    {
        printf("Up logic\n");
        return true;
    }
    else if (tileX == prevTileX && tileY - prevTileY <= maxTileDown && tileY > prevTileY)//down
    {
        printf("Down logic\n");

        return true;
    }
    else if (tileY == prevTileY && tileX - prevTileX <= maxTileRight && tileX > prevTileX)//right
    {
        printf("Right logic\n");

        return true;
    }
    else if (tileY == prevTileY && prevTileX - tileX <= maxTileLeft && tileX < prevTileX)//left
    {
        printf("Left logic\n");

        return true;
    }
    else if (upLeft || upRight || downRight || downLeft)
    {
        printf("Diag Logic: \n");
        if (board.gameBoard[tileX][tileY].piece == nullptr)
        {
            return true;
        }
        else if (board.gameBoard[tileX][tileY].piece->color != selectedPiece->color)
        {
            return true;
        }
    }
    else { return false; }

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