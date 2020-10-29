cd game_cache

g++ -std=c++11 -o backend *.cpp ../logic/*.cpp
cd ..
cd engine

g++ -std=c++11 -o suggestion *.cpp ../logic/*.cpp ../game_cache/CreateGame.cpp
cd ..
