all:
	rm -rf bin || true
	mkdir bin
	gcc -o bin/ping_pong.exe src/ping_pong.c
	bin/ping_pong.exe
