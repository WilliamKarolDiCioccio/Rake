cd "$(dirname "$0")/.."

echo "Starting..."

premake5 gmake2

echo "Done generating Makefiles using GMake2!"

read -p "Press any key to continue..."

exit $?
