SHELL := /bin/bash
TOOLCHAIN := /home/portia_labiata/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin
CC := $(TOOLCHAIN)/arm-rockchip830-linux-uclibcgnueabihf-gcc
LD := $(TOOLCHAIN)/arm-rockchip830-linux-uclibcgnueabihf-gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -I/usr/include/opencv4 -std=c++2a
LDFLAGS := -lopencv_core -lopencv_videoio -lopencv_imgproc -lstdc++ -lz -lopencv_imgcodecs
LIB := /home/portia_labiata/luckfox-pico/sysdrv/source/buildroot/buildroot-2023.02.6/output/build/opencv3-3.4.19
LIBZ :=/home/portia_labiata/luckfox-pico/sysdrv/source/buildroot/buildroot-2023.02.6/output/build/libzlib-1.2.13

TARGET := titd
SRCS := main.cpp tit.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean flash

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) -L$(LIB)/buildroot-build/lib -L$(LIBZ) 

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(LIB)/include -c -o $@ $<

flash:
	adb push $(TARGET) /opt

clean:
	rm $(OBJS) $(TARGET)
