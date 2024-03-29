# This script is used to install Miniconda3 and create a new environment called RkEnv on final user's machine
# This script should not be used for development enviroment setup purposes.

# Check if running as administrator
if (-not ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Host "Please run this script as an administrator."
    Exit 1
}

# Install Miniconda3 using winget
if (-not (Get-Command conda -ErrorAction SilentlyContinue)) {
    # Install Miniconda using Winget
    winget install Miniconda3 -e

    # Create a hidden environment called RkEnv
    conda create --name RkEnv --yes --quiet
    conda activate RkEnv
    conda config --set auto_activate_base false
    conda deactivate
}