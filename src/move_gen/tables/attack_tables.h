#pragma once
#pragma once

#include "../types/types.h"
#include "../../board/types/bitboard.h"
#include "../../board/types/piece.h"
#include "../../board/constants/zobrist_constants.h"

namespace tables {
	namespace {

		constexpr usize ROOK_TABLE_SIZE = 4096;
		constexpr usize BISHOP_TABLE_SIZE = 512;

		constexpr array<i32, NSQUARES> ROOK_SHIFTS = {
				52, 53, 53, 53, 53, 53, 53, 52,
				53, 54, 54, 54, 54, 54, 54, 53,
				53, 54, 54, 54, 54, 54, 54, 53,
				53, 54, 54, 54, 54, 54, 54, 53,
				53, 54, 54, 54, 54, 54, 54, 53,
				53, 54, 54, 54, 54, 54, 54, 53,
				53, 54, 54, 54, 54, 54, 54, 53,
				52, 53, 53, 53, 53, 53, 53, 52,
		};

		constexpr array<i32, NSQUARES> BISHOP_SHIFTS = {
				58, 59, 59, 59, 59, 59, 59, 58,
				59, 59, 59, 59, 59, 59, 59, 59,
				59, 59, 57, 57, 57, 57, 59, 59,
				59, 59, 57, 55, 55, 57, 59, 59,
				59, 59, 57, 55, 55, 57, 59, 59,
				59, 59, 57, 57, 57, 57, 59, 59,
				59, 59, 59, 59, 59, 59, 59, 59,
				58, 59, 59, 59, 59, 59, 59, 58,
		};

		constexpr array<Bitboard, NSQUARES> KING_ATTACKS = {
				0x302, 0x705, 0xe0a, 0x1c14,
				0x3828, 0x7050, 0xe0a0, 0xc040,
				0x30203, 0x70507, 0xe0a0e, 0x1c141c,
				0x382838, 0x705070, 0xe0a0e0, 0xc040c0,
				0x3020300, 0x7050700, 0xe0a0e00, 0x1c141c00,
				0x38283800, 0x70507000, 0xe0a0e000, 0xc040c000,
				0x302030000, 0x705070000, 0xe0a0e0000, 0x1c141c0000,
				0x3828380000, 0x7050700000, 0xe0a0e00000, 0xc040c00000,
				0x30203000000, 0x70507000000, 0xe0a0e000000, 0x1c141c000000,
				0x382838000000, 0x705070000000, 0xe0a0e0000000, 0xc040c0000000,
				0x3020300000000, 0x7050700000000, 0xe0a0e00000000, 0x1c141c00000000,
				0x38283800000000, 0x70507000000000, 0xe0a0e000000000, 0xc040c000000000,
				0x302030000000000, 0x705070000000000, 0xe0a0e0000000000, 0x1c141c0000000000,
				0x3828380000000000, 0x7050700000000000, 0xe0a0e00000000000, 0xc040c00000000000,
				0x203000000000000, 0x507000000000000, 0xa0e000000000000, 0x141c000000000000,
				0x2838000000000000, 0x5070000000000000, 0xa0e0000000000000, 0x40c0000000000000,
		};

		constexpr array<Bitboard, NSQUARES> KNIGHT_ATTACKS = {
				0x20400, 0x50800, 0xa1100, 0x142200,
				0x284400, 0x508800, 0xa01000, 0x402000,
				0x2040004, 0x5080008, 0xa110011, 0x14220022,
				0x28440044, 0x50880088, 0xa0100010, 0x40200020,
				0x204000402, 0x508000805, 0xa1100110a, 0x1422002214,
				0x2844004428, 0x5088008850, 0xa0100010a0, 0x4020002040,
				0x20400040200, 0x50800080500, 0xa1100110a00, 0x142200221400,
				0x284400442800, 0x508800885000, 0xa0100010a000, 0x402000204000,
				0x2040004020000, 0x5080008050000, 0xa1100110a0000, 0x14220022140000,
				0x28440044280000, 0x50880088500000, 0xa0100010a00000, 0x40200020400000,
				0x204000402000000, 0x508000805000000, 0xa1100110a000000, 0x1422002214000000,
				0x2844004428000000, 0x5088008850000000, 0xa0100010a0000000, 0x4020002040000000,
				0x400040200000000, 0x800080500000000, 0x1100110a00000000, 0x2200221400000000,
				0x4400442800000000, 0x8800885000000000, 0x100010a000000000, 0x2000204000000000,
				0x4020000000000, 0x8050000000000, 0x110a0000000000, 0x22140000000000,
				0x44280000000000, 0x0088500000000000, 0x0010a00000000000, 0x20400000000000
		};

		constexpr array<Bitboard, NSQUARES> WHITE_PAWN_ATTACKS = {
				0x200, 0x500, 0xa00, 0x1400,
				0x2800, 0x5000, 0xa000, 0x4000,
				0x20000, 0x50000, 0xa0000, 0x140000,
				0x280000, 0x500000, 0xa00000, 0x400000,
				0x2000000, 0x5000000, 0xa000000, 0x14000000,
				0x28000000, 0x50000000, 0xa0000000, 0x40000000,
				0x200000000, 0x500000000, 0xa00000000, 0x1400000000,
				0x2800000000, 0x5000000000, 0xa000000000, 0x4000000000,
				0x20000000000, 0x50000000000, 0xa0000000000, 0x140000000000,
				0x280000000000, 0x500000000000, 0xa00000000000, 0x400000000000,
				0x2000000000000, 0x5000000000000, 0xa000000000000, 0x14000000000000,
				0x28000000000000, 0x50000000000000, 0xa0000000000000, 0x40000000000000,
				0x200000000000000, 0x500000000000000, 0xa00000000000000, 0x1400000000000000,
				0x2800000000000000, 0x5000000000000000, 0xa000000000000000, 0x4000000000000000,
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
		};

		constexpr array<Bitboard, NSQUARES> BLACK_PAWN_ATTACKS = {
				0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
				0x2, 0x5, 0xa, 0x14, 0x28, 0x50, 0xa0, 0x40,
				0x200, 0x500, 0xa00, 0x1400,
				0x2800, 0x5000, 0xa000, 0x4000,
				0x20000, 0x50000, 0xa0000, 0x140000,
				0x280000, 0x500000, 0xa00000, 0x400000,
				0x2000000, 0x5000000, 0xa000000, 0x14000000,
				0x28000000, 0x50000000, 0xa0000000, 0x40000000,
				0x200000000, 0x500000000, 0xa00000000, 0x1400000000,
				0x2800000000, 0x5000000000, 0xa000000000, 0x4000000000,
				0x20000000000, 0x50000000000, 0xa0000000000, 0x140000000000,
				0x280000000000, 0x500000000000, 0xa00000000000, 0x400000000000,
				0x2000000000000, 0x5000000000000, 0xa000000000000, 0x14000000000000,
				0x28000000000000, 0x50000000000000, 0xa0000000000000, 0x40000000000000,
		};

		constexpr array<Bitboard, NSQUARES> BISHOP_MAGICS = {
				0x0002020202020200, 0x0002020202020000, 0x0004010202000000, 0x0004040080000000,
				0x0001104000000000, 0x0000821040000000, 0x0000410410400000, 0x0000104104104000,
				0x0000040404040400, 0x0000020202020200, 0x0000040102020000, 0x0000040400800000,
				0x0000011040000000, 0x0000008210400000, 0x0000004104104000, 0x0000002082082000,
				0x0004000808080800, 0x0002000404040400, 0x0001000202020200, 0x0000800802004000,
				0x0000800400A00000, 0x0000200100884000, 0x0000400082082000, 0x0000200041041000,
				0x0002080010101000, 0x0001040008080800, 0x0000208004010400, 0x0000404004010200,
				0x0000840000802000, 0x0000404002011000, 0x0000808001041000, 0x0000404000820800,
				0x0001041000202000, 0x0000820800101000, 0x0000104400080800, 0x0000020080080080,
				0x0000404040040100, 0x0000808100020100, 0x0001010100020800, 0x0000808080010400,
				0x0000820820004000, 0x0000410410002000, 0x0000082088001000, 0x0000002011000800,
				0x0000080100400400, 0x0001010101000200, 0x0002020202000400, 0x0001010101000200,
				0x0000410410400000, 0x0000208208200000, 0x0000002084100000, 0x0000000020880000,
				0x0000001002020000, 0x0000040408020000, 0x0004040404040000, 0x0002020202020000,
				0x0000104104104000, 0x0000002082082000, 0x0000000020841000, 0x0000000000208800,
				0x0000000010020200, 0x0000000404080200, 0x0000040404040400, 0x0002020202020200
		};

		constexpr array<Bitboard, NSQUARES> ROOK_MAGICS = {
				0x0080001020400080, 0x0040001000200040, 0x0080081000200080, 0x0080040800100080,
				0x0080020400080080, 0x0080010200040080, 0x0080008001000200, 0x0080002040800100,
				0x0000800020400080, 0x0000400020005000, 0x0000801000200080, 0x0000800800100080,
				0x0000800400080080, 0x0000800200040080, 0x0000800100020080, 0x0000800040800100,
				0x0000208000400080, 0x0000404000201000, 0x0000808010002000, 0x0000808008001000,
				0x0000808004000800, 0x0000808002000400, 0x0000010100020004, 0x0000020000408104,
				0x0000208080004000, 0x0000200040005000, 0x0000100080200080, 0x0000080080100080,
				0x0000040080080080, 0x0000020080040080, 0x0000010080800200, 0x0000800080004100,
				0x0000204000800080, 0x0000200040401000, 0x0000100080802000, 0x0000080080801000,
				0x0000040080800800, 0x0000020080800400, 0x0000020001010004, 0x0000800040800100,
				0x0000204000808000, 0x0000200040008080, 0x0000100020008080, 0x0000080010008080,
				0x0000040008008080, 0x0000020004008080, 0x0000010002008080, 0x0000004081020004,
				0x0000204000800080, 0x0000200040008080, 0x0000100020008080, 0x0000080010008080,
				0x0000040008008080, 0x0000020004008080, 0x0000800100020080, 0x0000800041000080,
				0x00FFFCDDFCED714A, 0x007FFCDDFCED714A, 0x003FFFCDFFD88096, 0x0000040810002101,
				0x0001000204080011, 0x0001000204000801, 0x0001000082000401, 0x0001FFFAABFAD1A2
		};

		[[nodiscard]] constexpr Bitboard board_edge(Direction D) {
			if (D == NORTH) return MASK_RANK[RANK8];
			else if (D == SOUTH) return MASK_RANK[RANK1];
			else if (D == EAST) return MASK_FILE[HFILE];
			else if (D == WEST) return MASK_FILE[AFILE];

			else if (D == NORTH_EAST) return MASK_RANK[RANK8] | MASK_FILE[HFILE];
			else if (D == NORTH_WEST) return MASK_RANK[RANK8] | MASK_FILE[AFILE];
			else if (D == SOUTH_EAST) return MASK_RANK[RANK1] | MASK_FILE[HFILE];
			else if (D == SOUTH_WEST) return MASK_RANK[RANK1] | MASK_FILE[AFILE];

			return 0;
		}

		[[nodiscard]] consteval Bitboard empty_board_rook_attacks(Square square) {
			return MASK_RANK[rank_of(square)] ^ MASK_FILE[file_of(square)];
		}

		[[nodiscard]] consteval Bitboard empty_board_bishop_attacks(Square square) {
			return MASK_DIAGONAL[diagonal_of(square)] ^ MASK_ANTI_DIAGONAL[anti_diagonal_of(square)];
		}

		[[nodiscard]] consteval array<Bitboard, NSQUARES> generate_rook_attack_masks() {
			array<Bitboard, NSQUARES> rook_attack_masks{};
			for (Square sq = a1; sq < NSQUARES; sq++) {
				Bitboard edges = 	((board_edge(NORTH) | board_edge(SOUTH)) & ~MASK_RANK[rank_of(sq)]) |
									((board_edge(EAST) 	| board_edge(WEST))  & ~MASK_FILE[file_of(sq)]);
				rook_attack_masks[sq] = empty_board_rook_attacks(sq) & ~edges;
			}
			return rook_attack_masks;
		}

		[[nodiscard]] consteval array<Bitboard, NSQUARES> generate_bishop_attack_masks() {
			array<Bitboard, NSQUARES> bishop_attack_masks{};
			for (Square sq = a1; sq < NSQUARES; sq++) {
				Bitboard edges = board_edge(NORTH) | board_edge(SOUTH) | board_edge(EAST) | board_edge(WEST);
				bishop_attack_masks[sq] = empty_board_bishop_attacks(sq) & ~edges;
			}
			return bishop_attack_masks;
		}

		constexpr array<Bitboard, NSQUARES> rook_attack_masks = generate_rook_attack_masks();
		constexpr array<Bitboard, NSQUARES> bishop_attack_masks = generate_bishop_attack_masks();

		[[nodiscard]] consteval Bitboard generate_slow_sliding_attacks(Square sq, Direction direction, Bitboard occupancy) {
			Bitboard attacks{};

			Bitboard blockers = board_edge(direction);
			Bitboard square_bb = square_to_bitboard(sq);

			if ((blockers & square_bb) != 0) return attacks;

			blockers |= occupancy;

			do {
				square_bb = shift(direction, square_bb);
				attacks |= square_bb;
			} while ((blockers & square_bb) == 0);

			return attacks;
		}

		[[nodiscard]] consteval Bitboard generate_slow_rook_attacks(Square sq, Bitboard occupancy) {
			return generate_slow_sliding_attacks(sq, NORTH, occupancy) |
				   generate_slow_sliding_attacks(sq, SOUTH, occupancy) |
				   generate_slow_sliding_attacks(sq, EAST, occupancy) |
				   generate_slow_sliding_attacks(sq, WEST, occupancy);
		}

		[[nodiscard]] consteval Bitboard generate_slow_bishop_attacks(Square sq, Bitboard occupancy) {
			return generate_slow_sliding_attacks(sq, NORTH_EAST, occupancy) |
				   generate_slow_sliding_attacks(sq, NORTH_WEST, occupancy) |
				   generate_slow_sliding_attacks(sq, SOUTH_EAST, occupancy) |
				   generate_slow_sliding_attacks(sq, SOUTH_WEST, occupancy);
		}


		[[nodiscard]] consteval array<array<Bitboard, ROOK_TABLE_SIZE>, NSQUARES> generate_rook_attack_table() {
			array<array<Bitboard, ROOK_TABLE_SIZE>, NSQUARES> rook_attack_table{};
			Bitboard subset{}, index{};

			for (Square sq = a1; sq < NSQUARES; sq++) {
				subset = 0;
				do {
					index = subset;
					index = index * ROOK_MAGICS[sq];
					index = index >> ROOK_SHIFTS[sq];
					rook_attack_table[sq][index] = generate_slow_rook_attacks(sq, subset);
					subset = (subset - rook_attack_masks[sq]) & rook_attack_masks[sq];
				} while (subset);
			}
			return rook_attack_table;
		}

		[[nodiscard]] consteval array<array<Bitboard, BISHOP_TABLE_SIZE>, NSQUARES> generate_bishop_attack_table() {
			array<array<Bitboard, BISHOP_TABLE_SIZE>, NSQUARES> bishop_attack_table{};
			Bitboard subset{}, index{};

			for (Square sq = a1; sq < NSQUARES; sq++) {
				subset = 0;
				do {
					index = subset;
					index = index * BISHOP_MAGICS[sq];
					index = index >> BISHOP_SHIFTS[sq];
					bishop_attack_table[sq][index] = generate_slow_bishop_attacks(sq, subset);
					subset = (subset - bishop_attack_masks[sq]) & bishop_attack_masks[sq];
				} while (subset);
			}
			return bishop_attack_table;
		}

		constexpr array<array<Bitboard, ROOK_TABLE_SIZE>, NSQUARES> rook_attack_table = generate_rook_attack_table();

		constexpr Bitboard get_rook_attacks(Square square, Bitboard occ) {
			usize index = ((occ & rook_attack_masks[square]) * ROOK_MAGICS[square]) >> ROOK_SHIFTS[square];
			return rook_attack_table[square][index];
		}

		constexpr array<array<Bitboard, BISHOP_TABLE_SIZE>, NSQUARES> bishop_attack_table = generate_bishop_attack_table();

		constexpr Bitboard get_bishop_attacks(Square square, Bitboard occ) {
			usize index = ((occ & bishop_attack_masks[square]) * BISHOP_MAGICS[square]) >> BISHOP_SHIFTS[square];
			return bishop_attack_table[square][index];
		}

	} // anon namespace

	template<PieceType piece_type, Color color = WHITE>
	constexpr Bitboard attacks(Square sq, Bitboard occupancy = 0) {
		if constexpr (piece_type == PAWN) {
			if constexpr (color == WHITE) return WHITE_PAWN_ATTACKS[sq];
			return BLACK_PAWN_ATTACKS[sq];
		}
		else if constexpr (piece_type == KNIGHT) return KNIGHT_ATTACKS[sq];
		else if constexpr (piece_type == BISHOP) return get_bishop_attacks(sq, occupancy);
		else if constexpr (piece_type == ROOK) return get_rook_attacks(sq, occupancy);
		else if constexpr (piece_type == QUEEN) return get_bishop_attacks(sq, occupancy) | get_rook_attacks(sq, occupancy);
		else if constexpr (piece_type == KING) return KING_ATTACKS[sq];
		return 0;
	}

	inline Bitboard attacks(PieceType piece_type, Square sq, Bitboard occupancy) {
		if (piece_type == PAWN) return 0;
		else if (piece_type == KNIGHT) return KNIGHT_ATTACKS[sq];
		else if (piece_type == BISHOP) return get_bishop_attacks(sq, occupancy);
		else if (piece_type == ROOK) return get_rook_attacks(sq, occupancy);
		else if (piece_type == QUEEN) return get_bishop_attacks(sq, occupancy) | get_rook_attacks(sq, occupancy);
		else if (piece_type == KING) return KING_ATTACKS[sq];
		return 0;
	}
} // table namespace