CC = clang
CFLAGS = -std=c99 -Wall -Isrc -Wextra -Werror -Wpedantic -Wfloat-equal 
FRAMEWORKS = -framework ApplicationServices
TARGET = hot-bookmarks.out
SRCS = src/main.c src/keyboard.c src/logger.c src/active_app.c

all: $(TARGET)

$(TARGET): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(FRAMEWORKS) -o $(TARGET)

clean:
	rm -f $(TARGET)
