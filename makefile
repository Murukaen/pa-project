.PHONY: build clean exe test

test_file="test_o"

build: bitmap/bitmap.o state/state.o move/move.o cur_state/cur_state.o update_state/update_state.o state_generator/state_generator.o xboard_com/xboard_com.o command/command.o main/engine.o 
	gcc -g -Wall bitmap/bitmap.o state/state.o move/move.o cur_state/cur_state.o update_state/update_state.o state_generator/state_generator.o xboard_com/xboard_com.o command/command.o main/engine.o -o engine

test: xboard_com/xboard_com.o command/command.o main/engine.o 
	gcc -g -Wall xboard_com/xboard_com.o command/command.o main/engine.o -o engine
	
bitmap/bitmap.o: bitmap/bitmap.c
	gcc -c -Wall bitmap/bitmap.c -o bitmap/bitmap.o
	
state/state.o : state/state.c
	gcc -c -Wall state/state.c -o state/state.o

cur_state/cur_state.o: cur_state/cur_state.c
	gcc -c -Wall cur_state/cur_state.c -o cur_state/cur_state.o
	
update_state/update_state.o: update_state/update_state.c
	gcc -c -Wall update_state/update_state.c -o update_state/update_state.o

move/move.o: move/move.c
	gcc -c -Wall move/move.c -o move/move.o

state_generator/state_generator.o: state_generator/state_generator.c
	gcc -c -Wall state_generator/state_generator.c -o state_generator/state_generator.o
	
xboard_com/xboard_com.o: xboard_com/xboard_com.c
	gcc -c -Wall xboard_com/xboard_com.c -o xboard_com/xboard_com.o
	
command/command.o: command/command.c
	gcc -c -Wall command/command.c -o command/command.o
	
main/engine.o: main/engine.c
	gcc -c -Wall main/engine.c -o main/engine.o
	
clean:
	rm -f bitmap/bitmap.o state/state.o move/move.o cur_state/cur_state.o update_state/update_state.o state_generator/state_generator.o xboard_com/xboard_com.o command/command.o main/engine.o
	
