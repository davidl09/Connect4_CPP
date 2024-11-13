// benchmark.cpp
#include "bitboard.hpp"
#include "minimaxbit.hpp"
#include <chrono>
#include <iomanip>
#include <functional>
#include <random>
#include <format>

class Benchmark {
private:
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::microseconds;

    template<typename F>
    Duration measure_execution(F&& func) {
        auto start = Clock::now();
        func();
        auto end = Clock::now();
        return std::chrono::duration_cast<Duration>(end - start);
    }

    void print_result(const std::string& test_name, Duration duration,
                     const std::string& additional_info = "") {
        std::cout << std::format("{:<40} {:>10} μs", test_name, duration.count());
        if (!additional_info.empty()) {
            std::cout << "    " << additional_info;
        }
        std::cout << "\n";
    }

    BitBoard create_random_board(int num_moves) {
        BitBoard board;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 6);

        for (int i = 0; i < num_moves; i++) {
            int col;
            do {
                col = dis(gen);
            } while (!board.is_legal_move(col));

            board.place_token(col, static_cast<colour>(i % 2));
        }
        return board;
    }

    std::vector<BitBoard> create_test_positions(int num_positions, int moves_per_position) {
        std::vector<BitBoard> positions;
        positions.reserve(num_positions);
        for (int i = 0; i < num_positions; i++) {
            positions.push_back(create_random_board(moves_per_position));
        }
        return positions;
    }

public:
    void run_all_benchmarks() {
        std::cout << "Running Connect 4 Performance Benchmarks\n";
        std::cout << std::string(50, '=') << "\n\n";

        benchmark_board_operations();
        benchmark_minimax_search();
        benchmark_evaluation_function();
        benchmark_move_generation();
        benchmark_win_detection();
    }

private:
    void benchmark_board_operations() {
        std::cout << "Board Operations Benchmarks:\n";
        std::cout << std::string(30, '-') << "\n";

        // Test place_token operation
        {
            BitBoard board;
            auto duration = measure_execution([&]() {
                for (int i = 0; i < 1000; i++) {
                    board = BitBoard();  // Reset board
                    for (int col = 0; col < 7; col++) {
                        board.place_token(col, yellow);
                    }
                }
            });
            print_result("Place Token (7000 operations)", duration);
        }

        // Test move validation
        {
            BitBoard board;
            auto duration = measure_execution([&]() {
                for (int i = 0; i < 10000; i++) {
                    for (int col = 0; col < 7; col++) {
                        board.is_legal_move(col);
                    }
                }
            });
            print_result("Move Validation (70000 checks)", duration);
        }

        // Test board copying
        {
            std::vector<BitBoard> boards(1000);
            auto duration = measure_execution([&]() {
                for (int i = 0; i < 1000; i++) {
                    BitBoard new_board = boards[i];
                }
            });
            print_result("Board Copying (1000 copies)", duration);
        }

        std::cout << "\n";
    }

    void benchmark_minimax_search() {
        std::cout << "Minimax Search Benchmarks:\n";
        std::cout << std::string(30, '-') << "\n";

        // Test different search depths
        for (int depth : {4, 6, 8, 10}) {
            MiniMaxBit algo(depth);
            auto positions = create_test_positions(5, 10);  // 5 positions, 10 moves each

            auto duration = measure_execution([&]() {
                for (auto& pos : positions) {
                    algo.best_move(pos);
                }
            });

            auto avg_duration = Duration(duration.count() / positions.size());
            print_result(
                std::format("Minimax Search (depth {})", depth),
                avg_duration,
                std::format("avg per position")
            );
        }

        std::cout << "\n";
    }

    void benchmark_evaluation_function() {
        std::cout << "Evaluation Function Benchmarks:\n";
        std::cout << std::string(30, '-') << "\n";

        // Test evaluation at different game stages
        for (int moves : {10, 20, 30}) {
            auto positions = create_test_positions(100, moves);

            auto duration = measure_execution([&]() {
                for (auto& pos : positions) {
                    pos.score(yellow);
                }
            });

            auto avg_duration = Duration(duration.count() / positions.size());
            print_result(
                std::format("Evaluation ({} moves)", moves),
                avg_duration,
                std::format("avg per position")
            );
        }

        std::cout << "\n";
    }

    void benchmark_move_generation() {
        std::cout << "Move Generation Benchmarks:\n";
        std::cout << std::string(30, '-') << "\n";

        // Test move generation at different game stages
        for (int moves : {0, 10, 20, 30}) {
            auto positions = create_test_positions(100, moves);
            int total_moves = 0;

            auto duration = measure_execution([&]() {
                for (auto& pos : positions) {
                    for (int col = 0; col < 7; col++) {
                        if (pos.is_legal_move(col)) {
                            total_moves++;
                        }
                    }
                }
            });

            auto avg_duration = Duration(duration.count() / positions.size());
            print_result(
                std::format("Move Generation ({} moves)", moves),
                avg_duration,
                std::format("avg {} legal moves", total_moves / positions.size())
            );
        }

        std::cout << "\n";
    }

    void benchmark_win_detection() {
        std::cout << "Win Detection Benchmarks:\n";
        std::cout << std::string(30, '-') << "\n";

        // Test win detection at different game stages
        for (int moves : {10, 20, 30}) {
            auto positions = create_test_positions(100, moves);

            auto duration = measure_execution([&]() {
                for (auto& pos : positions) {
                    pos.iswin(yellow);
                    pos.iswin(red);
                }
            });

            auto avg_duration = Duration(duration.count() / positions.size());
            print_result(
                std::format("Win Detection ({} moves)", moves),
                avg_duration,
                std::format("avg per position")
            );
        }

        // Test win detection with known patterns
        BitBoard pattern_board;
        for (int i = 0; i < 4; i++) {
            pattern_board.place_token(3, yellow);  // Vertical win
        }

        auto duration = measure_execution([&]() {
            for (int i = 0; i < 10000; i++) {
                pattern_board.iswin(yellow);
            }
        });
        print_result("Win Detection (Known Pattern)", duration, "10000 checks");

        std::cout << "\n";
    }
};

int main() {
    Benchmark bench;
    bench.run_all_benchmarks();
    return 0;
}