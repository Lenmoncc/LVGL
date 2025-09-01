
GEN_CSRCS += $(notdir $(wildcard $(PRJ_DIR)/EnvMonitor/custom/*.c))

DEPPATH += --dep-path $(PRJ_DIR)/EnvMonitor/custom
VPATH += :$(PRJ_DIR)/EnvMonitor/custom

CFLAGS += "-I$(PRJ_DIR)/EnvMonitor/custom"
AFLAGS += "-I$(PRJ_DIR)/EnvMonitor/custom"
