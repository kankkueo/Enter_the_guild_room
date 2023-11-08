FLAGS = -lSDL2 -lSDL2_image

game: src/renderer.o src/input.o src/main.o
	g++ $(FLAGS) src/renderer.o src/input.o src/main.cpp -o game

main.o: src/main.cpp
	g++ -c src/main.cpp

renderer.o: src/renderer.cpp
	g++ -c src/renderer.cpp

input.o: src/input.cpp
	g++ -c src/input.cpp

clean:
	rm src/*.o

run: game
	./game
