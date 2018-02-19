#include "player_random.hpp"

RandomPlayer::RandomPlayer(int id, Piece piece) :
    Player(id, piece), gen(rd()), dis(0, 2) {}

RandomPlayer::RandomPlayer(int id, Piece piece, const std::string& name) :
    Player(id, piece, name), gen(rd()), dis(0, 2) {}

RandomPlayer::~RandomPlayer() {}

Move RandomPlayer::getMove(const Board& board)
{
    while (true)
    {
        int i = dis(gen);
        int j = dis(gen);
        if (board.getPiece(i, j) == Piece::EMPTY)
            return {i, j, piece};
    }
}