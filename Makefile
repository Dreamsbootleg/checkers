CC = g++

CFLAGS = -g -Wall -Wextra -O3

obj_files = source/game_logic.o	\
			source/message.o 	\
			source/server.o 	\
			source/board.o 		\
			source/display.o 	\
			source/conio.o 		\
			source/logger.o 	\
			source/questions.o

default: all

all: controller player test

controller: $(obj_files)
	@echo "\tbuilding $@"
	@$(CC) $(CFLAGS) -o $@ controller.cpp $(obj_files)

clean_controller:
	@cd source; make clean; cd ..;

$(obj_files):
	@echo "\n### Source ###\n"
	@cd source; make all; cd ..;

player:
	@echo "\n### Players ###\n"
	@cd AI_Files; make all; cd ..;

clean_player:
	@cd AI_Files; make clean; cd ..;

test: $(obj_files)
	@echo "\n### Tests ###\n"
	@cd tests; make all; cd ..;

clean_test:
	@cd tests; make clean; cd ..;

clean: clean_controller clean_player clean_test
	rm -f controller