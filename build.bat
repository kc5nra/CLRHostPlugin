pushd %_CWD% 
set _CWD=%CD% 
popd 

for /f "delims=" %%a in ('"%GIT_BIN_DIR%\git" describe') do @set CHP_VERSION_BARE=%%a

set CHP_VERSION="CHP_VERSION=L"%CHP_VERSION_BARE%-x64""
msbuild /t:Rebuild /property:Configuration=Release;Platform=x64

rd Releasex64 /s /q
mkdir Releasex64
mkdir Releasex64\CLRHostPlugin

copy CLRHostPlugin\x64\Release\CLRHostPlugin.dll Releasex64\
copy CLRHostInterop\x64\Release\CLRHost.Interop.dll Releasex64\CLRHostPlugin\


cd Releasex64
7z a CHP-%CHP_VERSION_BARE%-x64.7z .
move CHP-%CHP_VERSION_BARE%-x64.7z ..
cd ..

set CHP_VERSION="CHP_VERSION=L"%CHP_VERSION_BARE%-x86""
msbuild /t:Rebuild /property:Configuration=Release;Platform=win32

rd Releasex86 /s /q
mkdir Releasex86
mkdir Releasex86\CLRHostPlugin

copy CLRHostPlugin\win32\Release\CLRHostPlugin.dll Releasex86\
copy CLRHostInterop\win32\Release\CLRHost.Interop.dll Releasex86\CLRHostPlugin\

cd Releasex86
7z a CHP-%CHP_VERSION_BARE%-x86.7z .
move CHP-%CHP_VERSION_BARE%-x86.7z ..
cd ..

rd Samples /s /q
mkdir Samples
mkdir Samples\CLRCSharpSamplePlugin
xcopy CLRCSharpSamplePlugin\* Samples\CLRCSharpSamplePlugin /s
rd /s /q Samples\CLRCSharpSamplePlugin\bin
rd /s /q Samples\CLRCSharpSamplePlugin\obj

cd Samples
7z a CHP-%CHP_VERSION_BARE%-Samples.7z .
move CHP-%CHP_VERSION_BARE%-Samples.7z ..
cd ..
