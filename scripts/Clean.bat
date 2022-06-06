@ECHO OFF
pushd %~dp0\..\

echo "Starting..."

if exist ./bin (
    rmdir /q /s "./bin/"
    rmdir /q /s "./obj/"
)

echo "Done!"

popd
PAUSE

EXIT %ERRORLEVEL%