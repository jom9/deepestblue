cd backend

g++ -std=c++11 -o backend *.cpp ../logic/*.cpp
cp a.exe backend.php ../my-app/public

cd ..
cd engine

g++ -std=c++11 -o suggestion *.cpp ../logic/*.cpp ../backend/CreateGame.cpp
cp a.exe SuggestMove.php ../my-app/public
cd ..
