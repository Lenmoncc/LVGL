#
# Makefile
#

PRJ_DIR := $(CURDIR)

CC              = arm-linux-gnueabihf-gcc
CXX             = arm-linux-gnueabihf-g++
LVGL_DIR_NAME   ?= lvgl
LVGL_DIR        ?= .
#LVGL_DIR        ?= /home/test/linux/tools/lv_port_linux-9.2.2/lvgl
#LVGL_DIR        ?= /home/test/linux/tools/lvgl-9.3.0

WARNINGS        :=  -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith \
                   -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits \
                   -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security \
                   -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body \
                   -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -std=gnu99
CFLAGS          ?= -O3 -g0 -I$(LVGL_DIR) -I./MusicPlayer/generated $(WARNINGS) 
LDFLAGS         ?= -lm -lpthread -ldl

BIN             = main
BUILD_DIR       = ./build
BUILD_OBJ_DIR   = $(BUILD_DIR)/obj
BUILD_BIN_DIR   = $(BUILD_DIR)/bin

prefix          ?= /home/test/linux/lvgl
bindir          ?= $(prefix)/bin

# Collect source files recursively
CSRCS           := $(shell find src -type f -name '*.c') \
				   $(shell find MusicPlayer/generated -type f -name '*.c') \
				   $(shell find MusicPlayer/custom -type f -name '*.c')
CXXSRCS         := $(shell find src -type f -name '*.cpp')


GENERATED_BASE := $(PRJ_DIR)/MusicPlayer/generated

include $(GENERATED_BASE)/images/images.mk
include $(GENERATED_BASE)/guider_fonts/guider_fonts.mk
include $(GENERATED_BASE)/guider_customer_fonts/guider_customer_fonts.mk
include $(GENERATED_BASE)/generated.mk
include $(GENERATED_BASE)/custom/custom.mk

# Include LVGL sources
include $(LVGL_DIR)/lvgl/lvgl.mk

OBJEXT          ?= .o

COBJS           = $(CSRCS:.c=$(OBJEXT))
CXXOBJS         = $(CXXSRCS:.cpp=$(OBJEXT))
AOBJS           = $(ASRCS:.S=$(OBJEXT))

SRCS            = $(ASRCS) $(CSRCS) $(CXXSRCS)
OBJS            = $(AOBJS) $(COBJS) $(CXXOBJS)
TARGET          = $(addprefix $(BUILD_OBJ_DIR)/, $(patsubst ./%, %, $(OBJS)))

all: default

$(BUILD_OBJ_DIR)/%.o: %.c lv_conf.h
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "CC  $<"

$(BUILD_OBJ_DIR)/%.o: %.cpp lv_conf.h
	@mkdir -p $(dir $@)
	@$(CXX)  $(CFLAGS) -c $< -o $@
	@echo "CXX $<"

$(BUILD_OBJ_DIR)/%.o: %.S lv_conf.h
	@mkdir -p $(dir $@)
	@$(CC)  $(CFLAGS) -c $< -o $@
	@echo "AS  $<"

default: $(TARGET)
	@mkdir -p $(dir $(BUILD_BIN_DIR)/)
	$(CXX) -o $(BUILD_BIN_DIR)/$(BIN) $(TARGET) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)

install:
	install -d $(DESTDIR)$(bindir)
	install $(BUILD_BIN_DIR)/$(BIN) $(DESTDIR)$(bindir)

uninstall:
	$(RM) -r $(addprefix $(DESTDIR)$(bindir)/,$(BIN))
