# This is basically a powershell script to build a c file with the correct options. I got it from chatgpt, and made some modifications
param (
    [Parameter(Mandatory=$true, Position = 0, ValueFromPipeline = $true)]
    [SupportsWildcards()]
    [ValidateScript({ Test-Path $_ })]
    [string[]]$Path,
    [Parameter(Mandatory=$false, Position = 1)]
    [switch]$r
)

$compilerOptions = "-lm -Wall -Wextra -pedantic -std=c99 -O0 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector -g3 -ggdb"
$compiler = "gcc"

# Show options to the user
Write-Output "Compiling with these options: $compilerOptions"
# Execute the compiler command
$inputFiles = ForEach-Object -InputObject $Path {Get-ChildItem -Path $_}

foreach($file in $inputFiles) {
    Write-Output "Compiling $file..."

    # Set the name of the output file to be the same as the input file, but with the extension changed to "exe"
    $outputFile = [IO.Path]::ChangeExtension($file, "exe")

    # Build the compiler command
    $compilerCommand = "$compiler $file -o $outputFile $compilerOptions"

    # Run it
    Invoke-Expression $compilerCommand

    # Check the result of the compilation, and inform the user accordingly
    if ($LASTEXITCODE -eq 0) {
        Write-Output "Compilation Successful.`n`nOutput File: $outputFile"
        if ($r) {
            Write-Output "Running Exec...`n"
            Invoke-Expression "gdb $outputFile"
            Write-Output "`nFinished Running!"
        }
    } else {
        Write-Output "`nCompilation failed with error code: $LASTEXITCODE`n"
    }
}