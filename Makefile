FLAGS = -lSDL2 -lSDL2_image

game: src/renderer.o src/main.o
	g++ $(FLAGS) src/main.cpp src/renderer.o -o game

main.o: src/main.cpp
	g++ -c src/main.cpp

renderer.o: src/renderer.cpp
	g++ -c src/renderer.cpp

clean:
	rm src/*.o

run: game
	./game
