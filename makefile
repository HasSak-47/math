SRC_DIR := src
OBJ_DIR := .cache
OUT := mathlib_test
SRCS := $(shell find src -name *.cpp)
INCLUDES := $(shell find include -name *.hpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CXX := g++
CXXFLAGS := -g -Iinclude -export-dynamic

build: $(OBJS) $(INCLUDES)
	g++ $(CXXFLAGS) -o $(OUT) $(OBJS) $(LDFLAGS)

run : build
	@./$(OUT)

test : build
	./$(OUT) test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	rm $(OBJS)

.PHONY: all clean inst source
