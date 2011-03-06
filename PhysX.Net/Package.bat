
cd E:\Development\PhysX.Net\PhysX.Net

cd Package
rd Working /S /Q
md Working
cd Working
md "Reference Assemblies"
md "Reference Assemblies\x86"
md "Reference Assemblies\x86\Debug"
md "Reference Assemblies\x86\Release"
md "Reference Assemblies\x64"
md "Reference Assemblies\x64\Debug"
md "Reference Assemblies\x64\Release"
cd ..\..

msbuild PhysX.Net.sln /p:Configuration=Debug;Platform=x86
msbuild PhysX.Net.sln /p:Configuration=Release;Platform=x86
msbuild PhysX.Net.sln /p:Configuration=Debug;Platform=x64
msbuild PhysX.Net.sln /p:Configuration=Release;Platform=x64

xcopy "PhysX.Net\bin\x86\Debug\StillDesign.PhysX.Net.dll" "Package\Working\Reference Assemblies\x86\Debug"
xcopy "PhysX.Net\bin\x86\Debug\StillDesign.PhysX.Net.pdb" "Package\Working\Reference Assemblies\x86\Debug"
xcopy "PhysX.Net\bin\x86\Release\StillDesign.PhysX.Net.dll" "Package\Working\Reference Assemblies\x86\Release"

xcopy "PhysX.Net\bin\x64\Debug\StillDesign.PhysX.Net.dll" "Package\Working\Reference Assemblies\x64\Debug"
xcopy "PhysX.Net\bin\x64\Debug\StillDesign.PhysX.Net.pdb" "Package\Working\Reference Assemblies\x64\Debug"
xcopy "PhysX.Net\bin\x64\Release\StillDesign.PhysX.Net.dll" "Package\Working\Reference Assemblies\x64\Release"

md Package\Working\Samples
robocopy Samples Package\Working\Samples /E /XF *.suo *.vssscc *.cachefile *.user *.vspscc *.pdb /XD obj Release

cd Package\Working
..\..\Tools\7-Zip\7z.exe a "PhysX 0.12.0.0.zip" .
