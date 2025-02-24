param (
    [string]$buildMode = "Debug",
    [string]$installPrefix,
    [string]$moduleDestination
)
if (($buildMode -eq "Debug" -or $buildMode -eq "Release") -and ($installPrefix -ne "") -and ($moduleDestination -ne ""))
{
    git clone --recursive https://github.com/Neargye/magic_enum.git "$moduleDestination/modules/magic_enum"
    cmake -S "$moduleDestination/modules/magic_enum" -B "$moduleDestination/dependencies/windows/magic_enum" -DCMAKE_INSTALL_PREFIX="$installPrefix"
    cmake --build "$moduleDestination/dependencies/windows/magic_enum" --config "$buildMode" --target install
}
else
{
    Write-Output "Invalid build type or install path. Please provide either 'Debug' or 'Release', a valid prefix path and a valid Module Destination"
}
