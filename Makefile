CC := g++
TARGET_EXEC := game.exe

BUILD_DIR := ./build
SRC_DIR := ./src
INC_DIR := include
INC_FLAGS := $(addprefix -I, $(INC_DIR))

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS_TEMP := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS))
OBJS := $(OBJS_TEMP:.cpp=.o)
DEPS := $(OBJS:.o=.d)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $^ -o $@ -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -I./$(INC_DIR)/mingw_dev_lib/include/SDL2 -L./$(INC_DIR)/mingw_dev_lib/lib

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(INC_FLAGS) -MMD -MP -c $^ -o $@ -I./$(INC_DIR)/mingw_dev_lib/include/SDL2 -L./$(INC_DIR)/mingw_dev_lib/lib

speak:
	echo $(SRCS)
	echo $(OBJS)

clean:
	rm $(BUILD_DIR)/*.o
	rm $(BUILD_DIR)/*.d
	rm $(BUILD_DIR)/*.exe
