CC = clang
CFLAGS = -Wall -Wextra -g -Iheaders
SRCS = server.c client.c headers/socket/socket_utils.c
OBJS = $(SRCS:.c=.o)
BIN_DIR = bin
TARGETS = $(BIN_DIR)/server $(BIN_DIR)/client

.PHONY: all clean run debug build

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

all: $(TARGETS)

$(BIN_DIR)/server: server.o headers/socket/socket_utils.o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/client: client.o headers/socket/socket_utils.o | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

build: all

clean:
	rm -f $(OBJS) $(TARGETS)
	rm -rf $(BIN_DIR)

run: build
	./$(BIN_DIR)/server & ./$(BIN_DIR)/client

debug: build
	echo "Server and client built with debug symbols."

