#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class Position {
public:
    explicit Position(int i, int j) : x(i), y(j) {}
    int x;
    int y;

    bool operator==(const Position& rhs) const {
        return x == rhs.x &&
               y == rhs.y;
    }

    bool operator!=(const Position& rhs) const {
        return !(*this == rhs); // reuse ==
    }

    bool operator<(const Position& rhs) const {
        if (x < rhs.x) return true;
        if (rhs.x < x) return false;
        return y < rhs.y;
    }

    bool operator>(const Position& rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Position& rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Position& rhs) const {
        return !(*this < rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const Position& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

class Knight {
    std::map<Position, std::vector<Position>> grid;
    std::vector<Position> steps;
    const int max_height, max_width;
    Position start;
    bool found;

    void printSteps () const {
        if (!found) {
            std::cout << "There is no Hamilton Cycle in Grid " << max_width << " by " << max_height << "!" << std::endl;
        } else {
            std::cout << "Hamilton Cycle in Grid " << max_width << " by " << max_height << " Starts from " << start << ":" << std::endl;
            for (int i = 0; i <= max_width * max_height; i++){
                std::cout << steps.at(i) << std::endl;
            }

        }
        std::cout << std::endl << std::endl;
    }

    [[nodiscard]] std::vector<Position> getPossibleMoveList(Position pos) const {
        std::vector<Position> moves;
        int x = pos.x;
        int y = pos.y;
        if (int nx = x - 2, ny = y - 1; nx >= 1 && ny >= 1)
            moves.emplace_back(nx, ny);
        if (int nx = x - 2, ny = y + 1; nx >= 1 && ny <= max_height)
            moves.emplace_back(nx, ny);
        if (int nx = x - 1, ny = y - 2; nx >= 1 && ny >= 1)
            moves.emplace_back(nx, ny);
        if (int nx = x - 1, ny = y + 2; nx >= 1 && ny <= max_height)
            moves.emplace_back(nx, ny);
        if (int nx = x + 1, ny = y - 2; nx <= max_width && ny >= 1)
            moves.emplace_back(nx, ny);
        if (int nx = x + 1, ny = y + 2; nx <= max_width && ny <= max_height)
            moves.emplace_back(nx, ny);
        if (int nx = x + 2, ny = y - 1; nx <= max_width && ny >= 1)
            moves.emplace_back(nx, ny);
        if (int nx = x + 2, ny = y + 1; nx <= max_width && ny <= max_height)
            moves.emplace_back(nx, ny);
        return moves;
    }

    bool run(Position pos, int step = 1) { // NOLINT(*-no-recursion)
        steps.push_back(pos);
        if (auto forwardList = grid[pos]; !forwardList.empty()) {
            if (step == max_height * max_width) {
                if (std::find(forwardList.begin(), forwardList.end(), start) != forwardList.end()) {
                    steps.push_back(start);
                    return true;
                }
            }
            else {
                for (auto move: forwardList) {
                    if (std::find(steps.begin(), steps.end(), move) == steps.end()) {
                        if(run(move, step + 1)) {
                            return true;
                        }
                    }
                }
            }
        }
        steps.pop_back();
        return false;
    }

public:
    explicit Knight(const int x = 6,const int y = 6, int start_x = 1, int start_y = 1) : max_height(y), max_width(x), start(start_x, start_y) {
        for (int i = 1; i <= x; i++)
            for (int j = 1; j <= y; j++)
                grid.insert(std::make_pair(Position(i, j), getPossibleMoveList(Position(i, j))));


        if ((max_width * max_width) % 2 == 1 || !run(start))
            found = false;
        else
            found = true;
        printSteps();
    }
};

int main() {
    Knight knight(6 , 6);
    Knight knight1(6, 6, 5, 3);
    Knight knight2(6, 7, 4, 7);
    Knight knight3(7,7);
    Knight knight4(6, 5);
    return 0;
}