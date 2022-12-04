#include "LeagueSimulator.hpp"

using namespace std;

int main() {
    vector<vector<string>> content;

    std::vector<tournament::Team> teams;
    std::map<std::string, double> team_mean_map;
    tournament::LeagueSimulator league_simulator(teams, team_mean_map);
    league_simulator.simulate_league();
    league_simulator.drop_league_results();
    return EXIT_SUCCESS;
}
