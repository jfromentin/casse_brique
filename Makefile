EXE 	= bin/brik
LIBS	= -lSDL2
CPP 	= g++
CFLAGS	= -O3

ALL	= $(EXE)

obj/%.o: src/%.cpp src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(EXE): obj/window.o src/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)
