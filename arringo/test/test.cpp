#include "gtest/gtest.h"
#include <iostream>
#include "../src/LeagueSimulator.hpp"

TEST(LeagueTest, wrongDocumentTest) {
    std::vector<tournament::Team> teams;
    std::map<std::string, double> team_mean_map;
    tournament::LeagueSimulator league_simulator(teams, team_mean_map, "../wrong_dir");
    league_simulator.simulate_league();
    EXPECT_EQ(0, league_simulator.teams.size());
}

TEST(LeagueTest, correctDocumentTest) {
    std::vector<tournament::Team> teams;
    std::map<std::string, double> team_mean_map;
    tournament::LeagueSimulator league_simulator(teams, team_mean_map);
    league_simulator.simulate_league();
    EXPECT_EQ(20, league_simulator.teams.size());
}

TEST(LeagueTest, playedGameCount) {
    std::vector<tournament::Team> teams;
    std::map<std::string, double> team_mean_map;
    tournament::LeagueSimulator league_simulator(teams, team_mean_map);
    league_simulator.simulate_league();
    EXPECT_EQ(38, league_simulator.teams[0].games_drawn_count + league_simulator.teams[0].games_lost_count + league_simulator.teams[0].games_won_count);
}

TEST(LeagueTest, leagueLeaderCheck) {
    std::vector<tournament::Team> teams;
    std::map<std::string, double> team_mean_map;
    tournament::LeagueSimulator league_simulator(teams, team_mean_map);
    league_simulator.simulate_league();
    EXPECT_EQ(true, league_simulator.teams[0].points > league_simulator.teams[1].points);
}

TEST(LeagueTest, leagueWorstCheck) {
    std::vector<tournament::Team> teams;
    std::map<std::string, double> team_mean_map;
    tournament::LeagueSimulator league_simulator(teams, team_mean_map);
    league_simulator.simulate_league();
    auto worst = *std::min_element(league_simulator.teams.begin(),league_simulator.teams.end(), [](auto& a, auto& b) {return a.points < b.points;} );
    auto expilict_worst = league_simulator.teams[19];
    EXPECT_EQ(true, worst.team_name == expilict_worst.team_name);
}

