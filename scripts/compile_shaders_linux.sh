cd "$(dirname "$0")/../assets/shaders"

echo "Starting..."

mkdir -p "../../Testbed/assets/shaders"

for shader_file in $(find . -type f -name "*.vert" -o -name "*.frag" -o -name "*.comp"); do
    glslangValidator -V "$shader_file" -o "${shader_file}.spv"
done

find . -type f -name "*.spv" -exec mv {} ../../Testbed/assets/shaders/ \;

echo "Done!"

exit $?
