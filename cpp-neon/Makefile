CXX = clang++
CXXFLAGS = -Wall
BINDIR = ./bin
OBJDIR = ./obj
SRCDIR = ./src
ASMDIR = ./asm
INCLUDEDIR=./include
TESTDIR=./test
LDFLAGS=
INCLIDES= -I$(INCLUDEDIR)

# DEBUGマクロで最適化・デバッグ情報の有無を切り替える
DEBUG    ?= no
ifeq ($(DEBUG), yes)
        CXXFLAGS   += -O0 -g
        CONFIG   := debug
else
        CXXFLAGS   += -O3
        CONFIG   := release
endif

TARGET=$(BINDIR)/$(CONFIG)/measure
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(addprefix $(OBJDIR)/$(CONFIG)/,$(notdir $(SRCS:.cpp=.o)))
ASMS := $(addprefix $(ASMDIR)/$(CONFIG)/,$(notdir $(SRCS:.cpp=.s)))
DEPS := $(OBJS:.o=.d)

#$(warning SRCS = $(SRCS))
#$(warning OBJS = $(OBJS))
#$(warning ASMS = $(ASMS))

.PHONY: all clean rebuild
all: $(TARGET) asm test

# ヘッダ依存関係のインクルード
-include $(DEPS)

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)/$(CONFIG)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


$(OBJDIR)/$(CONFIG)/%.o : $(SRCDIR)/%.cpp 
	mkdir -p $(OBJDIR)/$(CONFIG)
	$(CXX) -c $(CXXFLAGS) $(INCLIDES) -o $@ $<

asm: $(ASMS)

$(ASMDIR)/$(CONFIG)/%.s : $(SRCDIR)/%.cpp
	mkdir -p $(ASMDIR)/$(CONFIG)
	$(CXX) -S $(CXXFLAGS) $(INCLIDES) -o $@ $<

test: $(TARGET)
	$(TARGET) 1024
	$(TARGET) 2048
	$(TARGET) 4096
	$(TARGET) 
clean:
	rm -r $(BUILDDIR) $(BINDIR) $(ASMDIR)

rebuild:
	make clean && make