param (
    [string]$version = $(throw "No version specified")
)

. ./appveyor/ApplyVersion.ps1

Write-Host "Apply to appveyor.yml" -ForegroundColor "Yellow"
ApplyVersionToAppVeyorYml "$version.{build}"

Write-Host "Apply to src\VersionInfo.h" -ForegroundColor "Yellow"
ApplyVersionToVersionInfoH "$version-dev"

Write-Host "Apply to src\LightFXExtender.rc" -ForegroundColor "Yellow"
ApplyVersionToResource "$version.0-dev"
