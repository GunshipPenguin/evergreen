CC=$(HOME)/cross/bin/i686-elf-gcc

CFLAGS=-ffreestanding -nostdlib -std=gnu99 -Wall -Wextra -I kernel/src/include

OBJ_DIR=obj
BIN_DIR=bin

BIN_NAME=evergreen

ARCH=x86

ARCH_OBJ_FILES=$(addsuffix .o, $(basename $(wildcard kernel/arch/$(ARCH)/*.[S,c])))
OBJ_FILES=$(addsuffix .o, \
$(basename $(wildcard kernel/src/*.c)) \
$(basename $(wildcard kernel/src/libk/*.c)))

.PHONY: all clean output_dirs

all: output_dirs $(BIN_NAME)

evergreen: $(ARCH_OBJ_FILES) $(OBJ_FILES)
				@echo $(ARCH_OBJ_FILES)
				@echo $(OBJ_FILES)
				$(CC) $(CFLAGS) -T kernel/arch/$(ARCH)/link.ld -o $(BIN_DIR)/$@ $(wildcard $(OBJ_DIR)/*.o)
				grub-file --is-x86-multiboot $(BIN_DIR)/$(BIN_NAME)

%.o: %.c
				$(CC) $(CFLAGS) -o $(OBJ_DIR)/$(notdir $@) -c $<

%.o: %.S
				$(CC) -o $(OBJ_DIR)/$(notdir $@) -c $<

output_dirs:
				mkdir -p $(OBJ_DIR)
				mkdir -p $(BIN_DIR)

clean:
				rm -f $(BIN_NAME)
				rm -rf $(OBJ_DIR)
				rm -rf $(BIN_DIR)
