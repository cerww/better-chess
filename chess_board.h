#pragma once
#include <vector>
#include <array>
#include "vectors.h"
#include <experimental\coroutine>
#include <experimental\generator>

enum class chess_piece:char{NONE,WHITE_PAWN, WHITE_HORSE, WHITE_QUEEN, WHITE_KING, WHITE_BISH, WHITE_ROOK,
							BLACK_PAWN, BLACK_HORSE, BLACK_QUEEN, BLACK_KING, BLACK_BISH, BLACK_ROOK
};

constexpr cw::vector2i horse_movements[8] = { {1,2},{-1,2},{-1,-2},{1,-2},{2,1},{2,-1},{-2,1},{-2,-1} };
constexpr cw::vector2i bish_movements[] = {{1,1},{1,-1},{-1,1},{-1,-1}};
constexpr cw::vector2i rook_movements[] = {{1,0},{0,1},{0,-1},{-1,0}};
constexpr cw::vector2i king_movements[] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};

constexpr uint8_t left_white_rook_bit	=	0b1;
constexpr uint8_t right_white_rook_bit =	0b10;
constexpr uint8_t left_black_rook_bit	=	0b100;
constexpr uint8_t right_black_rook_bit =	0b1000;
constexpr uint8_t white_king_bit		=	0b10000;
constexpr uint8_t black_king_bit		=	0b100000;

class chess_board {
public:
	chess_board() = default;
	decltype(auto) operator[](size_t index){
		return m_board[index];
	}
	chess_piece& getPiece(cw::vector2i spot){
		return m_board[spot.x][spot.y];
	};
	const chess_piece& getPiece(cw::vector2i spot) const{
		return m_board[spot.x][spot.y];
	};
	std::vector<cw::vector2i> get_moveable_spots(cw::vector2i)const;
	uint8_t castleing_status = 0;//left white, right white, left black, right black,white king, black king
	cw::vector2i prev_to = {};
	cw::vector2i prev_from = {};
private:
	std::array<std::array<chess_piece, 8>, 8> m_board = {};
	std::experimental::generator<cw::vector2i> get_moveable_spotsy(cw::vector2i)const;
};

std::pair<cw::vector2i, cw::vector2i> get_king_spots(const chess_board&);

bool is_valid_board_after_white_plays(const chess_board&);
bool is_valid_board_after_black_plays(const chess_board&);
bool is_same_colour(chess_piece, chess_piece);
bool is_black(chess_piece);
bool is_white(chess_piece);

template<bool is_special_move = false>
chess_board move_spot(chess_board b,cw::vector2i spot1, cw::vector2i spot2);

inline bool is_valid_spot(const cw::vector2i spot) {
	return spot.x < 8 && spot.x >= 0 && spot.y < 8 && spot.y >= 0;
}

chess_board get_starting_board();