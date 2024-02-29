@ECHO OFF
pushd %~dp0\..\assets\shaders\

echo "Starting..."

if not exist "..\..\Testbed\assets\shaders" (
    mkdir "..\..\Testbed\assets\shaders" 2>nul
)

for /R %%f in (*) do (
    %VULKAN_SDK%\Bin\glslc.exe %%f -o %%f.spv
)

for /R %%f in (*.spv) do (
    move %%f ../../Testbed/assets/shaders/
)

echo "Done!"

popd
PAUSE

EXIT %ERRORLEVEL%