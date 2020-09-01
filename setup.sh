cd backend

g++ -std=c++11 *.cpp ../logic/*.cpp

cd ..
cd engine

g++ -std=c++11 *.cpp ../logic/*.cpp ../backend/CreateGame.cpp
