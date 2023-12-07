#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct hand_t {
    enum { HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND,
        FULL_HOUSE, FOUR_OF_A_KIND, FIVE_OF_A_KIND };
    enum { T = 10, J = 1, Q = 12, K = 13, A = 14 };
    std::vector<int> cards;
    int bid, score;

    void calc_score() {
        std::map<int, int> card2freq;
        for (const auto& card : cards) card2freq[card]++;
        int jokers = card2freq[J];
        card2freq[J] = 0;

        std::vector<int> freqs;
        for (const auto& [k, v] : card2freq) freqs.push_back(v);
        std::sort(freqs.begin(), freqs.end(), std::greater<int>());

        freqs.at(0) += jokers;

        if (freqs.at(0) == 5) score = FIVE_OF_A_KIND;
        else if (freqs.at(0) == 4) score = FOUR_OF_A_KIND;
        else if (freqs.at(0) == 3 && freqs.at(1) == 2) score = FULL_HOUSE;
        else if (freqs.at(0) == 3) score = THREE_OF_A_KIND;
        else if (freqs.at(0) == 2 && freqs.at(1) == 2) score = TWO_PAIR;
        else if (freqs.at(0) == 2) score = ONE_PAIR;
        else score = HIGH_CARD;
    }

    friend std::istream& operator>>(std::istream& in, hand_t& hand) {
        hand.cards.clear();
        for (int i{0}; i < 5; i++) {
            char c; if (!(in >> c)) return in;
            int val;
            if (std::isdigit(c)) val = c - '0';
            else if (c == 'T') val = T;
            else if (c == 'J') val = J;
            else if (c == 'Q') val = Q;
            else if (c == 'K') val = K;
            else if (c == 'A') val = A;
            hand.cards.push_back(val);
        }
        hand.calc_score();

        in >> hand.bid;

        return in;
    }

    bool operator<(const hand_t& rhs) const {
        if (score != rhs.score)
            return score < rhs.score;
        else
            return cards < rhs.cards;
    }
};

int main (int argc, char *argv[]) {
    std::string line;
    std::vector<hand_t> hands;

    hand_t hand;
    while (std::cin >> hand) hands.push_back(hand);
    std::sort(hands.begin(), hands.end());

    long sum{0};
    for (int i{0}; i < hands.size(); i++)
        sum += hands[i].bid * (i + 1);

    std::cout << sum << std::endl;

    return 0;
}
