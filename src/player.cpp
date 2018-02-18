#include <sstream>

#include "player.hpp"

Player::Player(int id, Piece piece) : id(id), piece(piece), name("Player " + std::to_string(id)) {}

Player::Player(int id, Piece piece, const std::string& name) : id(id), piece(piece), name(name) {}

Player::~Player() {}

std::string Player::str() const
{
    std::ostringstream oss;
    oss << "{ id: " << id << ", piece: " << static_cast<char>(piece) << " }";
    return oss.str();
}