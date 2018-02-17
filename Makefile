CXX = g++
CXXFLAGS = -Wall
TARGET = out/main.exe

all: release

release: $(TARGET)

debug: CXXFLAGS += -g
debug: $(TARGET)

$(TARGET): obj/main.o
	$(CXX) $< -o $@

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f obj/*.o out/*.exe
