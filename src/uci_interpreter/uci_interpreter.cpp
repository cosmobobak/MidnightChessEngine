//
// Created by Archishmaan Peyyety on 6/21/23.
//
#include "uci_interpreter.h"

void initialize_uci(Position& p) {
	initialize_engine();
	p.set_fen(INITIAL_BOARD_FEN);
}

void uci_position(Position& board, const string& input_line) {
	if (input_line.substr(0, 17) == "position startpos") {
		string uci_moves;
		if (input_line.size() > 17) uci_moves = input_line.substr(24, input_line.size() - 24);
		board.set_fen(INITIAL_BOARD_FEN);
		uci_update_position_from_moves(board,  uci_moves);
	} else {
		auto fen_start = static_cast<i32>(input_line.find("position fen ")) + 13;
		auto fen_end = static_cast<i32>(input_line.find(" moves"));
		auto moves_start = fen_end + 6;
		auto fen_size = fen_end - fen_start;
		const string& fen = input_line.substr(fen_start, fen_size);
		string moves;
		if (input_line.find(" moves") != string::npos) {
			moves = input_line.substr(moves_start + 1, input_line.size() - moves_start);
		}

		board.set_fen(fen);
		uci_update_position_from_moves(board, moves);
	}
}

void parse_move_time(Color side_to_play, const string& move_time_s, BestMoveSearchParameters& params) {
	std::vector<string> tokens = split(move_time_s);
	// Possible inputs to parse
	// input --> go movetime xxx
	// input --> go xtime ### xinc ### ytime ### yinc ###
	// input --> go xtime ### ytime ###
	if (tokens[1] == "movetime") {
		params.hard_time_limit = stoi(tokens[2]) * 0.95;
		params.soft_time_limit = stoi(tokens[2]) * 0.95;
		return;
	}
	i32 wtime = 0, winc = 0, btime = 0, binc = 0, moves_to_go = -1;
	for (usize i = 1; i < tokens.size(); i += 2) {
		string token = tokens[i];
		auto value = 0;
		if (tokens.size() > i + 1) value = stoi(tokens[i + 1]);

		if (token == "wtime") wtime = value;
		else if (token == "winc") winc = value;
		else if (token == "btime") btime = value;
		else if (token == "binc") binc = value;
		else if (token == "movestogo") moves_to_go = value;
	}
	if (side_to_play == WHITE) {
		std::tie(params.soft_time_limit, params.hard_time_limit) = allocate_time(wtime, winc, moves_to_go);
	} else {
		std::tie(params.soft_time_limit, params.hard_time_limit) = allocate_time(btime, binc, moves_to_go);
	}
}

void uci_go(Position& board, const string& input_line, ReadUCIParameters& uci_parameters) {
	BestMoveSearchParameters params = {
			.depth = MAX_DEPTH,
			.debug_info = uci_parameters.debug_info
	};
	parse_move_time(board.turn(), input_line, params);
	search(board, params);
	std::cout << "bestmove " << data.final_best_move << std::endl;
}

void bench() {
	u64 total_nodes = 0;
	auto start = std::chrono::steady_clock::now();
	for (auto idx = 0; idx < BENCH_SIZE; idx++) {
		Position p;
		initialize_uci(p);
		p.set_fen(BENCH_FENS[idx]);

		std::cout << "\nPosition: " << idx + 1 << " " << BENCH_FENS[idx] << std::endl;

		BestMoveSearchParameters parameters = {
				.depth = 14,
				.hard_time_limit = 86'400'000, // 1 Day
				.soft_time_limit = 86'400'000,
				.debug_info = true,
		};
		search(p, parameters);
		std::cout << "bestmove " << data.final_best_move << std::endl;
		total_nodes += data.nodes_searched;
	}
	auto end = std::chrono::steady_clock::now();
	auto total_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	auto total_time = static_cast<double>(total_time_ms) / 1000.0;
	std::cout << "Total Time: " << total_time << std::endl;
	std::cout << "\n";
	std::cout << total_nodes << " nodes " << signed(total_nodes / (total_time + 1)) << " nps" << std::endl;
}

void read_uci() {
	Position board;
	ReadUCIParameters parameters = {};
	initialize_uci(board);

	string input_line;

	std::cout.setf(std::ios::unitbuf);

	while (std::getline(std::cin, input_line)) {
		if (input_line == "uci") {
			std::cout << "id name Midnight 6.0" << std::endl;
			std::cout << "id author Archishmaan Peyyety" << std::endl;
			std::cout << "option name Hash type spin default 64 min 1 max 1024" << std::endl;
			std::cout << "option name Threads type spin default 1 min 1 max 1" << std::endl;
			std::cout << "uciok" << std::endl;
		} else if (input_line == "quit") {
			std::cout << "Bye Bye" << std::endl;
			break;
		} else if (input_line == "isready") {
			std::cout << "readyok" << std::endl;
		} else if (input_line == "ucinewgame") {
			initialize_uci(board);
		}
		if (input_line.substr(0, 8) == "position") {
			uci_position(board, input_line);
		} else if (input_line == "stop") {
		} else if (input_line == "debug on") {
			parameters.debug_info = true;
		} else if (input_line == "debug off") {
			parameters.debug_info = false;
		} else if (input_line.substr(0, 2 ) == "go") {
			uci_go(board, input_line, parameters);
		} else if (input_line == "bench") {
			bench();
		} else if (input_line.substr(0, 14) == "setoption name") {
			std::vector<string> parsed_options = split(input_line);
			std::transform(parsed_options[2].begin(), parsed_options[2].end(), parsed_options[2].begin(),
						   [](unsigned char c){ return std::tolower(c); });
			if (parsed_options[2] == "hash") {
				auto mb = std::stoi(parsed_options[4]);
				t_table.resize(mb);
			}
		} else if (input_line == "hash size") {
			std::cout << t_table.entry_count() << " entries" << std::endl;
		}
	}
}
