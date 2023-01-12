
CXX=$(shell sst-config --CXX)
CXXFLAGS=$(shell sst-config --ELEMENT_CXXFLAGS)
LDFLAGS=$(shell sst-config --ELEMENT_LDFLAGS)

TARGET_LIB = libNeuralProcessor.so
BUILD_DIR := ./build
SRC_DIRS := ./src 

.PHONY: all
all: $(BUILD_DIR)/$(TARGET_LIB) install

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/$(TARGET_LIB): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I./include -c $< -o $@

install:
	sst-register NeuralProcessor NeuralProcessor_LIBDIR=$(CURDIR)/build
	sst-register SST_ELEMENT_SOURCE NeuralProcessor=$(CURDIR)/src
	sst-register SST_ELEMENT_TESTS  NeuralProcessor=$(CURDIR)/../tests

clean:
	rm -r $(BUILD_DIR)
