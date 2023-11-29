FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

game: src/renderer.o src/input.o src/main.o src/game.o src/entity.o src/player.o src/monster.o src/room.o src/hud.o src/weapon.o
	g++ src/renderer.o src/input.o src/main.cpp src/game.o src/entity.o src/player.o src/monster.o src/room.o src/hud.o src/weapon.o -o game $(FLAGS)

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

player.o: src/player.cpp
	g++ -c src/player.cpp

monster.o: src/monster.cpp
	g++ -c src/monster.cpp

room.o: src/room.cpp
	g++ -c src/room.cpp

hud.o: src/hud.cpp
	g++ -c src/hud.cpp

weapon.o: src/weapon.cpp
	g++ -c src/weapon.cpp

clean:
	rm src/*.o

run: game
	./game
