CC := g++-14

CCFLAGS := -Wall -Wextra -Wpedantic -std=c++20 -I./inc -I/opt/homebrew/include -g2 
CLFLAGS := -lm

INC_PATH := ./inc
SRC_PATH := ./src
OBJ_PATH := ./out

SRCS := $(wildcard $(SRC_PATH)/*.cxx)
OBJS := $(subst $(SRC_PATH),$(OBJ_PATH),$(SRCS:.cxx=.o))

app : $(OBJS) 
	$(CC) -o $@ $^ $(CLFLAGS)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cxx $(INC_PATH)/*.hpp
	mkdir -p ./out
	$(CC) -o $@ -c $< $(CCFLAGS)

.PHONY : clean

clean :
	rm -rf $(OBJ_PATH)
	rm -f app
	rmdir out
