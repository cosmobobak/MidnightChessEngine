//
// Created by Archishmaan Peyyety on 2/14/23.
//
#pragma once
const int PREVIOUS_BEST_MOVE_BONUS = 10'000'000;
const int PROMOTION_BONUS = PREVIOUS_BEST_MOVE_BONUS / 10;
const int MVV_LVA_BONUS = PROMOTION_BONUS / 10;
const int KILLER_MOVE_BONUS = MVV_LVA_BONUS / 10;
const int HISTORY_BONUS = -(KILLER_MOVE_BONUS / 10);
const int IN_OPP_PAWN_TERRITORY_PENALTY = -350;

const short NKILLERS = 2;

const int ORDERING_PAWN_VALUE = 100;
const int ORDERING_KNIGHT_VALUE = 320;
const int ORDERING_BISHOP_VALUE = 340;
const int ORDERING_ROOK_VALUE = 500;
const int ORDERING_QUEEN_VALUE = 900;
const int ORDERING_KING_VALUE = 1000;