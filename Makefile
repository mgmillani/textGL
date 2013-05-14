CC = gcc
CFLAGS = -Wall -Wextra -I$(INC)
SRC = src
OBJ = obj
BIN = bin
INC = include
LIB = -lGL -lSDLmain -lSDL -lSDL_image
OBJECTS = $(OBJ)/surfaceOperations.o $(OBJ)/textDrawer.o $(OBJ)/textLoader.o $(OBJ)/textOrganizer.o $(OBJ)/file.o
NAME = libtextGL

all: $(OBJ) $(BIN) release

release: CFLAGS += -s -O3
release: text

debug: CFLAGS += -g
debug: text

$(OBJ):
	mkdir $(OBJ)
$(BIN):
	mkdir $(BIN)

text: $(OBJECTS)
	ar r $(BIN)/$(NAME).a $(OBJECTS)
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f obj/*.o
	rm -f bin/$(NAME).a
