@ECHO OFF
pushd %~dp0\..\

echo "Starting..."

set /p git_command="Type your command: "

for /d %%i in (%cd%\*) do (
    echo *****************************************

    echo "%%i"
    cd "%%i"

    echo -----------------------------------------
    echo %git_command%
    git %git_command%
    echo -----------------------------------------

    echo *****************************************
)

echo "Done!"

popd
PAUSE

EXIT %ERRORLEVEL%