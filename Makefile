CXX = g++
CXXFLAGS = -Wall
_OBJS = main.o board.o game.o move.o player.o player_human.o
OBJS = $(patsubst %.o,build/debug/obj/%.o,$(_OBJS))
TARGET = build/debug/main.exe

all: release

release: $(TARGET)

debug: CXXFLAGS += -g
debug: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

build/debug/obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f build/debug/obj/*.o build/debug/*.exe build/release/obj/*.o build/release/*.exe
