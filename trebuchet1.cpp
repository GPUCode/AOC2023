#include <cstdio>
#include "input.h"

constexpr char haystack[] = "123456789";

constexpr auto answer = [] {
    size_t start_pos = 0;
    size_t end_pos = -1;

    const auto find_next = [&] {
        start_pos = end_pos + 1;
        end_pos = puzzle_input.find('\n', start_pos);
        return end_pos != puzzle_input.npos;
    };

    const auto to_digit = [](char c) -> size_t {
        return c - '0';
    };

    size_t result = 0;
    while (find_next()) {
        const size_t size = end_pos - start_pos;
        const auto line = puzzle_input.substr(start_pos, size);
        const size_t first = line.find_first_of(haystack);
        const size_t last = [&] {
            const size_t pos = line.find_last_of(haystack);
            return pos == line.npos ? first : pos;
        }();
        const size_t num = to_digit(line[first]) * 10 + to_digit(line[last]);
        result += num;
    }

    return result;
}();

int main() {
    printf("%lld\n", answer);
    return 0;
}