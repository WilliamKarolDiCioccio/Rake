# This script is used to install Miniconda3 and create a new environment called RkEnv on final user's machine
# This script should not be used for development enviroment setup purposes.

# Check if running as administrator
if (-not ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Host "Please run this script as an administrator."
    Exit 1
}

# Install Miniconda3 using winget
if (-not (Get-Command conda -ErrorAction SilentlyContinue)) {
    winget install Miniconda3 -e
}

# Add Miniconda3 bin directories to session PATH
$minicondaPath = "$env:ChocolateyToolsLocationC:\tools\miniconda3\condabin"
$env:Path = "$minicondaPath;$env:Path"

# Refresh the environment variables
[System.Environment]::SetEnvironmentVariable("Path", $env:Path, [System.EnvironmentVariableTarget]::Machine)
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", [System.EnvironmentVariableTarget]::Machine)

# Check if the environment RkEnv already exists
if (-not (Get-Command conda -ErrorAction SilentlyContinue) -or -not (conda info --envs | Select-String -Pattern "RkEnv")) {
    # Create a hidden environment called RkEnv
    conda create --name RkEnv --yes --quiet
}
