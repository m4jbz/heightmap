SRC = src
OBJ = build
BIN = bin

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

CFLAGS = -Wall -Wextra -g
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CC = gcc

TARGET = $(BIN)/heightmap

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

.PHONY: all clean
