# Check if running as root
if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root" 1>&2
    exit 1
fi

# Install Premake 5.0.0-beta2
echo "Downloading and installing Premake 5.0.0-beta2..."
wget -q https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-linux.tar.gz -O /tmp/premake.tar.gz
tar -xzf /tmp/premake.tar.gz -C /usr/local/bin --strip-components=1
rm /tmp/premake.tar.gz
echo "Premake 5.0.0-beta2 installed successfully."

# Install Python 3.12 using apt
echo "Installing Python 3.12..."
apt update
apt install -y software-properties-common
add-apt-repository -y ppa:deadsnakes/ppa
apt update
apt install -y python3.12
echo "Python 3.12 installed successfully."

# Install requirements.txt from current folder
echo "Installing requirements.txt..."
pip install -r requirements.txt
echo "Requirements installed successfully."
