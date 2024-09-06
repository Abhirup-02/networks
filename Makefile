all: src/parity-bit/client.cpp
	@g++ -Iinclude -o client $?