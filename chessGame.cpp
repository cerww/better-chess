#include "chessGame.h"
#include "cw/Rectangle.h"
#include "game.h"
#include "randomThings.h"

chessGame::chessGame(game & g):
	m_game(g)
	//,m_undoButton(glm::vec4{1,2,3,4},imgLoader::loadPNG(""),Color(),[](){},Color())
{	//*
	m_textures[0] = imgLoader::loadPNG("pawn.png");
	m_textures[1] = imgLoader::loadPNG("horse.png");
	m_textures[2] = imgLoader::loadPNG("queen.png");
	m_textures[3] = imgLoader::loadPNG("king.png");
	m_textures[4] = imgLoader::loadPNG("bish.png");
	m_textures[5] = imgLoader::loadPNG("rook.png");
	//*/
}

void chessGame::update(){
	const auto mousePos = m_game.getCamera().scrnToWorld(m_game.getWindow().getMousePos());
	if (mousePos.x <= (8* s_pieceWidth) + s_screen_padding && mousePos.y <= (8* s_pieceWidth) + s_screen_padding && mousePos.x > s_screen_padding && mousePos.y > s_screen_padding){
		m_mouseOver = { ((int)mousePos.x - s_screen_padding) / s_pieceWidth,((int)mousePos.y - s_screen_padding) / s_pieceWidth };
	}else{
		m_mouseOver = s_outOfBoard;
	}
	if (m_game.getWindow().getMouseButton(mouseB::LEFT) && m_mouseOver != s_outOfBoard){
		if(is_in(m_moveableSpotsForSelectedPiece,m_mouseOver)){
			m_boardHistory.erase(m_boardHistory.begin() + m_turns + 1, m_boardHistory.end());
			m_boardHistory.push_back(move_spot<false>(m_boardHistory[m_turns], m_selected, m_mouseOver));
			++m_turns;
			m_moveableSpotsForSelectedPiece.clear();
		}else if((m_turns%2 == 0 && is_white(m_boardHistory[m_turns].getPiece(m_mouseOver))) || (m_turns % 2 == 1 && is_black(m_boardHistory[m_turns].getPiece(m_mouseOver)))){
			m_selected = m_mouseOver;
			m_moveableSpotsForSelectedPiece = m_boardHistory[m_turns].get_moveable_spots(m_selected);
		}
	}
}

void chessGame::draw(){
	//draw board
	for(int i = 0;i<64;++i){
		if(m_boardHistory[m_turns][i % 8][i/8] != chess_piece::NONE){
			m_game.getRenderer().draw({ (i % 8) * s_pieceWidth+ s_screen_padding,(i / 8) * s_pieceWidth + s_screen_padding,s_pieceWidth,s_pieceWidth }, fullPicUV, m_textures[((int)m_boardHistory[m_turns][i % 8][i / 8] - 1) % 6].id, is_white(m_boardHistory[m_turns][i % 8][i / 8]) ? Color{200,200,200,255} : Color{20,20,20,255}, 1);
		}
	}
	for(auto spot:m_moveableSpotsForSelectedPiece){
		m_game.getRenderer().draw({ spot.x * s_pieceWidth + s_screen_padding,spot.y * s_pieceWidth + s_screen_padding,s_pieceWidth,s_pieceWidth }, fullPicUV, Rectangle::getFlatColor().id, { 200,90,20,200 }, 2);
	} 
	if(m_mouseOver != s_outOfBoard){
		m_game.getRenderer().draw({m_mouseOver.x*s_pieceWidth + s_screen_padding,m_mouseOver.y*s_pieceWidth + s_screen_padding,s_pieceWidth,s_pieceWidth },fullPicUV,Rectangle::getFlatColor().id,{50,50,50,255},3);
	}
}
