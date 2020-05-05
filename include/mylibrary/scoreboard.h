//
// Created by lilyl on 5/4/2020.
//

#ifndef FINALPROJECT_SCOREBOARD_H
#define FINALPROJECT_SCOREBOARD_H
#include <sqlite_modern_cpp.h>

#include <string>
#include <vector>

namespace myapp {
    struct Player {
        Player(const std::string& name, size_t score) : name(name), score(score) {}
        std::string name;
        size_t score;
    };
    class ScoreBoard {
    public:
        // Creates a new leaderboard table if it doesn't already exist.
        explicit ScoreBoard(const std::string& db_path);

        // Adds a player to the leaderboard.
        void AddScoreToScoreBoard(const Player&);

        // Returns a list of the players with the highest scores, in decreasing order.
        // The size of the list should be no greater than `limit`.
        std::vector<Player> RetrieveHighScores(const size_t limit);

        // Returns a list of the players with the highest scores, in decreasing order,
        // that have the same `name` as the input player name.
        // The size of the list should be no greater than `limit`.
        std::vector<Player> RetrieveHighScores(const Player&, const size_t limit);

    private:
        sqlite::database db_;
    };

}

#endif //FINALPROJECT_SCOREBOARD_H
