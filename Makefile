CC = g++
CFLAGS = -g -std=c++17 -m64 -Iinclude -Wall # -Werror
# LFLAGS = 

BINDIR = .
SRCDIR = .
INCDIR = include
LIBDIR = lib

WORKDIR	= $(pwd)

# Locate files
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRC))


TARGET = $(BINDIR)/app

all: $(TARGET)

# Build Rules
$(TARGET) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBDIR) -l:pdcurses.a

$(BINDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	rm $(BINDIR)/*.o -rf

run: $(BINDIR)/app.exe
	./app.exe

