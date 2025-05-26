BUILD_DIR=build
include $(N64_INST)/include/n64.mk

src = main.c

all: gldemo.z64

$(BUILD_DIR)/gldemo.elf: $(src:%.c=$(BUILD_DIR)/%.o)

gldemo.z64: N64_ROM_TITLE="GL Demo"

clean:
	rm -rf $(BUILD_DIR) filesystem/ gldemo.z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
