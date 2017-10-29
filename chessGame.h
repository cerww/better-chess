#pragma once
#include "boardGameBase.h"
#include "chess_board.h"
#include "cw/button.h"

class game;

class chessGame :
	public boardGameBase
{
public:
	chessGame(game&);
	void update() override final;
	void draw() override final;
private:
	static constexpr cw::vector2i s_outOfBoard = { 9,9 };
	std::vector<chess_board> m_boardHistory = std::vector<chess_board>(1,get_starting_board());
	cw::vector2i m_selected={};
	cw::vector2i m_mouseOver = { 9,9 };
	std::vector<cw::vector2i> m_moveableSpotsForSelectedPiece;
	game& m_game;
	size_t m_turns = 0;
	std::array<texture, 12> m_textures;
	button m_undoButton;
};

