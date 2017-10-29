#include "chessGame.h"
#include "cw/Rectangle.h"
#include "game.h"
#include "randomThings.h"

chessGame::chessGame(game & g):
	m_game(g)
	//,m_undoButton(glm::vec4{1,2,3,4},imgLoader::loadPNG(""),Color(),[](){},Color())
{
	
}

void chessGame::update(){
	const auto mousePos = m_game.getWindow().getMousePos();
	if (mousePos.x < 655 && mousePos.y < 655 && mousePos.x > 25 && mousePos.y > 25){
		m_mouseOver = { ((int)mousePos.x - 25) / 70,((int)mousePos.y - 25) / 70 };
	}else{
		m_mouseOver = s_outOfBoard;
	}
	if (m_game.getWindow().getMouseButton(mouseB::LEFT) && m_mouseOver != s_outOfBoard){
		if(is_in(m_moveableSpotsForSelectedPiece,m_mouseOver)){//;-; c++ pls
			m_boardHistory.erase(m_boardHistory.begin() + m_turns + 1, m_boardHistory.end());
			m_boardHistory.push_back(move_spot(m_boardHistory[m_turns], m_selected, m_mouseOver));
			++m_turns;
			m_moveableSpotsForSelectedPiece.clear();
		}else if(m_turns%2 == 0 && is_white(m_boardHistory[m_turns].getPiece(m_mouseOver))){
			m_selected = m_mouseOver;
			m_moveableSpotsForSelectedPiece = m_boardHistory[m_turns].get_moveable_spots(m_selected);
		}else if(m_turns%2 == 1 && is_black(m_boardHistory[m_turns].getPiece(m_mouseOver))){
			m_selected = m_mouseOver;
			m_moveableSpotsForSelectedPiece = m_boardHistory[m_turns].get_moveable_spots(m_selected);
		}
	}
}

void chessGame::draw(){
	//draw board
	for(int i = 0;i<64;++i){
		if(m_boardHistory[m_turns][i % 8][i/8] != chess_piece::NONE){
			m_game.getRenderer().draw({ (i % 8) * 70+ 25,(i / 8) * 70 + 25,70,70 }, fullPicUV, m_textures[((int)m_boardHistory[m_turns][i % 8][i / 8] - 1) % 6].id, is_white(m_boardHistory[m_turns][i % 8][i / 8]) ? colours::WHITE : colours::BLACK, 1);
		}
	}
	for(auto spot:m_moveableSpotsForSelectedPiece){
		m_game.getRenderer().draw({ spot.x * 70 + 25,spot.y * 70 + 25,70,70 }, fullPicUV, Rectangle::getFlatColor().id, { 200,90,20,200 }, 2);
	}
}
