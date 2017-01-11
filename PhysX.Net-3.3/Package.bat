
cd C:\Development\PhysX.Net\PhysX.Net-3.3
C:

md Package
cd Package
rd Working /S /Q
md Working
cd Working
md "PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4"
cd "PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4"
md "Assemblies"
md "Assemblies\x64"
md "Assemblies\x64\Checked"
md "Assemblies\x64\Release"
cd ..\..\..

msbuild PhysX.Net-3.3.4.sln /p:Configuration=Checked;Platform=x64 /t:Clean,Build
msbuild PhysX.Net-3.3.4.sln /p:Configuration=Release;Platform=x64 /t:Clean,Build

# Samples
md "Package\Working\PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4\Samples"
robocopy Samples "Package\Working\PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4\Samples" /E /XF *.suo *.vssscc *.cachefile *.user *.vspscc *.pdb *.vshost.exe* /XD obj Release
md "Package\Working\PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4\Assemblies"
robocopy Assemblies "Package\Working\PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4\Assemblies" /E

xcopy "PhysX.Net-3\bin\x64\Checked\PhysX.Net.dll" "Package\Working\PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4\Assemblies\x64\Checked"
xcopy "PhysX.Net-3\bin\x64\Checked\PhysX.Net.pdb" "Package\Working\PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4\Assemblies\x64\Checked"
xcopy "PhysX.Net-3\bin\x64\Release\PhysX.Net.dll" "Package\Working\PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4\Assemblies\x64\Release"

cd "Package\Working"

attrib * -R /S /D

..\..\..\Tools\7-Zip\7z.exe a "PhysX.Net 0.5.1 for NVIDIA PhysX 3.3.4.zip" .

cd ..\..
