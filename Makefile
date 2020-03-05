# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 22:06:19 by marvin            #+#    #+#              #
#    Updated: 2020/03/04 14:56:04 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
###############                  VARIABLES                       ###############
################################################################################

NM :=    ft_nm
OTOOL := ft_otool
NAME := $(NM) $(OTOOL)


CFLAGS ?= -g3 -Wall -Wextra #-Werror -fno-builtin

SRC_NAME_COMMON = utils.c
SRC_NAME_NM = $(shell cd src/nm && find . -type f)
SRC_NAME_OTOOL = $(shell cd src/otool && find . -type f)


NM_FD =    nm/
OTOOL_FD = otool/

NM_SRC_SUBFOLDERS =
OTOOL_SRC_SUBFOLDERS =

BUILD_FOLDER =	build

################################################################################
###############                  CONSTANTS                       ###############
################################################################################
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	NUMPROC := $(shell grep -c ^processor /proc/cpuinfo)
	EXEC_RPATH := \$$ORIGIN
else ifeq ($(UNAME_S),Darwin)
	NUMPROC := $(shell sysctl hw.ncpu | awk '{print $$2}')
	EXEC_RPATH := @loader_path #https://blogs.oracle.com/dipol/dynamic-libraries,-rpath,-and-mac-os
endif

CC = gcc
LDLIBS = -lft
LDFLAGS = -L./libft
CFLAGS += -MMD -I./src -I./libft

SRC_FOLDERS =	$(addprefix $(NM_FD), $(NM_SRC_SUBFOLDERS))			\
				$(addprefix $(OTOOL_FD), $(OTOOL_SRC_SUBFOLDERS))	\
				$(NM_FD) $(OTOOL_FD)

REPO_PATH = $(patsubst %/,%,$(dir $(realpath $(firstword $(MAKEFILE_LIST)))))
BUILD_PATH = $(REPO_PATH)/$(BUILD_FOLDER)
SRC_PATH =	src
OBJ_FOLDER = $(BUILD_FOLDER)/obj
LFT = libft/libft.a

OBJ_COMMON = utils.c
OBJ_NM    = $(addprefix $(OBJ_FOLDER)/$(NM_FD), $(SRC_NAME_NM:.c=.c.o)) $(addprefix $(OBJ_FOLDER)/, $(SRC_NAME_COMMON:.c=.c.o))
OBJ_OTOOL = $(addprefix $(OBJ_FOLDER)/$(OTOOL_FD), $(SRC_NAME_OTOOL:.c=.c.o))  $(addprefix $(OBJ_FOLDER)/, $(SRC_NAME_COMMON:.c=.c.o))

################################################################################
#################                  RULES                       #################
################################################################################
all : $(LFT)
	@$(MAKE) -j$(NUMPROC) $(OTOOL) --no-print-directory
	@$(MAKE) -j$(NUMPROC) $(NM) --no-print-directory

############## LIBS ############
$(LFT) :
	@printf "$(YLW)Making libft...$(EOC)\n"
	@$(MAKE) -j$(NUMPROC) -s -C libft/
################################

$(NM) : $(LFT) $(OBJ_NM)
	@printf "$(GRN)Linking $@...$(EOC)\n"
	$(CC) $(CFLAGS) $(OBJ_NM) -o $@ $(LDFLAGS) $(LDLIBS)

$(OTOOL)	: $(LFT) $(OBJ_OTOOL)
	@printf "$(GRN)Linking $@...$(EOC)\n"
	$(CC) $(CFLAGS) $(OBJ_OTOOL) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_FOLDER) :
	@mkdir -p $(BUILD_PATH) 2> /dev/null
	@mkdir -p $(OBJ_FOLDER) 2> /dev/null
	@mkdir -p $(addprefix $(OBJ_FOLDER)/,$(SRC_FOLDERS)) 2> /dev/null

$(BUILD_FOLDER)/obj :
	mkdir -p $(BUILD_FOLDER) $(BUILD_FOLDER)/obj 2> /dev/null
	mkdir -p $(addprefix $(OBJ_FOLDER)/,$(SRC_FOLDERS)) 2> /dev/null

#objects
$(OBJ_FOLDER)/%.c.o : $(SRC_PATH)/%.c | $(BUILD_FOLDER)/obj
	@printf "\t$(CC) (...) $@\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_FOLDER)/%.cpp.o : $(SRC_PATH)/%.cpp | $(BUILD_FOLDER)/obj
	@printf "\t$(CXX) (...) $@\n"
	@$(CXX) $(CFLAGS) -o $@ -c $<

# Add rules written in .d files (by gcc -MMD)
# The '-' makes it doesn't care if the file exists or not
-include $(OBJ_NM:.o=.d) $(OBJ_OTOOL:.o=.d)

obj_clean :
	@printf "$(RED)Cleaning $(OBJ_FOLDER)$(EOC)\n"
	@rm -rf $(OBJ_FOLDER)

clean :
	@printf "$(RED)Cleaning $(BUILD_FOLDER)$(EOC)\n"
	@rm -rf $(BUILD_FOLDER)
	@printf "$(YLW)Cleaning libft...$(EOC)\n"
	@make -s fclean -C libft

fclean : clean
	@printf "$(RED)Cleaning $(NAME) & $(ASM)$(EOC)\n"
	@rm -f $(NAME)
	@rm -f $(ASM)

sclean	:	obj_clean
re		:	fclean		all
sre		:	obj_clean		all

.PHONY: all obj_clean clean fclean re sre

RED = \033[1;31m
GRN = \033[1;32m
YLW = \033[1;33m
INV = \033[7m
EOC = \033[0m
