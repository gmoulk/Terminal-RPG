make compile:
	g++ -o Terminal-RPG main.cpp market.cpp living.cpp game.cpp square.cpp squads.cpp battle.cpp

make run:
	./Terminal-RPG

make mem_check:
	valgrind ./Terminal-RPG		
