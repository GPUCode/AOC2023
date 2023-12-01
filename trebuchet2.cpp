#include <cstdio>
#include <array>
#include "input.h"

constexpr std::array<std::string_view, 9> numbers = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};

struct FindResult {
    size_t pos;
    size_t digit;
    size_t size;

    size_t End() const noexcept {
        return pos + size;
    }
};

template <bool reverse>
FindResult FindInRange(std::string_view line, size_t start, size_t stop) {
    constexpr size_t addend = reverse ? -1 : 1;
    for (size_t i = start; reverse ? i >= stop : i < stop; i += addend) {
        // Is number
        const char c = line[i];
        if (c >= '1' && c <= '9') {
            return {i, static_cast<size_t>(c - '0'), 1};
        }

        // Is number word
        const auto num = line.substr(i);
        for (size_t j = 0; j < numbers.size(); j++) {
            const auto str = numbers[j];
            if (i + str.size() <= line.size() && num.starts_with(str)) {
                return {i, j + 1, str.size()};
            }
        }
    }
    return {line.npos, 0, 0};
}

constexpr auto compute() {
    size_t start_pos = 0;
    size_t end_pos = -1;

    const auto find_next = [&] {
        start_pos = end_pos + 1;
        end_pos = puzzle_input.find('\n', start_pos);
        return end_pos != puzzle_input.npos;
    };

    size_t result = 0;
    while (find_next()) {
        const size_t size = end_pos - start_pos;
        const auto line = puzzle_input.substr(start_pos, size);
        const auto first = FindInRange<false>(line, 0, line.size());
        const auto last = [&] {
            const auto last = FindInRange<true>(line, line.size() - 1, first.End());
            return last.pos == line.npos ? first : last;
        }();
        const size_t num = first.digit * 10 + last.digit;
        result += num;
    }

    return result;
}

int main() {
    printf("%lld\n", compute());
    return 0;
}
