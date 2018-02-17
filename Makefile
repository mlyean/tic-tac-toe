CXX = g++
CXXFLAGS = -Wall
TARGET = build/debug/main.exe

all: release

release: $(TARGET)

debug: CXXFLAGS += -g
debug: $(TARGET)

$(TARGET): build/debug/obj/main.o
	$(CXX) $< -o $@

build/debug/obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f build/debug/obj/*.o build/debug/*.exe build/release/obj/*.o build/release/*.exe
