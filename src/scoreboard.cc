//
// Created by lilyl on 5/4/2020.
//

#include "mylibrary/scoreboard.h"
#include <sqlite_modern_cpp.h>
#include <string>

using std::string;
using std::vector;

namespace myapp {
    ScoreBoard::ScoreBoard(const string& db_path) : db_{db_path} {
        db_ << "CREATE TABLE if not exists scoreboard (\n"
               "  username  TEXT NOT NULL,\n"
               "  time INTEGER NOT NULL\n"
               ");";
    }

    void ScoreBoard::AddScoreToScoreBoard(const Player& player) {
        try {
            db_ << "insert into scoreboard (username, time) values (?, ?)"
                << player.name
                << player.score;
        } catch (std::exception &e) {
            std::cout << e.what();
        }


    }

    vector<Player> GetPlayers(sqlite::database_binder* rows) {
        vector<Player> players;

        for (auto&& row : *rows) {
            string name;
            size_t score;
            row >> name >> score;
            Player player = {name, score};
            players.push_back(player);
        }

        return players;
    }

    vector<Player> ScoreBoard::RetrieveHighScores(const size_t limit) {
        auto rows = db_ << "select username, time from scoreboard order by time ASC limit ?"
                        << limit;
        return GetPlayers(&rows);
    }

    vector<Player> ScoreBoard::RetrieveHighScores(const Player& player,
                                                   const size_t limit) {
        auto rows = db_ << "select username, time from scoreboard where username = ? order by time ASC limit ?"
                        << player.name
                        << limit;
        return GetPlayers(&rows);
    }

}
