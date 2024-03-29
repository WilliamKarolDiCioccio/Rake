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

# Install Miniconda3 using Chocolatey
if (-not (Get-Command conda -ErrorAction SilentlyContinue)) {
    choco install miniconda3 -y
}

# Add Python and Miniconda3 bin directories to PATH
$pythonPath = (Get-Command python).Path
$minicondaPath = "$env:ChocolateyToolsLocation\miniconda3\condabin"
[Environment]::SetEnvironmentVariable("PATH", "$pythonPath;$minicondaPath;$env:PATH", [EnvironmentVariableTarget]::Machine)
Write-Host $PWD

# Install Python dependencies using pip
Write-Host "Installing Python dependencies using pip..."
pip install -r https://raw.githubusercontent.com/WilliamKarolDiCioccio/Rake/main/scripts/requirements.txt

# Check if the environment RkEnv already exists
if (-not (Get-Command conda -ErrorAction SilentlyContinue) -or -not (conda info --envs | Select-String -Pattern "RkEnv")) {
    # Create a hidden environment called RkEnv
    conda create --name RkEnv --yes --quiet
}

Write-Host "Installation completed successfully."