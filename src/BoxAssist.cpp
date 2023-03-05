//
// Created by antonina on 05.03.23.
//

#include "BoxAssist.h"

#include <stdexcept>
#include <string>

std::string BoxAssist::extensionName() {
    return "BoxAssist";
}

BoxAssist::BoxAssist() {

}

// Returns size of maximum sized subset
// if there is a subset of set[] with sun
// equal to given sum. It returns -1 if there
// is no subset with given sum.
std::vector<uint16_t> isSubsetSum(std::vector<uint16_t> set, int setLen, int n, int sum)
{
    // The value of subset[i][j] will be true if there
    // is a subset of set[0..j-1] with sum equal to i
    bool subset[sum + 1][n + 1];
    int count[sum + 1][n + 1];
    std::vector<uint16_t> val[sum + 1][n + 1]; // Тут докидываем еще один массив который будет содержать решение с контейенрами

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
            if (i >= set[j - 1])
            {
                subset[i][j] = subset[i][j] ||
                               subset[i - set[j - 1]][j - 1];

                if (subset[i][j])count[i][j] = std::max(count[i][j - 1],
                                      count[i - set[j - 1]][j - 1] + 1);


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
    std::vector<uint16_t> dest(source.size()/2);
    for (int i = 0; i < source.size()/2; ++i) {
        uint16_t hi = static_cast<u_char>(source[2 * i]);
        uint16_t lo = static_cast<u_char>(source[2 * i + 1]);
        dest.push_back((hi << 8) | lo);
    }
    std::vector<uint16_t> d(234);
    isSubsetSum(d, dest.size(), 20, dest.size() -1);
}