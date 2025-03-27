CFLAGS = -Wall
FRAMEWORKS = -framework ApplicationServices
TARGET = hot-bookmarks.out

all: $(TARGET)

$(TARGET): main.c keyboard.c logger.c active_app.c
	@clang $(CFLAGS) main.c keyboard.c logger.c active_app.c $(FRAMEWORKS) -o $(TARGET)

clean:
	rm -f $(TARGET)
