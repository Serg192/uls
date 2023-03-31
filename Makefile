FLAGS = -std=c11 -Wall -Werror -Wpedantic -Wextra
NAME = uls

all: install

install:
	make -C ./libmx
	mkdir -p obj
	clang $(FLAGS) -c src/*.c -I libmx/inc 
	mv *.o obj/
	clang $(FLAGS) obj/*.o -L libmx -lmx  -o $(NAME)	

uninstall: clean
	make -C ./libmx uninstall
	rm -rf $(NAME)

reinstall: uninstall install

clean:
	rm -rf obj

