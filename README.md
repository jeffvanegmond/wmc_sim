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
I assumed that teams will show up with their strongest 3 players (based on Elo-rating) when possible. For the second part of each day, teams will show up with their second best formation. Since it is impossible to say beforehand in which position each player will sit, I randomize the seats of the players on each team each time the composition is changed. I also assumed the Elo-ratings of the players does not change during the tournament. This is a big assumption, since the Elo-project does not have a rating on some players yet; these ratings are almost sure to be incorrect.

# Notes
You can change `num_sims` in `wmc_sim.cpp` to do a different amount of simulations. I have not optimized my code and it is incredibly memory hungry. At `num_sims=100000` my 8GB machine runs out of physical memory. It took about 6 minutes to run a simulation with `num_sims=100000`. `num_sims=10000` was fine memory-wise.

# Results
There is a results folder in this repository, I have uploaded some sets of results. Each of these are independent sets, so in principle they can be combined. If someone happens to find an error that invalidates my results, I will empty the results folder and hopefully find some time to repopulate it.
