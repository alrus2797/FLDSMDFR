all :
	g++ -c -std=c++11 main.cpp
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -ltgui
	./sfml-app
