CC = g++

CFLAGS = -g -Wall -Wextra -o3

obj_files = source/questions.o \
			source/referee.o \
			source/board.o \
			source/server.o

default: all

all: controller player

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
	
clean: clean_controller clean_player
	rm -f controller