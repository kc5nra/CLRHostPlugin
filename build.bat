
pushd %_CWD% 
set _CWD=%CD% 
popd 

for /f "delims=" %%a in ('"%GIT_BIN_DIR%\git" describe') do @set SPP_VERSION_BARE=%%a

set SPP_VERSION="SPP_VERSION=L"%SPP_VERSION_BARE%-x64""
msbuild /t:Rebuild /property:Configuration=Release;Platform=x64

del SPP-%SPP_VERSION_BARE%.zip
zip -j SPP-%SPP_VERSION_BARE%-x64.zip x64\Release\ServerPingPlugin.dll

set SPP_VERSION="SPP_VERSION=L"%SPP_VERSION_BARE%-x86""
msbuild /t:Rebuild /property:Configuration=Release;Platform=Win32

del SPP-%SPP_VERSION_BARE%.zip
zip -j SPP-%SPP_VERSION_BARE%-x86.zip Release\ServerPingPlugin.dll