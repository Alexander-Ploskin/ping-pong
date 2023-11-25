all:
	rd /s /q bin
	if exist bin rd /s /q bin
	mkdir bin
	gcc -o bin/ping_pong src/ping_pong.c
