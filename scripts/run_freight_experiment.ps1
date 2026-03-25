param(
    [Parameter(Mandatory = $true)]
    [string]$Executable,

    [string[]]$Arguments = @()
)

$repoRoot = Split-Path -Parent $PSScriptRoot

Push-Location $repoRoot
try {
    New-Item -ItemType Directory -Force "simulation_results" | Out-Null

    $exePath = Join-Path $repoRoot $Executable
    if (-not (Test-Path $exePath)) {
        $candidate = "$exePath.exe"
        if (Test-Path $candidate) {
            $exePath = $candidate
        }
    }

    if (-not (Test-Path $exePath)) {
        throw "Executable '$Executable' was not found in bin/. Build first with 'make all' in Command Prompt or '.\\make.bat all' in PowerShell."
    }

    & $exePath @Arguments
    if ($LASTEXITCODE -ne 0) {
        throw "Experiment failed with exit code $LASTEXITCODE."
    }
}
finally {
    Pop-Location
}
