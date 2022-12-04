#ifndef LeagueSimulator_HPP
#define LeagueSimulator_HPP

#include <string>
#include <iostream>
#include "Team.hpp"

namespace tournament{
class LeagueSimulator {
private:
    std::map<std::string, double>& team_mean_map;
    std::map<std::string, double> read_csv(const std::string& fname)
    {
        std::vector<std::string> row;
        std::string line, word;
        std::fstream file(fname, std::ios::in);
        if (file.is_open())
        {
            getline(file, line); //first line is uncessary
            while (getline(file, line))
            {
                row.clear();

                std::stringstream str(line);

                while (getline(str, word, ','))
                    row.push_back(word);
                
                try {
                    team_mean_map[row[0]] = std::stod(row[1]);
                } catch(...) {
                    std::cout << "unhandled csv" << std::endl;
                }
                
            }
        }
        else
            std::cout << "Could not open the file\n";


        return team_mean_map;
    }    
public:
    LeagueSimulator(
        std::vector<tournament::Team>& in_teams, std::map<std::string, double>& in_team_mean_map, const std::string& file_name = "../../src/MeanGoalPerGame.csv")
    : team_mean_map(in_team_mean_map)
    , teams(in_teams) {
        team_mean_map = read_csv(file_name);

        for(const auto& team : team_mean_map)
            teams.emplace_back(tournament::Team(team.first));
    }

    std::map<uint32_t, double> GetGoalDistribution(const double meanGoalPerMatch)
    {
        constexpr auto lbdFactorial{[](const uint32_t factorial)
                                    {
                                        auto result{1u};
                                        for (uint32_t idx = 1u; idx <= factorial; ++idx)
                                        {
                                            result *= idx;
                                        }
                                        return result;
                                    }};

        constexpr auto maxGoals{5u};

        auto prevProbability{0.0};
        std::map<uint32_t, double> goalDist;
        for (uint32_t i = 0u; i < maxGoals; ++i)
        {
            const auto probPoisson{(std::pow(meanGoalPerMatch, i) * std::exp(-1 * meanGoalPerMatch)) / lbdFactorial(i)};

            goalDist.emplace(std::make_pair(i, (probPoisson + prevProbability)));
            prevProbability += probPoisson;
        }

        goalDist.emplace(std::make_pair(maxGoals, 1.0));

        return goalDist;
    }

    int get_goal_count(const std::map<uint32_t, double>& goal_distribution) {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dist(0.0, 1.0);
        double random_number = dist(gen);

        for(const auto & item : goal_distribution ) {
            if(random_number < item.second)
                return item.first;
        }

        return 5;
    }

    void simulate_league() {
        std::for_each(teams.begin(), teams.end(),
            [this](auto &team_a) {
                for(auto& team_b : this->teams) { 
                    if(team_a.team_name == team_b.team_name) {
                        continue;
                    }
                    auto goal_distribution_a =  GetGoalDistribution(team_mean_map[team_a.team_name]);
                    auto goal_number_a = get_goal_count(goal_distribution_a);
                    
                    auto goal_distribution_b =  GetGoalDistribution(team_mean_map[team_b.team_name]);
                    auto goal_number_b = get_goal_count(goal_distribution_a);

                    team_a.total_goals_scored += goal_number_a;
                    team_b.total_goals_scored += goal_number_b;

                    team_a.total_goals_conceded += goal_number_b;
                    team_b.total_goals_conceded += goal_number_a;

                    if (goal_number_a > goal_number_b) {                    
                        team_a.games_won_count += 1;
                        team_b.games_lost_count += 1;                    
                    } else if (goal_number_a < goal_number_b) {
                        team_b.games_won_count += 1;
                        team_a.games_lost_count += 1;                      
                    } else {
                        team_a.games_drawn_count += 1;
                        team_b.games_drawn_count += 1;
                    }
                }        
        });

        for(auto& team : teams) {
            team.calculate_points();  
        }

        std::sort(teams.begin(), teams.end(),
        [](auto& team_a, auto& team_b) { return (team_a.points > team_b.points); } );
    }

    void drop_league_results() {
        std::fstream fout; 
        fout.open("../../src/LeagueReport.csv", std::ios::out | std::ios::app);
            // Insert the data to file
        fout << "TeamName" << " "
                << "Points" << " "
                << "GamesWonCount" << " "
                << "GamesDrawnCount" << " "
                << "GamesLostCount" << " "
                << "TotalGoalsScored" << " "
                << "TotalGoalsConceded"
                << "\n";

        for(auto& team : teams) {
            fout << team << "\n";  
        }        
    }
    std::vector<tournament::Team>& teams;
};
}
#endif
