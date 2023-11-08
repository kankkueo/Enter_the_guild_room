FLAGS = -lSDL2 -lSDL2_image

game: src/sdlexample.o src/renderer.o src/main.o
	g++ $(FLAGS) src/main.cpp src/sdlexample.o src/renderer.o -o game
src/main.o: src/main.cpp
	g++ -c src/main.cpp

sdlexample.o: src/sdlexample.cpp
	g++ -c src/sdlexample.cpp

renderer.o: src/renderer.cpp
	g++ -c src/renderer.cpp

clean:
	rm src/*.o

run: game
	./game
