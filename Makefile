# project name ######################################################################################
NAME ::= tulib

# command line args #################################################################################
ARGS ::=

# source file containing the 'main' function (directory need not be included) #######################
MAIN ::= src/main.c

# compilers and linker ##############################################################################
cc = gcc 

CC_DEBUG_FLAGS ::= -std=c2x -c -g -fPIC -O2 -Wall -Wextra -Wpedantic -Wno-unused-parameter
CC_RELEASE_FLAGS ::= -std=c2x -c -s -fPIC -O3

CC_FLAGS ::= $(CC_DEBUG_FLAGS)
#CC_FLAGS ::= $(CC_RELEASE_FLAGS)

CC ::= $(cc) $(CC_FLAGS)

ld ::= $(cc)
LD_FLAGS ::=
LD ::= $(ld) $(LD_FLAGS)

# external libs #####################################################################################
LIBS ::=

# autodetect object files ###########################################################################
extract_obj_name = $(patsubst %.c, build/obj/%.o, $(notdir $(1)))

SRC ::= $(wildcard src/*.c src/*/*.c)
OBJ ::= $(foreach f, $(SRC), $(call extract_obj_name, $(f)))

# make entry point ##################################################################################
EXEC ::= build/bin/$(NAME)

.PHONY: all

all: $(EXEC)

# generate dirs #####################################################################################
BUILD_DIRS ::= build/bin build/lib build/obj build/asm

$(BUILD_DIRS):
	mkdir -p $(BUILD_DIRS)

$(OBJ): | $(BUILD_DIRS)

# executable ########################################################################################
$(EXEC): $(OBJ)
	$(LD) $(OBJ) $(LIBS) -o $(EXEC)

# compile object files ##############################################################################
define make_obj =
$(subst \,, $(shell gcc -MT $(1) -MM $(2)))
	$(CC) $(2) -o $(1)
endef

$(foreach f, $(SRC), $(eval $(call make_obj, $(call extract_obj_name, $(f)), $(f))))

# auxiliary targets #################################################################################
.PHONY: clean run libs asm

clean:
	rm -f -r build/*/*

run: $(EXEC)
	./$(EXEC) $(ARGS)

# create static and dynamic libraties ###############################################################
STATIC_LIB ::= build/lib/lib$(NAME).a
DYNAMIC_LIB ::= build/lib/lib$(NAME).so

LIB_OBJ ::= $(filter-out $(call extract_obj_name, $(MAIN)), $(OBJ))

libs: $(LIB_OBJ)
	ar rcs $(STATIC_LIB) $(LIB_OBJ)
	$(LD) --shared $(LIB_OBJ) -o $(DYNAMIC_LIB)

# generate assembly for all .c files ################################################################
extract_asm_name = $(patsubst %.c, build/asm/%.s, $(notdir $(1)))

ASM ::= $(foreach f, $(SRC), $(call extract_asm_name, $(f)))

define make_asm =
$(subst \,, $(shell gcc -MT $(1) -MM $(2)))
	$(cc) -std=c2x -O3 -S -masm=intel $(2) -o $(1)
endef

$(foreach f, $(SRC), $(eval $(call make_asm, $(call extract_asm_name, $(f)), $(f))))

asm: $(ASM)
