# Check if running as administrator
if (-not ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole] "Administrator")) {
    Write-Host "Please run this script as an administrator."
    Exit 1
}

# Install Chocolatey
if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
    Write-Host "Installing Chocolatey..."
    Set-ExecutionPolicy Bypass -Scope Process -Force
    Invoke-Expression ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
}

# Install Premake5 using Chocolatey
if (-not (Get-Command premake5 -ErrorAction SilentlyContinue)) {
    Write-Host "Installing Premake5..."
    choco install premake5 -y
}

# Install Python 3.12 using Chocolatey
if (-not (Get-Command python -ErrorAction SilentlyContinue)) {
    Write-Host "Installing Python 3.12..."
    choco install python --version 3.12 -y
}

# Install Miniconda3 using Chocolatey and create a new environment called RkEnv
if (-not (Get-Command conda -ErrorAction SilentlyContinue)) {
    choco install miniconda3

    conda create --name RkEnv --yes --quiet
    conda activate RkEnv
    conda config --set auto_activate_base false
    conda deactivate
}

# Add Python and Chocolatey bin directories to PATH
$pythonPath = (Get-Command python).Path
$chocoBinPath = [System.Environment]::GetEnvironmentVariable("ChocolateyInstall", [System.EnvironmentVariableTarget]::Machine) + "\bin"
[Environment]::SetEnvironmentVariable("PATH", "$pythonPath;$chocoBinPath;$env:PATH", [EnvironmentVariableTarget]::Machine)

# Install Python dependencies using pip
Write-Host "Installing Python dependencies using pip..."
pip install -r ./scripts/requirements.txt

Write-Host "Installation completed successfully."