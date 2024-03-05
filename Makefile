CC=gcc
install:
	@git clone https://github.com/raysan5/raylib.git 
	@cd ./raylib/src
	@make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED
	@sudo make install
	@cp ./raylib/src/libraylib.so.500 /usr/lib/libraylib.450

build:
	@ $(CC) -lraylib -o main main.c
