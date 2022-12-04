# League Simulator

> **Version:** 0.1.0 **Date:** 12.04.2022 **Author:** Olcay Davut Cabbas
>
> **Email:** [olcay.d.cabbas@gmail.com]

### Requirements
A compiler supporting the C++17 features.

## Features

- Football tournament simulation based on data extracted from the English Premiere League season
  2018/2019 (Ref.: MeanGoalPerGame.csv)

- Simulate a complete football tournament and compute the resulting table containing the below data
  for each team:
  + Total points
  + Total games won
  + Total games drawn
  + Total games lost
  + Total goals scored
  + Total goals conceded

## Cmake/Build

 * mkdir build
 * cd build
 * cmake ..
 * make

### Basic Usage
###### Client side
```
under arringo folder
run executable -> cd build/src && ./tournament_simulation_run
after run the executable, check the csv result under /arringo/src folder
run test -> cd build/test && ./league_test
```