
SET TMP=C:\Temp
SET TEMP=C:\Temp

SET UVEXE=C:\Keil\UV4\UV4.EXE

%UVEXE% -b usblib-cm3.uvproj -t"usblib-cm3" -o"usblib-cm3.log"
%UVEXE% -b usblib-cm4f.uvproj -t"usblib-cm4f" -o"usblib-cm4f.log"
