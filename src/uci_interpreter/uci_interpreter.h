//
// Created by Archishmaan Peyyety on 1/9/23.
//
#pragma once
#include "engine.h"
#include "move_search/search.h"
#include "parse_uci_move.h"
#include "time_manager.h"
#include "helpers.h"
#include "sstream"

using namespace std;

struct ReadUCIParameters {
	bool debug_info = true;
};

void initialize_uci(Position& p) {
	initialize_engine();
	Position::set(INITIAL_BOARD_FEN, p);
}

void uci_position(Position& board, const string& input_line) {
	if (input_line.substr(0, 17) == "position startpos") {
		std::string uci_moves;
		if (input_line.size() > 17) uci_moves = input_line.substr(24, input_line.size() - 24);
		Position::set(INITIAL_BOARD_FEN, board);
		uci_update_position_from_moves(board,  uci_moves);
	} else {
		int fen_start = input_line.find("position fen ") + 13;
		int fen_end = input_line.find(" moves");
		int moves_start = fen_end + 6;
		int fen_size = fen_end - fen_start;
		const string& fen = input_line.substr(fen_start, fen_size);
		std::string moves;
		if (fen_end != std::string::npos) {
			moves = input_line.substr(moves_start + 1, input_line.size() - moves_start);
		}

		Position::set(fen, board);
		uci_update_position_from_moves(board, moves);
	}
}

int parse_move_time(const Color side_to_play, const string& move_time_s) {
	std::vector<string> tokens = split(move_time_s, " ");
	// Possible inputs to parse
	// input --> go movetime xxx
	// input --> go xtime ### xinc ### ytime ### yinc ###
	// input --> go xtime ### ytime ###
	if (tokens[1] == "movetime") {
		return stoi(tokens[2]) * 0.95;
	}
	int wtime = 0, winc = 0, btime = 0, binc = 0;
	for (int i = 1; i < tokens.size(); i += 2) {
		string token = tokens[i];
		int value = 0;
		if (tokens.size() > i + 1) value = stoi(tokens[i + 1]);

		if (token == "wtime") wtime = value;
		else if (token == "winc") winc = value;
		else if (token == "btime") btime = value;
		else if (token == "binc") binc = value;
	}
	if (side_to_play == WHITE) {
		return time_for_move(wtime, winc);
	}
	return time_for_move(btime, binc);
}

void uci_go(Position& board, const string& input_line, ReadUCIParameters& uci_parameters) {
	auto t_start = std::chrono::high_resolution_clock::now();

	BestMoveSearchResults results;
	int move_time = parse_move_time(board.turn(), input_line);
	const BestMoveSearchParameters params = BestMoveSearchParameters {
		.depth = MAX_DEPTH,
		.time_limit = move_time,
		.debug_info = uci_parameters.debug_info
	};
	results = best_move(board, params);
	std::cout << "bestmove " << results.best_move << std::endl;
}

void read_uci() {
	Position board;
	ReadUCIParameters parameters = {};
	initialize_uci(board);

	string input_line;

	cout.setf(ios::unitbuf);

	while (std::getline(cin, input_line)) {
		if (input_line == "uci") {
			std::cout << "id name Midnight V3.0" << std::endl;
			std::cout << "id author Archishmaan Peyyety" << std::endl;
			std::cout << "uciok" << std::endl;
		} else if (input_line == "quit") {
			std::cout << "Bye Bye" << std::endl;
			break;
		} else if (input_line == "isready") {
			std::cout << "readyok" << std::endl;
		} else if (input_line == "ucinewgame") {}
		if (input_line.substr(0, 8) == "position") {
			uci_position(board, input_line);
		} else if (input_line == "stop") {
		} else if (input_line == "debug on") {
			parameters.debug_info = true;
		} else if (input_line == "debug off") {
			parameters.debug_info = false;
		} else if (input_line.substr(0, 2 ) == "go") {
			uci_go(board, input_line, parameters);
		}
	}
}