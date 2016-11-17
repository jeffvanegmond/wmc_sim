# wmc_sim
This repository contains a simulation for the World Magic Cup 2016. It simulates the flow of the tournament, based on the players Elo-ratings (http://mtgeloproject.net/).

# Building 
For those not familiar with how to build a CMake project, here's the short version on the command line. Start at the root of the project:
```
mkdir build && cd build
cmake ..
make all
```

# Running 
From the build directory, run: `./wmc_sim`

# Output 
The output is in CSV-format and gives a table of how often each team has reached a certain result.

# Assumptions 
I assumed that teams will show up with their strongest 3 players (based on Elo-rating) when possible. For the second part of each day, teams will show up with their second best formation. Since it is impossible to say beforehand in which position each player will sit, I randomize the seats of the players on each team each time the composition is changed.
