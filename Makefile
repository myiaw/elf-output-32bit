all: build

build:
	gcc -m32 main.c -o elf_changer -Wall -Wextra -Wpedantic -Werror
	gcc -m32 hello.c -o hello.o -c -Wall -Wextra -Wpedantic -Werror

runh: build
	./elf_changer -h hello.o

runl: build
	./elf_changer -l hello.o

clean:
	rm -f elf_changer hello.o