#include <unordered_map>
#include "move_generation/types.h"

enum TranspositionTableEntryNodeType {
	EXACT,
	UPPER_NODE,
	LOWER_NODE
};

enum TranspositionTableEntrySearchType {
	Q_SEARCH,
	FULL_SEARCH
};

struct TranspositionTableEntry {
	uint64_t zobrist_hash;
	int depth;
	int value;
	TranspositionTableEntryNodeType node_type;
	// Used ?
	Move best_move;
};

struct TranspositionTableSearchResults {
	TranspositionTableEntry entry;
	bool entry_found;
};

// More to learn from here: https://github.com/kobolabs/stockfish/blob/master/tt.cpp
class TranspositionTable {
public:
	TranspositionTableEntryNodeType get_node_type(const int &alpha_initial, const int &beta, const int &value);
	void put(zobrist_hash hash, int depth, int score, TranspositionTableEntryNodeType node_type);
	TranspositionTableSearchResults probe(zobrist_hash hash, int depth);
	explicit TranspositionTable(uint64_t size = 64000);
	~TranspositionTable();

private:
	uint64_t get_index(uint64_t zobrist_hash);
	TranspositionTableEntry *transposition_table;
	uint64_t table_size;
};
