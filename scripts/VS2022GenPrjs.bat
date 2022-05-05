@ECHO OFF
pushd %~dp0\..\

echo "Starting..."

call .\\thirdparties\\premake\\premake5.exe vs2022

echo "Done!"

popd
PAUSE

EXIT %ERRORLEVEL%