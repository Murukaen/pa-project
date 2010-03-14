.PHONY: build clean exe test

test_file="test_o"

build: bitmap/bitmap.o state/state.o move/move.o cur_state/cur_state.o update_state/update_state.o state_generator/state_generator.o
	

bitmap/bitmap.o: bitmap/bitmap.c
	gcc -c bitmap/bitmap.c -o bitmap/bitmap.o
	
state/state.o : state/state.c
	gcc -c state/state.c -o state/state.o

cur_state/cur_state.o: cur_state/cur_state.c
	gcc -c cur_state/cur_state.c -o cur_state/cur_state.o
	
update_state/update_state.o: update_state/update_state.c
	gcc -c update_state/update_state.c -o update_state/update_state.o

move/move.o: move/move.c
	gcc -c move/move.c -o move/move.o

state_generator/state_generator.o: state_generator/state_generator.c
	gcc -c state_generator/state_generator.c -o state_generator/state_generator.o
	
clean:
	rm -Rf -v *.o
	
