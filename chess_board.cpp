#include "chess_board.h"
#include <future>
#include "randomThings.h"
#include <ppl.h>
#include <ppltaskscheduler.h>

chess_board get_starting_board() {
	chess_board retVal = {};
	retVal.getPiece({ 0,0 }) = chess_piece::BLACK_ROOK;
	retVal.getPiece({ 1,0 }) = chess_piece::BLACK_HORSE;
	retVal.getPiece({ 2,0 }) = chess_piece::BLACK_BISH;
	retVal.getPiece({ 3,0 }) = chess_piece::BLACK_QUEEN;
	retVal.getPiece({ 4,0 }) = chess_piece::BLACK_KING;
	retVal.getPiece({ 5,0 }) = chess_piece::BLACK_BISH;
	retVal.getPiece({ 6,0 }) = chess_piece::BLACK_HORSE;
	retVal.getPiece({ 7,0 }) = chess_piece::BLACK_ROOK;
	for (int i = 0; i<8; ++i) {
		retVal.getPiece({ i,1 }) = chess_piece::BLACK_PAWN;
		retVal.getPiece({ i,6 }) = chess_piece::WHITE_PAWN;
	}
	retVal.getPiece({ 0,7 }) = chess_piece::WHITE_ROOK;
	retVal.getPiece({ 1,7 }) = chess_piece::WHITE_HORSE;
	retVal.getPiece({ 2,7 }) = chess_piece::WHITE_BISH;
	retVal.getPiece({ 3,7 }) = chess_piece::WHITE_QUEEN;
	retVal.getPiece({ 4,7 }) = chess_piece::WHITE_KING;
	retVal.getPiece({ 5,7 }) = chess_piece::WHITE_BISH;
	retVal.getPiece({ 6,7 }) = chess_piece::WHITE_HORSE;
	retVal.getPiece({ 7,7 }) = chess_piece::WHITE_ROOK;
	return retVal;
}


std::pair<cw::vector2i, cw::vector2i> get_king_spots(const chess_board& board){
	cw::vector2i whiteKingSpot = {};
	cw::vector2i blackKingSpot = {};
	for (int x = 0; x<8; ++x) {
		for (int y = 0; y<8; ++y) {
			if (board.getPiece({ x,y }) == chess_piece::WHITE_KING)
				whiteKingSpot = { x,y };
			if (board.getPiece({ x,y }) == chess_piece::BLACK_KING)
				blackKingSpot = { x,y };
		}
	}return { whiteKingSpot,blackKingSpot };
}

bool is_valid_board_after_white_plays(const chess_board& board){
	auto whiteKingSpot = get_king_spots(board).first;
	for(int i = 0;i<8;++i){
		cw::vector2i next_spot = whiteKingSpot + king_movements[i];
		if(is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::BLACK_KING)
			return false;
		if (i < 4) {			
			next_spot = whiteKingSpot + bish_movements[i];
			while(is_valid_spot(next_spot)){
				if(board.getPiece(next_spot) == chess_piece::BLACK_BISH || board.getPiece(next_spot) == chess_piece::BLACK_QUEEN)
					return false;
				if (board.getPiece(next_spot) != chess_piece::NONE) 
					break;
				next_spot = next_spot + bish_movements[i];
			}
			next_spot = whiteKingSpot + rook_movements[i];
			while (is_valid_spot(next_spot)) {
				if (board.getPiece(next_spot) == chess_piece::BLACK_ROOK || board.getPiece(next_spot) == chess_piece::BLACK_QUEEN)
					return false;
				if (is_white(board.getPiece(next_spot))) break;
				next_spot = next_spot + rook_movements[i]; 
			}
		}
		next_spot = whiteKingSpot + horse_movements[i];
		if(is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::BLACK_HORSE)
			return false;
	}auto next_spot = whiteKingSpot + cw::vector2i{ 1,-1 };
	if (is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::BLACK_PAWN)
		return false;
	next_spot = whiteKingSpot + cw::vector2i{ -1,-1 };
	if (is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::BLACK_PAWN)
		return false;
	return true;
}

bool is_valid_board_after_black_plays(const chess_board& board){
	const auto blackKingSpot = get_king_spots(board).second;
	for (int i = 0; i<8; ++i) {
		cw::vector2i next_spot = blackKingSpot + king_movements[i];
		if (is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::WHITE_KING)
			return false;
		if (i < 4) {
			next_spot = blackKingSpot + bish_movements[i];
			while (is_valid_spot(next_spot)) {
				if (board.getPiece(next_spot) == chess_piece::WHITE_BISH || board.getPiece(next_spot) == chess_piece::WHITE_QUEEN)
					return false;
				if (board.getPiece(next_spot) != chess_piece::NONE) 
					break;
				next_spot = next_spot + bish_movements[i];
			}
			next_spot = blackKingSpot + rook_movements[i];
			while (is_valid_spot(next_spot)) {
				if (board.getPiece(next_spot) == chess_piece::WHITE_ROOK|| board.getPiece(next_spot) == chess_piece::WHITE_QUEEN)
					return false;
				if (board.getPiece(next_spot) != chess_piece::NONE) break;
				next_spot = next_spot + rook_movements[i];
			}
		}
		next_spot = blackKingSpot + horse_movements[i];
		if (is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::WHITE_HORSE)
			return false;		
	}
	auto next_spot = blackKingSpot + cw::vector2i{ 1,1 };
	if (is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::WHITE_PAWN)
		return false;
	next_spot = blackKingSpot + cw::vector2i{ -1,1 };
	if (is_valid_spot(next_spot) && board.getPiece(next_spot) == chess_piece::WHITE_PAWN)
		return false; 
	return true;
}

bool is_same_colour(chess_piece first, chess_piece second){
	return !(((int)first < 7) ^ ((int)second < 7)) && first!= chess_piece::NONE && second != chess_piece::NONE;
}

bool is_black(chess_piece p){
	return (int)p > 6;
}

bool is_white(chess_piece p){
	return ((int)p)<7 && p!=chess_piece::NONE;
}

template<bool is_special_move>
chess_board move_spot(chess_board b,cw::vector2i from, cw::vector2i to){
	if constexpr(!is_special_move){
		if(b.getPiece(from) == chess_piece::BLACK_KING){
			b.castleing_status |= black_king_bit;
			if(from == cw::vector2i(4,0) && std::abs(to.x - from.x) > 1)
				b = move_spot<true>(b, cw::vector2i(to.x > from.x ? 7 : 0, 0), { to.x > from.x ? 5 : 3 ,0 });
		}else if (b.getPiece(from) == chess_piece::WHITE_KING) {
			b.castleing_status |= white_king_bit;
			if(from == cw::vector2i(4, 7) && std::abs(to.x - from.x) > 1) 
				b = move_spot<true>(b, cw::vector2i(to.x > from.x ? 7 : 0, 7), { to.x > from.x ? 5 : 3 ,7 });
		}else if (b.getPiece(from) == chess_piece::BLACK_PAWN && b.getPiece(to) == chess_piece::NONE && from.y == 4 && from.x != to.x) {
			b = move_spot<true>(b, to, { to.x,to.y - 1 });
		}else if (b.getPiece(from) == chess_piece::WHITE_PAWN && b.getPiece(to) == chess_piece::NONE && from.y == 3 && from.x != to.x) {
			b = move_spot<true>(b, to, { to.x,to.y + 1 });
		}if (from == cw::vector2i(7, 7) || to == cw::vector2i(7,7))
			b.castleing_status |= right_white_rook_bit;
		else if (from == cw::vector2i(0, 7) || to == cw::vector2i(0,7))
			b.castleing_status |= left_white_rook_bit;
		else if (from == cw::vector2i(0, 0) || to == cw::vector2i(0,0))
			b.castleing_status |= left_black_rook_bit;
		else if (from == cw::vector2i(7, 0) || to == cw::vector2i(7,0))
			b.castleing_status |= right_black_rook_bit;
	}
	b.getPiece(to) = b.getPiece(from);
	b.getPiece(from) = chess_piece::NONE;
	b.prev_from = from;
	b.prev_to = to;
	if((b.getPiece(to) == chess_piece::BLACK_PAWN && to.y == 7) || (b.getPiece(to) == chess_piece::WHITE_PAWN && to.y == 0)){
		b.getPiece(to) = (chess_piece)((int)b.getPiece(to) + 2);
	}return b;
}


std::experimental::generator<cw::vector2i> chessMoveGenerator::get_moveable_spotsy(const chess_board& m_board,const cw::vector2i spot) const{
	const chess_piece piece = m_board.getPiece(spot);
	switch (piece)
	{
	case chess_piece::NONE:
		break;
	case chess_piece::WHITE_PAWN:
		if(m_board.getPiece({spot.x,spot.y-1}) == chess_piece::NONE){
			co_yield { spot.x,spot.y - 1 };
			if(spot.y==6 && m_board.getPiece({spot.x,spot.y-2}) == chess_piece::NONE)
				co_yield { spot.x,spot.y - 2};
		}
		if (spot.x + 1 < 8 && is_black(m_board.getPiece({ spot.x + 1,spot.y - 1 })))
			co_yield { spot.x + 1,spot.y - 1 };
		if (spot.x-1>=0 &&is_black(m_board.getPiece({ spot.x - 1,spot.y - 1 })))
			co_yield { spot.x - 1,spot.y - 1 };
		if(spot.y == 3){//en passant
			if (spot.x - 1 >= 0 && m_board.getPiece({ spot.x - 1,spot.y }) == chess_piece::BLACK_PAWN && m_board.prev_to == cw::vector2i{spot.x -1,spot.y} && m_board.prev_from == cw::vector2i(spot.x - 1,spot.y - 2))
				co_yield{ spot.x - 1,spot.y - 1 };
			if (spot.x + 1 < 8 && m_board.getPiece({ spot.x + 1,spot.y }) == chess_piece::BLACK_PAWN && m_board.prev_to == cw::vector2i{ spot.x + 1,spot.y } && m_board.prev_from == cw::vector2i(spot.x + 1, spot.y - 2))
				co_yield{ spot.x + 1,spot.y - 1 };
		}
		break;
	case chess_piece::WHITE_HORSE:
		for(int i = 0;i<8;++i){
			auto newSpot = spot + horse_movements[i];
			if(is_valid_spot(newSpot) && !is_same_colour(piece, m_board.getPiece(newSpot))){
				co_yield newSpot;
			}
		}
		break;
	case chess_piece::WHITE_QUEEN:
		for(int i = 0;i<4;++i){			
			auto newSpot = spot + rook_movements[i];
			while (is_valid_spot(newSpot)) {
				if(m_board.getPiece(newSpot) == chess_piece::NONE){
					co_yield newSpot;
					newSpot = newSpot + rook_movements[i];
				}else if(!is_same_colour(piece, m_board.getPiece(newSpot))){
					co_yield newSpot;
					break;
				}else{
					break;
				}
			}
			newSpot = spot + bish_movements[i]; 
			while (is_valid_spot(newSpot)) {
				if (m_board.getPiece(newSpot) == chess_piece::NONE) {
					co_yield newSpot;
					newSpot = newSpot + bish_movements[i];
				}else if (!is_same_colour(piece, m_board.getPiece(newSpot))) {
					co_yield newSpot;
					break;
				}else {
					break;
				}
			}
		}
		break;
	case chess_piece::WHITE_KING:
		for (int i = 0; i<8; ++i) {
			const cw::vector2i newSpot = spot + king_movements[i];
			if (is_valid_spot(newSpot) && !is_same_colour(piece, m_board.getPiece(newSpot)))
				co_yield newSpot;
		}if (spot == cw::vector2i(4,7) && !(m_board.castleing_status & (right_white_rook_bit | white_king_bit))&& m_board.getPiece({5,7}) == chess_piece::NONE && m_board.getPiece({6,7}) == chess_piece::NONE && m_board.getPiece({7,7}) == chess_piece::WHITE_ROOK){
			co_yield { 6,7 };
		}
		if(spot == cw::vector2i(4,7) && !(m_board.castleing_status & (left_white_rook_bit | white_king_bit))&& m_board.getPiece({3,7}) == chess_piece::NONE &&m_board.getPiece({2,7}) == chess_piece::NONE &&m_board.getPiece({1,7}) == chess_piece::NONE && m_board.getPiece({0,7}) == chess_piece::WHITE_ROOK){
			co_yield{ 2,7 };
		}
		break;
	case chess_piece::WHITE_BISH:
		for(int i = 0;i<4;++i){
			auto newSpot = spot + bish_movements[i];
			while (newSpot.x < 8 && newSpot.y < 8 && newSpot.x >= 0 && newSpot.y >= 0) {
				if (m_board.getPiece(newSpot) == chess_piece::NONE) {
					co_yield newSpot;
					newSpot = newSpot + bish_movements[i];
				}else if (!is_same_colour(piece, m_board.getPiece(newSpot))) {
					co_yield newSpot;
					break;
				}else {
					break;
				}
			}
		}
		break;
	case chess_piece::WHITE_ROOK:
		for (int i = 0; i<4; ++i) {
			auto newSpot = spot + rook_movements[i];
			while (newSpot.x < 8 && newSpot.y < 8 && newSpot.x >= 0 && newSpot.y >= 0) {
				if (m_board.getPiece(newSpot) == chess_piece::NONE) {
					co_yield newSpot;
					newSpot = newSpot + rook_movements[i];
				}else if (!is_same_colour(piece, m_board.getPiece(newSpot))) {
					co_yield newSpot;
					break;
				}
				else {
					break;
				}
			}
		}
		break;
	case chess_piece::BLACK_PAWN:
		if(m_board.getPiece({spot.x,spot.y + 1}) == chess_piece::NONE){
			co_yield { spot.x,spot.y + 1 };
			if(spot.y==1&& m_board.getPiece({spot.x,spot.y+2}) == chess_piece::NONE)
				co_yield { spot.x,spot.y + 2 };
		}
		if (spot.x + 1 < 8 && (is_white(m_board.getPiece({ spot.x + 1,spot.y + 1 }))))
			co_yield { spot.x + 1,spot.y + 1 };
		if (spot.x - 1 >= 0 && (is_white(m_board.getPiece({ spot.x - 1,spot.y + 1 }))))
			co_yield { spot.x - 1,spot.y + 1 };
		if (spot.y == 4) {//en passant
			if (spot.x - 1 >= 0 && m_board.getPiece({ spot.x - 1,spot.y }) == chess_piece::WHITE_PAWN&& m_board.prev_to == cw::vector2i{ spot.x - 1,spot.y } &&m_board.prev_from == cw::vector2i(spot.x - 1, spot.y + 2))
				co_yield{ spot.x - 1,spot.y + 1 };
			if (spot.x + 1 < 8 && m_board.getPiece({ spot.x + 1,spot.y }) == chess_piece::WHITE_PAWN&& m_board.prev_to == cw::vector2i{ spot.x + 1,spot.y } && m_board.prev_from == cw::vector2i(spot.x + 1, spot.y + 2))
				co_yield{ spot.x + 1,spot.y + 1 };
		}
		break;
	case chess_piece::BLACK_HORSE:
		for (int i = 0; i<8; ++i) {
			auto newSpot = spot + horse_movements[i];
			if (is_valid_spot(newSpot) && !is_same_colour(piece, m_board.getPiece(newSpot))) {
				co_yield newSpot;
			}
		}
		break;
	case chess_piece::BLACK_QUEEN:
		for (int i = 0; i<4; ++i) {
			auto newSpot = spot + rook_movements[i];
			while (is_valid_spot(newSpot)) {
				if (m_board.getPiece(newSpot) == chess_piece::NONE) {
					co_yield newSpot;
					newSpot = newSpot + rook_movements[i];
				}
				else if (!is_same_colour(piece, m_board.getPiece(newSpot))) {
					co_yield newSpot;
					break;
				}else {
					break;
				}
			}
			newSpot = spot + bish_movements[i];
			while (is_valid_spot(newSpot)) {
				if (m_board.getPiece(newSpot) == chess_piece::NONE) {
					co_yield newSpot;
					newSpot = newSpot + bish_movements[i];
				}
				else if (!is_same_colour(piece, m_board.getPiece(newSpot))) {
					co_yield newSpot;
					break;
				}
				else {
					break;
				}
			}
		}
		break;
	case chess_piece::BLACK_KING:
		for (int i = 0; i<8; ++i){
			cw::vector2i newSpot = spot + king_movements[i];
			if (is_valid_spot(newSpot) && !is_same_colour(piece, m_board.getPiece(newSpot)))
				co_yield newSpot;
		}if (spot == cw::vector2i(4, 0) && !(m_board.castleing_status & (right_black_rook_bit | black_king_bit)) && m_board.getPiece({ 5,0 }) == chess_piece::NONE && m_board.getPiece({ 6,0}) == chess_piece::NONE && m_board.getPiece({ 7,0 }) == chess_piece::BLACK_ROOK) {
			co_yield{ 6,0 };
		}
		if (spot == cw::vector2i(4, 0) && !(m_board.castleing_status & (left_black_rook_bit | black_king_bit)) && m_board.getPiece({ 3,0 }) == chess_piece::NONE && m_board.getPiece({ 2,0 }) == chess_piece::NONE && m_board.getPiece({ 1,0 }) == chess_piece::NONE && m_board.getPiece({ 0,0 }) == chess_piece::BLACK_ROOK) {
			co_yield{ 2,0 };
		}
		break;
	case chess_piece::BLACK_BISH:
		for (int i = 0; i<4; ++i) {
			auto newSpot = spot + bish_movements[i];
			while (is_valid_spot(newSpot)) {
				if (m_board.getPiece(newSpot) == chess_piece::NONE) {
					co_yield newSpot;
					newSpot = newSpot + bish_movements[i];
				}
				else if (!is_same_colour(piece, m_board.getPiece(newSpot))) {
					co_yield newSpot;
					break;
				}
				else {
					break;
				}
			}
		}
		break;
	case chess_piece::BLACK_ROOK:
		for (int i = 0; i<4; ++i) {
			auto newSpot = spot + rook_movements[i];
			while (is_valid_spot(newSpot)) {
				if (m_board.getPiece(newSpot) == chess_piece::NONE) {
					co_yield newSpot;
					newSpot = newSpot + rook_movements[i];
				}
				else if (!is_same_colour(piece, m_board.getPiece(newSpot))) {
					co_yield newSpot;
					break;
				}
				else {
					break;
				}
			}
		}
		break;
	default:
		break;
	}
	//return retVal;
}

std::vector<cw::vector2i> chessMoveGenerator::get_moveable_spots(const chess_board& m_board,const cw::vector2i spot1)const{
	std::vector<cw::vector2i> retVal;
	retVal.reserve(10);
	std::vector<concurrency::task<std::pair<bool,cw::vector2i>>> worky;
	worky.reserve(10);

	for (auto&& spot : get_moveable_spotsy(m_board,spot1)) {
		if (is_black(m_board.getPiece(spot1))) {
			//if (is_valid_board_after_black_plays(move_spot(*this, spot1, spot)))
			//retVal.push_back(spot);	
			worky.push_back(concurrency::create_task([&,t_spot = spot]()->std::pair<bool,cw::vector2i>{
				return { is_valid_board_after_black_plays(move_spot<false>(m_board, spot1, t_spot)),t_spot };
			}));
		}
		else {
			//if (is_valid_board_after_white_plays(move_spot(*this, spot1, spot)))
			//retVal.push_back(spot);
			worky.push_back(concurrency::create_task([&,t_spot = spot]()->std::pair<bool,cw::vector2i>{
				return { is_valid_board_after_white_plays(move_spot<false>(m_board, spot1, t_spot)),t_spot }; 
			}));
		}
	}
	concurrency::when_all(worky.begin(), worky.end()).then([&](std::vector<std::pair<bool,cw::vector2i>> stuffs){
		retVal.reserve(stuffs.size());
		for(const auto& i:stuffs){
			if(i.first){
				retVal.push_back(i.second);
			}
		}
	}).wait();

	return retVal;
}