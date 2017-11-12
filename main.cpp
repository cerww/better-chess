#include <iostream>
#include <experimental\filesystem>
#include "chess_board.h"
#include "game.h"

int main(){
	if (glfwInit() == GLFW_FALSE) return -1;
	//std::experimental::filesystem::path k = std::experimental::filesystem::current_path;
	game g;
	g.run();
	chess_board b;
	b.getPiece({ 0,0 }) = chess_piece::BLACK_ROOK;
	b.getPiece({ 1,0 }) = chess_piece::BLACK_HORSE;
	b.getPiece({ 2,0 }) = chess_piece::BLACK_BISH;
	b.getPiece({ 3,0 }) = chess_piece::BLACK_QUEEN;
	b.getPiece({ 4,0 }) = chess_piece::BLACK_KING;
	b.getPiece({ 5,0 }) = chess_piece::BLACK_BISH;
	b.getPiece({ 6,0 }) = chess_piece::BLACK_HORSE;
	b.getPiece({ 7,0 }) = chess_piece::BLACK_ROOK;
	for(int i = 0;i<8;++i){
		b.getPiece({ i,1 }) = chess_piece::BLACK_PAWN;
		b.getPiece({ i,6 }) = chess_piece::WHITE_PAWN;
	}

	//b.getPiece({ 4,1 }) = chess_piece::NONE;
	//b.getPiece({ 4,3 }) = chess_piece::WHITE_QUEEN;

	b.getPiece({ 0,7 }) = chess_piece::WHITE_ROOK;
	b.getPiece({ 1,7 }) = chess_piece::WHITE_HORSE;
	b.getPiece({ 2,7 }) = chess_piece::WHITE_BISH;
	b.getPiece({ 3,7 }) = chess_piece::WHITE_QUEEN;
	b.getPiece({ 4,7 }) = chess_piece::WHITE_KING;
	b.getPiece({ 5,7 }) = chess_piece::WHITE_BISH;
	b.getPiece({ 6,7 }) = chess_piece::WHITE_HORSE;
	b.getPiece({ 7,7 }) = chess_piece::WHITE_ROOK;
	int qweuoyqwedas;
	std::cin >> qweuoyqwedas;
	return 0;
}