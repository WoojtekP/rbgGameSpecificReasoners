#include <cstdlib>
#include <cstdint>
#include <string>
#include <vector>

namespace reasoner {
    constexpr int NUMBER_OF_PLAYERS = 3;
    constexpr int MONOTONIC_CLASSES = 0;

    class resettable_bitarray_stack {};

    typedef uint64_t move_representation;
    struct move {
        move_representation mr;
        move(const move_representation& mv) : mr(mv) {};
        move(void) = default;
        bool operator==(const move& rhs) const {
            return mr == rhs.mr;
        }
    };
    enum player {
        WHITE = 1,
        BLACK = 2
    };
    class game_state {
        public:
            int get_current_player(void) const;
            int get_player_score(int player_id) const;
            void apply_move(const move& m);
            std::vector<move> get_all_moves(resettable_bitarray_stack& cache);
            void get_all_moves(resettable_bitarray_stack&, std::vector<move>& moves);
            bool apply_any_move(resettable_bitarray_stack&);
            int get_monotonicity_class(void);
            bool is_legal(const move& m) const;
        private:
            inline uint64_t msb(const uint64_t&) const;
            uint64_t empty = 0xFFFFFFFF0000;
            uint64_t white = 0xFFFF;
            uint64_t black = 0xFFFF000000000000;
            const uint64_t maskLD = 0xFEFEFEFEFEFEFEFE;
            const uint64_t maskRD = 0x7F7F7F7F7F7F7F7F;
            int winner = 0;
            int current_cell = 1;
            int current_player = WHITE;
            int current_state = 0;
            int variables[2] = {0, 0};
    };
}