#include "breakthrough.hpp"

namespace reasoner {
    int game_state::get_current_player(void) const {
        return current_player;
    }

    int game_state::get_player_score(int player_id) const {
        return variables[player_id-1];
    }

    void game_state::apply_move(const move& mv) {
        auto curr_id = current_player - 1;
        auto opp_id = current_player & 1;
        pieces[curr_id] ^= mv.mr;
        pieces[opp_id] &= ~mv.mr;
        if (pieces[curr_id] & last_row[curr_id]) {
            variables[curr_id] = 100;
            current_player = 0;
        }
        else {
            current_player ^= 0b11;
        }
        empty = ~(pieces[0] | pieces[1]);
    }

    void game_state::get_all_moves(resettable_bitarray_stack&, std::vector<move>& moves) {
        moves.clear();
        if (current_player == 1) {
            uint64_t not_white = ~pieces[0];
            uint64_t movers = pieces[0] & (empty >> 8);
            while (movers) {
                auto piece = msb(movers);
                moves.push_back(piece | piece << 8);
                movers ^= piece;
            }
            movers = pieces[0] & maskLD & (not_white >> 7);
            while (movers) {
                auto piece = msb(movers);
                moves.push_back(piece | piece << 7);
                movers ^= piece;
            }
            movers = pieces[0] & maskRD & (not_white >> 9);
            while (movers) {
                auto piece = msb(movers);
                moves.push_back(piece | piece << 9);
                movers ^= piece;
            }
        }
        else {
            uint64_t not_black = ~pieces[1];
            uint64_t movers = pieces[1] & (empty << 8);
            while (movers) {
                auto piece = msb(movers);
                moves.push_back(piece | piece >> 8);
                movers ^= piece;
            }
            movers = pieces[1] & maskLD & (not_black << 9);
            while (movers) {
                auto piece = msb(movers);
                moves.push_back(piece | piece >> 9);
                movers ^= piece;
            }
            movers = pieces[1] & maskRD & (not_black << 7);
            while (movers) {
                auto piece = msb(movers);
                moves.push_back(piece | piece >> 7);
                movers ^= piece;
            }
        }
        if (moves.empty()) {
            variables[current_player - 1] = 100;
        }
    }

    bool game_state::apply_any_move(resettable_bitarray_stack&) {
        return false;
    }

    int game_state::get_monotonicity_class(void) {
        return -1;
    }

    bool game_state::is_legal([[maybe_unused]] const move& m) const {
        return false;
    }

    inline uint64_t game_state::msb(const uint64_t& pieces) const {
        auto k = 63 - __builtin_clzll(pieces);
        return 1ull << k;
    }
}
