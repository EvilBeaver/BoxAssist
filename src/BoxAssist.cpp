//
// Created by antonina on 05.03.23.
//

#include "BoxAssist.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <numeric>

std::vector<uint16_t> isSubsetSum(std::vector<uint16_t> set, int n, int sum);
std::vector<uint16_t> readFromBytes(std::vector<char> source);
std::vector<char> writeToBytes(const std::vector<uint16_t> &calcResult);
std::string intTostring(const std::vector<uint16_t> &calcResult);

#define MATRIX(type, m, n) std::vector<std::vector<type>>(m, std::vector<type>(n))
#ifdef __linux__
#define MAX std::max
#else
#define MAX max
#endif

std::string BoxAssist::extensionName() {
    return "BoxAssist";
}

union binLayout {
    uint16_t intValue;
    char bytePart[2];
};

BoxAssist::BoxAssist() {

    AddMethod(L"Calculate", L"Вычислить", this, &BoxAssist::calculate);

    AddMethod(L"Test", L"Тест", this, &BoxAssist::test);

}

variant_t BoxAssist::calculate(const variant_t &input, const variant_t &sum) {

    if (std::holds_alternative<std::vector<char>>(input)
            && std::holds_alternative<int32_t>(sum)) {

        auto extractedData = readFromBytes(std::get<std::vector<char>>(input));
        auto sumAsInt = std::get<int32_t>(sum);

        auto calcResult = isSubsetSum(extractedData, extractedData.size(), sumAsInt);

        return intTostring(calcResult);

    } else {
        throw std::runtime_error(u8"Неподдерживаемые типы данных в параметрах");
    }

}

std::vector<char> writeToBytes(const std::vector<uint16_t> &calcResult) {
    std::vector<char> result;
    result.reserve(calcResult.size() * sizeof(uint16_t));

    for (unsigned short i : calcResult) {
        binLayout parts = {0};
        parts.intValue = i;

        result.push_back(parts.bytePart[0]);
        result.push_back(parts.bytePart[1]);
    }

    return result;
}

std::string intTostring(const std::vector<uint16_t> &calcResult) {
    std::stringstream ss;
    for(size_t i = 0; i < calcResult.size(); ++i)
    {
        if(i != 0)
            ss << ",";
        ss << calcResult[i];
    }
    std::string s = ss.str();

    return s;
}


variant_t BoxAssist::test(const variant_t &input) {
    auto read = readFromBytes(std::get<std::vector<char>>(input));
    return writeToBytes(read);
}

// Returns size of maximum sized subset
// if there is a subset of set[] with sun
// equal to given sum. It returns -1 if there
// is no subset with given sum.
std::vector<uint16_t> isSubsetSum(std::vector<uint16_t> set, int n, int sum)
{
    // The value of subset[i][j] will be true if there
    // is a subset of set[0..j-1] with sum equal to i

    auto subset = MATRIX(bool, sum + 1, n + 1);
    auto count = MATRIX(int, sum + 1, n + 1);
    auto val = MATRIX(std::vector<uint16_t>, sum + 1, n + 1);

    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
    {
        subset[0][i] = true;
        count[0][i] = 0;
        val[0][i] = {};
    }

    // If sum is not 0 and set is empty,
    // then answer is false
    for (int i = 1; i <= sum; i++)
    {
        subset[i][0] = false;
        count[i][0] = -1;
        val[i][0] = {};
    }

    // Fill the subset table in bottom up manner
    for (int i = 1; i <= sum; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            subset[i][j] = subset[i][j - 1];
            count[i][j] = count[i][j - 1];
            val[i][j] = val[i][j - 1];
            if (i >= set[j - 1])
            {
                subset[i][j] = subset[i][j] ||
                               subset[i - set[j - 1]][j - 1];

                if (subset[i][j]) {
                    count[i][j] = MAX(count[i][j - 1], count[i - set[j - 1]][j - 1] + 1);
                }


                if (count[i][j] > count[i][j-1]) {
                    val[i][j] = std::vector(val[i-set[j-1]][j-1]);
                    val[i][j].push_back(j-1);
                }
            }
        }
    }

    return val[sum][n];
}

std::vector<uint16_t> readFromBytes(std::vector<char> source) {
    std::vector<uint16_t> dest;
    dest.reserve(source.size() / sizeof(uint16_t));
    for (size_t i = 0; i < source.size() / sizeof(uint16_t); ++i) {
        auto hi = static_cast<u_char>(source[2 * i]);
        auto lo = static_cast<u_char>(source[2 * i + 1]);

        binLayout reader{};
        reader.bytePart[0] = hi;
        reader.bytePart[1] = lo;

        dest.push_back(reader.intValue);
    }

    return dest;
}