//
// Created by Archishmaan on 12/21/22.
//

#include "position.h"

template<Color color>
int evaluateOneSide(Position& board) {
	// TODO: better ways to handle mate, this is not ideal and can result in mis-evaluations of a position.
	int usPawns = pop_count(board.bitboard_of(color, PAWN));
	int usKnight = pop_count(board.bitboard_of(color, KNIGHT));
	int usBishop = pop_count(board.bitboard_of(color, BISHOP));
	int usRook = pop_count(board.bitboard_of(color, ROOK));
	int usQueen = pop_count(board.bitboard_of(color, QUEEN));
	int usCheck = board.in_check<color>() ? -1: 0;

	return usPawns + (3 * (usKnight + usBishop)) + (5 * usRook) + (8 * usQueen) + usCheck;
}

template<Color color>
int evaluate(Position& board) {
	int usPawns = pop_count(board.bitboard_of(color, PAWN));
	int usKnight = pop_count(board.bitboard_of(color, KNIGHT));
	int usBishop = pop_count(board.bitboard_of(color, BISHOP));
	int usRook = pop_count(board.bitboard_of(color, ROOK));
	int usQueen = pop_count(board.bitboard_of(color, QUEEN));
	int usCheck = board.in_check<color>() ? -1: 0;

	int themPawns = pop_count(board.bitboard_of(~color, PAWN));
	int themKnight = pop_count(board.bitboard_of(~color, KNIGHT));
	int themBishop = pop_count(board.bitboard_of(~color, BISHOP));
	int themRook = pop_count(board.bitboard_of(~color, ROOK));
	int themQueen = pop_count(board.bitboard_of(~color, QUEEN));
	int themCheck = board.in_check<~color>() ? -1: 0;

	int usMaterial = usPawns + (3 * (usKnight + usBishop)) + (5 * usRook) + (8 * usQueen) + usCheck;
	int themMaterial = themPawns + (3 * (themKnight + themBishop)) + (5 * themRook) + (8 * themQueen) + themCheck;
	return usMaterial - themMaterial;
	//return evaluateOneSide<color>(board) - evaluateOneSide<~color>(board);
}
