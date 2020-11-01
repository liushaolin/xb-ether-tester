# 
# 本软件为免费、开源软件。
# 本软件的版权(包括源码及二进制发布版本)归一切公众所有。
# 您可以自由使用、传播本软件。
# 您也可以以任何形式、任何目的使用本软件(包括源码及二进制发布版本)，而不受任何版权限制。
# =====================
# 作者: 孙明保
# 邮箱: sunmingbao@126.com
# 

BUILD_TIME:=$(shell echo %date:~0,10%) $(shell echo %time:~0,8%)

CC := gcc

CFLAG := -Wall -O2 -fno-strict-overflow -fno-strict-aliasing -DBUILD_TIME='"$(BUILD_TIME)"' -D_WIN32_IE=0x0501 -D_WIN32_WINNT=0x0502 -DWINVER=0x0501 -DHAVE_REMOTE -DWPCAP 
LDFLAG := -mwindows  -s  -lkernel32 -luser32 -lgdi32 -lcomctl32 -lws2_32 -lwininet -liphlpapi -lWinmm -lwpcap 

CFLAG := $(CFLAG) -D_DEBUG
CFLAG := $(CFLAG) -fno-strict-aliasing

PRJ_DIR:=.
RES_DIR := $(PRJ_DIR)\res
INC_RES_DIRS := --include-dir $(RES_DIR)
INC_DIRS := -I$(PRJ_DIR)\inc -I$(PRJ_DIR)\WpdPack\Include -I$(RES_DIR)
OBJ_DIR:=$(PRJ_DIR)\obj

CFLAG := $(CFLAG) $(INC_DIRS)
LDFLAG := -L$(PRJ_DIR)\WpdPack\Lib $(LDFLAG)
WINDRES_FLAG := --use-temp-file $(INC_RES_DIRS)

# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

### Variables: ###
target := $(OBJ_DIR)\xb_ether_tester.exe

OBJECTS :=  \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/frame_window.o \
	$(OBJ_DIR)/left_window.o \
	$(OBJ_DIR)/right_window.o \
	$(OBJ_DIR)/bottom_window.o \
	$(OBJ_DIR)/splitters.o \
	$(OBJ_DIR)/toolbar_statusbar.o \
	$(OBJ_DIR)/tip_window.o \
	$(OBJ_DIR)/hex_edit_window.o \
	$(OBJ_DIR)/packets_rx_tx.o \
	$(OBJ_DIR)/stats_window.o \
	$(OBJ_DIR)/stream_edit_dlg.o \
	$(OBJ_DIR)/net.o \
	$(OBJ_DIR)/history.o \
	$(OBJ_DIR)/common.o \
	$(OBJ_DIR)/gui.o \
	$(OBJ_DIR)/ver_update.o \
	$(OBJ_DIR)/sample_pkts.o \
	$(OBJ_DIR)/debug.o \
	$(OBJ_DIR)/sample.orc

### Targets: ###

default: $(target)


$(target): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)  $(LDFLAG)

$(OBJ_DIR)/%.orc: $(PRJ_DIR)/res/%.rc
	windres $(WINDRES_FLAG) -i $< -o $@  

$(OBJ_DIR)/%.o: $(PRJ_DIR)/src/%.c
	$(CC) -c $(CFLAG)  -o $@  $<

installer:
	makensis $(PRJ_DIR)\xb_ether_tester.nsi
	
clean:
	-cmd.exe /c del /F /Q  $(OBJ_DIR)\\*

prepare:
	-cmd.exe /c mkdir  $(OBJ_DIR)
	
all: default installer

.PHONY: all prepare default installer clean



