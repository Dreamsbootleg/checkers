CC = g++

CFLAGS = -g -Wall -Wextra -03

cpp_files = questions.cpp \
			referee.cpp
header_files = $(patsubst %.cpp, %.h, $(cpp_files))
obj_files = $(patsubst %.cpp, %.o, $(cpp_files))

all: $(header_files) $(cpp_files) $(obj_files)

%.o: %.cpp %.h
	@echo "\tbuilding $@"
	@$(CC) -o $@ -c $<

clean:
	rm -f $(obj_files)