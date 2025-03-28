CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wfloat-equal -Isrc `pkg-config --cflags gtk+-3.0`
CFLAGS += -Wno-typedef-redefinition
LDFLAGS = `pkg-config --libs gtk+-3.0` -framework ApplicationServices

TARGET = hot-bookmarks.out
SRCDIR = src

# находит все существующие файлы, подходящие под шаблон
SRCS = $(wildcard $(SRCDIR)/*.c)
# замена расширения .c на .o
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

# линковка объектных файлов
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

# rule pattern. Если файл .o не найден, то он будет собран из .c
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
