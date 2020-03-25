# Build-Depends: libsdl2-dev libsdl2-image-dev

OBJS = jt_game.o jt_helpers.o jt_menu.o jt_text.o main.o

DATE := $(shell date --rfc-3339=date)

CPPFLAGS += -DJT_COMPILE_DATE=\"$(DATE)\"
CFLAGS += -std=c99
CFLAGS += -O2
CFLAGS += -Wall
CPPFLAGS += $(shell pkg-config --cflags SDL2_image sdl2)
LDLIBS += $(shell pkg-config --libs SDL2_image sdl2)
LDLIBS += -lm

JoppyType: $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS)

.PHONY: clean

clean:
	-rm JoppyType
	-rm $(OBJS)
