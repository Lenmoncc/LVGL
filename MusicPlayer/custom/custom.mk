
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/MusicPlayer/custom/*.c))

DEPPATH += --dep-path $(PRJ_DIR)/MusicPlayer/custom
VPATH += :$(PRJ_DIR)/MusicPlayer/custom

CFLAGS += "-I$(PRJ_DIR)/MusicPlayer/custom"
AFLAGS += "-I$(PRJ_DIR)/MusicPlayer/custom"
