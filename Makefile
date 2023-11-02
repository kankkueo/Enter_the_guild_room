FLAGS = -lSDL2 -lSDL2_image

game: src/sdlexample.o
	g++ $(FLAGS) src/sdlexample.o -o game

sdlexample.o: src/sdlexample.cpp
	g++ -c src/sdlexample.cpp

clean:
	rm src/*.o
