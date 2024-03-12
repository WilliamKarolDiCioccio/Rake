@ECHO OFF
pushd %~dp0\..\

echo "Starting..."

call premake5 vs2022

echo "Done!"

popd
PAUSE

EXIT %ERRORLEVEL%