#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <map>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace tournament {
struct Team {
    std::string team_name;
    int points {0};
    int games_won_count{0};
    int games_drawn_count{0};
    int games_lost_count{0};
    int total_goals_scored{0};
    int total_goals_conceded{0};

    Team(const std::string& name)
    : team_name(name) {}

    int calculate_points() {
        points =  3*games_won_count + games_drawn_count;
        return points;
    }

   friend std::ostream& operator<<(std::ostream& stream, const Team& team) {
      
        stream << team.team_name << ' ' << team.points << ' ' << team.games_won_count << ' '<< 
        team.games_drawn_count << ' '<< team.games_lost_count << ' '<< team.total_goals_scored << ' ' << team.total_goals_conceded;
        return stream;
    }
};
}
#endif //TEAM_HPP