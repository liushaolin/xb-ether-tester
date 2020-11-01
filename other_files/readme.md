

# Requirements
## pcap or winpcap library
Extract dll from installtion, and use tools to generate.

```dlltool --dllname other_files\npcap\wpcap.dll  --output-lib libwpcap.a```

C:\TDM-GCC-64\x86_64-w64-mingw32\bin\gendef other_files\npcap\wpcap.dll
dlltool.exe -d wpcap.def -D other_files\npcap\wpcap.dll -l WpdPack\Lib\libwpcap.a

```dlltool --dllname other_files\npcap\Packet.dll  --output-lib libpacket.a```

C:\TDM-GCC-64\x86_64-w64-mingw32\bin\gendef other_files\npcap\Packet.dll
dlltool.exe -d Packet.def -D other_files\npcap\Packet.dll -l WpdPack\Lib\libpacket.a

## tdm-gcc
Can download from the following url with Xunlei.

- [x86 version](https://github.com/jmeubank/tdm-gcc/releases/download/v9.2.0-tdm-1/tdm-gcc-9.2.0.exe)
- [x64 version](https://github.com/jmeubank/tdm-gcc/releases/download/v9.2.0-tdm64-1/tdm64-gcc-9.2.0.exe)

