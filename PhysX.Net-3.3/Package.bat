
cd C:\Development\PhysX.Net\PhysX.Net-3.3
C:

md Package
cd Package
rd Working /S /Q
md Working
cd Working
md "PhysX.Net 0.4 for NVIDIA PhysX 3.3.3"
cd "PhysX.Net 0.4 for NVIDIA PhysX 3.3.3"
md "Assemblies"
md "Assemblies\x86"
md "Assemblies\x86\Debug"
md "Assemblies\x86\Release"
md "Assemblies\x64"
md "Assemblies\x64\Debug"
md "Assemblies\x64\Release"
cd ..\..\..

msbuild PhysX.Net-3.3.1.sln /p:Configuration=Debug;Platform=x86 /t:Clean,Build
msbuild PhysX.Net-3.3.1.sln /p:Configuration=Release;Platform=x86 /t:Clean,Build
msbuild PhysX.Net-3.3.1.sln /p:Configuration=Debug;Platform=x64 /t:Clean,Build
msbuild PhysX.Net-3.3.1.sln /p:Configuration=Release;Platform=x64 /t:Clean,Build

# Samples
md "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Samples"
robocopy Samples "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Samples" /E /XF *.suo *.vssscc *.cachefile *.user *.vspscc *.pdb *.vshost.exe* /XD obj Release
md "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies"
robocopy Assemblies "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies" /E

xcopy "PhysX.Net-3\bin\x86\Debug\PhysX.Net.dll" "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies\x86\Debug"
xcopy "PhysX.Net-3\bin\x86\Debug\PhysX.Net.pdb" "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies\x86\Debug"
xcopy "PhysX.Net-3\bin\x86\Release\PhysX.Net.dll" "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies\x86\Release"

xcopy "PhysX.Net-3\bin\x64\Debug\PhysX.Net.dll" "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies\x64\Debug"
xcopy "PhysX.Net-3\bin\x64\Debug\PhysX.Net.pdb" "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies\x64\Debug"
xcopy "PhysX.Net-3\bin\x64\Release\PhysX.Net.dll" "Package\Working\PhysX.Net 0.4 for NVIDIA PhysX 3.3.3\Assemblies\x64\Release"

cd "Package\Working"

attrib * -R /S /D

..\..\..\Tools\7-Zip\7z.exe a "PhysX.Net 0.4 for NVIDIA PhysX 3.3.3.zip" .

cd ..\..
