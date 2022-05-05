@ECHO OFF
pushd %~dp0\..\

echo "Starting..."

if exist ./bin/Debug-windows-x86_64 (
    @RD /S /Q "./bin/Debug-windows-x86_64"
    @RD /S /Q "./obj/Debug-windows-x86_64"
) else (
    echo "./bin/Debug-windows-x86_64 does not exist."
)
if exist ./bin/Development-windows-x86_64 (
    @RD /S /Q "./bin/Development-windows-x86_64"
    @RD /S /Q "./obj/Development-windows-x86_64"
) else (
    echo "./bin/Development-windows-x86_64 does not exist."
)
if exist ./bin/Release-windows-x86_64 (
    @RD /S /Q "./bin/Release-windows-x86_64"
    @RD /S /Q "./obj/Release-windows-x86_64"
) else (
    echo "./bin/Release-windows-x86_64 does not exist."
)

echo "Done!"

popd
PAUSE

EXIT %ERRORLEVEL%