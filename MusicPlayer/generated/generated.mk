# images
include $(PRJ_DIR)/MusicPlayer/generated/images/images.mk

# GUI Guider fonts
include $(PRJ_DIR)/MusicPlayer/generated/guider_fonts/guider_fonts.mk

# GUI Guider customer fonts
include $(PRJ_DIR)/MusicPlayer/generated/guider_customer_fonts/guider_customer_fonts.mk


GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/MusicPlayer/generated/*.c))

DEPPATH += --dep-path $(PRJ_DIR)/MusicPlayer/generated
VPATH += :$(PRJ_DIR)/MusicPlayer/generated

CFLAGS += "-I$(PRJ_DIR)/MusicPlayer/generated"