FLAGS = -lSDL2 -lSDL2_image

game: src/renderer.o src/input.o src/main.o src/game.o src/entity.o
	g++ src/renderer.o src/input.o src/main.cpp src/game.o src/entity.o -o game $(FLAGS)

main.o: src/main.cpp
	g++ -c src/main.cpp

renderer.o: src/renderer.cpp
	g++ -c src/renderer.cpp

input.o: src/input.cpp
	g++ -c src/input.cpp

game.o: src/game.cpp
	g++ -c src/game.cpp

entity.o: src/entity.cpp
	g++ -c src/entity.cpp

clean:
	rm src/*.o

run: game
	./game
