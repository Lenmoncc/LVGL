# images
include $(PRJ_DIR)/EnvMonitor/generated/images/images.mk

# GUI Guider fonts
include $(PRJ_DIR)/EnvMonitor/generated/guider_fonts/guider_fonts.mk

# GUI Guider customer fonts
include $(PRJ_DIR)/EnvMonitor/generated/guider_customer_fonts/guider_customer_fonts.mk


GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/EnvMonitor/generated/*.c))

DEPPATH += --dep-path $(PRJ_DIR)/EnvMonitor/generated
VPATH += :$(PRJ_DIR)/EnvMonitor/generated

CFLAGS += "-I$(PRJ_DIR)/EnvMonitor/generated"