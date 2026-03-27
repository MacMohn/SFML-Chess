#include "Piece.h"

Piece::Piece(sf::Texture& texture, sf::Vector2f position, PieceType t, PieceColor c) : sprite(texture), type(t), color(c)
{
    sprite.setTextureRect({ {0,0}, {100,100} });
    sprite.setPosition(position);
}

void Piece::Draw(sf::RenderWindow& window)
{
        window.draw(sprite);
}
