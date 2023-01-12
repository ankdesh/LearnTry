
CXX=$(shell sst-config --CXX)
CXXFLAGS=$(shell sst-config --ELEMENT_CXXFLAGS)
LDFLAGS=$(shell sst-config --ELEMENT_LDFLAGS)

TARGET_LIB = libsimpleExternalElement.so
BUILD_DIR := ./build
SRC_DIRS := ./src 

.PHONY: all
all: $(BUILD_DIR)/$(TARGET_LIB) install

#SRCS =  $(shell echo src/*.cc)
SRCS := $(shell find $(SRC_DIRS) -name '*.cc')
#OBJS = $(SRCS:.cc=.o)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
HEADERS = $(shell echo include/*.h)

$(BUILD_DIR)/$(TARGET_LIB): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Build step for C++ source
$(BUILD_DIR)/%.cc.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#libsimpleExternalElement.so: src/simpleExternalElement.cc
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $<

install:
	sst-register simpleExternalElement simpleExternalElement_LIBDIR=$(CURDIR)
	sst-register SST_ELEMENT_SOURCE simpleExternalElement=$(CURDIR)
#	sst-register SST_ELEMENT_TESTS  simpleExternalElement=$(CURDIR)/../tests

clean:
	rm -f $(OBJS) libsimpleExternalElement.so
