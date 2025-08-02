# Usage
``` powershell
.\compiledb4ms.exe [-t <arch_type>] [-s <sln_file>] ... [-p <vcxproj_file>] ...

  -t <arch_type> = Default to "Debug|x64"
                   Combinations of "Release", "Debug" with "x64", "x86"
                   Indicates the arch type of the arguments following it
```

## example
``` powershell
# arch_type = Debug|x64
.\compiledb4ms.exe -s .\build\main.sln
```
``` powershell
# arch_type = Debug|x64
.\compiledb4ms.exe -p .\build\a.vcxproj -p .\build\b.vcxproj
```
``` powershell
.\compiledb4ms.exe -t "Release|x64" -p .\build\a.vcxproj -p .\build\b.vcxproj
```
``` powershell
# the arch_type of project a is Debug|x64, the arch_type of project b is Release|x64
.\compiledb4ms.exe -p .\build\a.vcxproj -t "Release|x64" -p .\build\b.vcxproj

# the arch_type of project c is Debug|x64
.\compiledb4ms.exe -p .\build\a.vcxproj -t "Release|x64" -p .\build\b.vcxproj -t "Debug|x64" -p .\build\c.vcxproj
```