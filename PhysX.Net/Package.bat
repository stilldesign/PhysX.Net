
cd E:\Development\PhysX.Net\PhysX.Net
E:

cd Package
rd Working /S /Q
md Working
cd Working
cd ..\..

# Samples
md Package\Working\Samples
robocopy Samples Package\Working\Samples /E /XF *.suo *.vssscc *.cachefile *.user *.vspscc *.pdb /XD obj Release
md Package\Working\Assemblies
robocopy Assemblies Package\Working\Assemblies /E

md "Assemblies"
md "Assemblies\x86"
md "Assemblies\x86\Debug"
md "Assemblies\x86\Release"
md "Assemblies\x64"
md "Assemblies\x64\Debug"
md "Assemblies\x64\Release"

#msbuild PhysX.Net.sln /p:Configuration=Debug;Platform=x86
#msbuild PhysX.Net.sln /p:Configuration=Release;Platform=x86
#msbuild PhysX.Net.sln /p:Configuration=Debug;Platform=x64
#msbuild PhysX.Net.sln /p:Configuration=Release;Platform=x64

xcopy "PhysX.Net\bin\x86\Debug\StillDesign.PhysX.Net.dll" "Package\Working\Assemblies\x86\Debug"
xcopy "PhysX.Net\bin\x86\Debug\StillDesign.PhysX.Net.pdb" "Package\Working\Assemblies\x86\Debug"
xcopy "PhysX.Net\bin\x86\Release\StillDesign.PhysX.Net.dll" "Package\Working\Assemblies\x86\Release"

xcopy "PhysX.Net\bin\x64\Debug\StillDesign.PhysX.Net.dll" "Package\Working\Assemblies\x64\Debug"
xcopy "PhysX.Net\bin\x64\Debug\StillDesign.PhysX.Net.pdb" "Package\Working\Assemblies\x64\Debug"
xcopy "PhysX.Net\bin\x64\Release\StillDesign.PhysX.Net.dll" "Package\Working\Assemblies\x64\Release"

cd Package\Working

attrib * -R /S /D
..\..\Tools\StripSourceControl "Samples\PhysX.Net Samples.sln"
..\..\Tools\7-Zip\7z.exe a "PhysX 0.12.0.0.zip" .

cd ..\..
