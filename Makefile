# Compiler parameters
CXX = g++
CXXFLAGS = -Iinclude -IC:/msys64/mingw64/include/ncurses -Wall

# Object files
_OBJS = main.o board.o client.o game.o move.o player.o player_human.o player_random.o

# Executable name
EXEC = main.exe

# Debug parameters
DEBTARDIR = build/debug
DEBOBJDIR = build/debug/obj
DEBOBJS = $(patsubst %.o,$(DEBOBJDIR)/%.o,$(_OBJS))
DEBEXEC = $(DEBTARDIR)/$(EXEC)

# Release parameters
RELTARDIR = build/release
RELOBJDIR = build/release/obj
RELOBJS = $(patsubst %.o,$(RELOBJDIR)/%.o,$(_OBJS))
RELEXEC = $(RELTARDIR)/$(EXEC)

OBJDIR = build/debug/obj
TARGETDIR = build/debug

all: release

# Debug target
debug: CXXFLAGS += -g
debug: $(DEBEXEC)

$(DEBEXEC): $(DEBOBJS)
	$(CXX) $(DEBOBJS) -o $@ -lncurses

$(DEBOBJDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Release target
release: $(RELEXEC)

$(RELEXEC): $(RELOBJS)
	$(CXX) $(RELOBJS) -o $@ -lncurses

$(RELOBJDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(DEBOBJDIR)/*.o $(DEBTARDIR)/*.exe $(RELOBJDIR)/*.o $(RELTARDIR)/*.exe
