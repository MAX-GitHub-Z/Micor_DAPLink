
SET TMP=C:\Temp
SET TEMP=C:\Temp

SET UVEXE=C:\Keil\UV4\UV4.EXE

%UVEXE% -b grlib-cm3.uvproj -t"grlib-cm3" -o"grlib-cm3.log"
%UVEXE% -b grlib-cm4f.uvproj -t"grlib-cm4f" -o"grlib-cm4f.log"
