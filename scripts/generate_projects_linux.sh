cd "$(dirname "$0")/.."

echo "Starting..."

premake5 codelite

echo "Done generating Makefiles using Codelite!"

read -p "Press any key to continue..."

exit $?
