FINAL_EXEC := game
CC := g++

# source file dir
SRC_DIR := ./src
# build dir
BUILD_DIR := ./build
# header file dir
INC_DIRS := include
INC_FLAGS := $(addprefix -I, $(INC_DIRS))
CPP_FLAGs := $(INC_FLAGS) -MMD -MP

# list of all source files
SRCS := $(shell find $(SRC_DIR) -name *.cpp)
# list of all source files, but in build dir
OBJS_TEMP := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS))
# list of all object files in build dir
OBJS := $(OBJS_TEMP:.cpp=.o )
# list of all dependencies
DEPS := $(OBJS:.o=.d)

$(BUILD_DIR)/$(FINAL_EXEC): $(OBJS)
	$(CC) $^ -o $@ -lSDL2main -lSDL2 -lSDL2_image

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(INC_FLAGS) -MMD -MP -c $^ -o $@ 

speak:
	echo $(CPP_FLAGS)

clean:
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/$(FINAL_EXEC)
	rm $(BUILD_DIR)/*.d