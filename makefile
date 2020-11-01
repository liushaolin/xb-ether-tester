# 
# �����Ϊ��ѡ���Դ�����
# ������İ�Ȩ(����Դ�뼰�����Ʒ����汾)��һ�й������С�
# ����������ʹ�á������������
# ��Ҳ�������κ���ʽ���κ�Ŀ��ʹ�ñ����(����Դ�뼰�����Ʒ����汾)���������κΰ�Ȩ���ơ�
# =====================
# ����: ������
# ����: sunmingbao@126.com
# 

BUILD_TIME:=$(shell echo %date:~0,10%) $(shell echo %time:~0,8%)

CC := gcc

CFLAG := -Wall -O2 -fno-strict-overflow -fno-strict-aliasing -DBUILD_TIME='"$(BUILD_TIME)"' -D_WIN32_IE=0x0501 -D_WIN32_WINNT=0x0502 -DWINVER=0x0501 -DHAVE_REMOTE -DWPCAP 
LDFLAG := -mwindows  -s  -lkernel32 -luser32 -lgdi32 -lcomctl32 -lws2_32 -lwininet -liphlpapi -lWinmm -lwpcap 

#CFLAG := $(CFLAG) -D_DEBUG
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
	$(OBJ_DIR)\main.o \
	$(OBJ_DIR)\frame_window.o \
	$(OBJ_DIR)\left_window.o \
	$(OBJ_DIR)\right_window.o \
	$(OBJ_DIR)\bottom_window.o \
	$(OBJ_DIR)\splitters.o \
	$(OBJ_DIR)\toolbar_statusbar.o \
	$(OBJ_DIR)\tip_window.o \
	$(OBJ_DIR)\hex_edit_window.o \
	$(OBJ_DIR)\packets_rx_tx.o \
	$(OBJ_DIR)\stats_window.o \
	$(OBJ_DIR)\stream_edit_dlg.o \
	$(OBJ_DIR)\net.o \
	$(OBJ_DIR)\history.o \
	$(OBJ_DIR)\common.o \
	$(OBJ_DIR)\gui.o \
	$(OBJ_DIR)\ver_update.o \
	$(OBJ_DIR)\sample_pkts.o \
	$(OBJ_DIR)\debug.o \
	$(OBJ_DIR)\res.orc

### Targets: ###

default: $(target)


$(target): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)  $(LDFLAG)

$(OBJ_DIR)\res.orc: $(PRJ_DIR)\res\sample.rc
	windres $(WINDRES_FLAG) -i $< -o $@  

$(OBJ_DIR)\main.o: $(PRJ_DIR)\src\main.c
	$(CC) -c $(CFLAG)  -o $@  $<

$(OBJ_DIR)\frame_window.o: $(PRJ_DIR)\src\frame_window.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\left_window.o: $(PRJ_DIR)\src\left_window.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\right_window.o: $(PRJ_DIR)\src\right_window.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\bottom_window.o: $(PRJ_DIR)\src\bottom_window.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\splitters.o: $(PRJ_DIR)\src\splitters.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\toolbar_statusbar.o: $(PRJ_DIR)\src\toolbar_statusbar.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\tip_window.o: $(PRJ_DIR)\src\tip_window.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\hex_edit_window.o: $(PRJ_DIR)\src\hex_edit_window.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\packets_rx_tx.o: $(PRJ_DIR)\src\packets_rx_tx.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\stats_window.o: $(PRJ_DIR)\src\stats_window.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\stream_edit_dlg.o: $(PRJ_DIR)\src\stream_edit_dlg.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\net.o: $(PRJ_DIR)\src\net.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\history.o: $(PRJ_DIR)\src\history.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\common.o: $(PRJ_DIR)\src\common.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\gui.o: $(PRJ_DIR)\src\gui.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\ver_update.o: $(PRJ_DIR)\src\ver_update.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\debug.o: $(PRJ_DIR)\src\debug.c
	$(CC) -c $(CFLAG) -o $@  $<

$(OBJ_DIR)\sample_pkts.o: $(PRJ_DIR)\src\sample_pkts.c
	$(CC) -c $(CFLAG) -o $@  $<

installer:
	makensis $(PRJ_DIR)\xb_ether_tester.nsi
	
clean:
	-cmd.exe /c del /F /Q  $(OBJ_DIR)\\*
	-cmd.exe /c copy /y profile.ini  .\$(OBJ_DIR)\\
	-cmd.exe /c copy /y version_update.ini .\$(OBJ_DIR)\\

prepare:
	-cmd.exe /c mkdir  $(OBJ_DIR)
	
all: default installer

.PHONY: all prepare default installer clean



