taskkill /IM mGBA.exe
taskkill /IM bgb64.exe
del obj\*.sym
del obj\*.o
del obj\*.lst
del obj\*.gb
del obj\*.ihx
del obj\*.map
del obj\*.noi
del obj\*.asm
mkdir obj
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba0 -c -o obj\bank_00.o src\banks\bank_00.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba1 -c -o obj\bank_01.o src\banks\bank_01.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba2 -c -o obj\bank_02.o src\banks\bank_02.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba3 -c -o obj\bank_03.o src\banks\bank_03.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba4 -c -o obj\bank_04.o src\banks\bank_04.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba5 -c -o obj\bank_05.o src\banks\bank_05.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba6 -c -o obj\bank_06.o src\banks\bank_06.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba7 -c -o obj\bank_07.o src\banks\bank_07.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba8 -c -o obj\bank_08.o src\banks\bank_08.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba9 -c -o obj\bank_09.o src\banks\bank_09.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba10 -c -o obj\bank_10.o src\banks\bank_10.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba11 -c -o obj\bank_11.o src\banks\bank_11.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba12 -c -o obj\bank_12.o src\banks\bank_12.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba13 -c -o obj\bank_13.o src\banks\bank_13.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba14 -c -o obj\bank_14.o src\banks\bank_14.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba15 -c -o obj\bank_15.o src\banks\bank_15.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-ba16 -c -o obj\bank_16.o src\banks\bank_16.c

..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o obj\main.o src\main.c
..\..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yt0xFC -Wl-yo4 -Wl-ya16 -o obj\gbfs.gb obj\main.o obj\bank_00.o obj\bank_01.o obj\bank_02.o obj\bank_03.o obj\bank_04.o obj\bank_05.o obj\bank_06.o obj\bank_07.o obj\bank_08.o obj\bank_09.o obj\bank_10.o obj\bank_11.o obj\bank_12.o obj\bank_13.o obj\bank_14.o obj\bank_15.o obj\bank_16.o

start /b "" obj\gbfs.gb
