Set WshShell = CreateObject("WScript.Shell")
Set fso = CreateObject("Scripting.FileSystemObject")

' Get the folder where this .vbs file is located
currentFolder = fso.GetParentFolderName(WScript.ScriptFullName)

' Build the full path to Ultimate2026.exe in the same folder
exePath = Chr(34) & currentFolder & "\Ultimate2026.exe" & Chr(34)

' Run silently with flags
WshShell.Run exePath & " /silent /norestart", 0, True