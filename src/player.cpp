#include <sstream>

#include "player.hpp"

Player::Player(int id, Piece piece) : id(id), piece(piece) {}

std::string Player::str() const
{
    std::ostringstream oss;
    oss << "id: " << id << ", piece: " << static_cast<char>(piece);
    return oss.str();
}