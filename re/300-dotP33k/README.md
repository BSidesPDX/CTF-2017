# RE 300 dotP33k

## Building

1. Put a flag in `guiStager/Form1.Designer.cs`

1. Build Round1 Solution

1. Run guiStager and extract the encrypted key

1. Add key to `canYouREMe/stager.cs` in `public static string encryptedFlag`

1. Set `flag` to something not the actual flag

1. Build Round1 solution 

1. Create a byte array of `canYouREMe.dll` and `guiStager.exe` respectively and place them in the locations of `reMe.cs` and `guiStager.cs` in Round2 

1. Build Round2 

## TODO

Automate the build process. In reality, we only need to given the `round2.exe` during the event so it might not be necessary.

Determine if there is a decent free .NET obfuscator. I do not want to deal with legal issues for a single CTF binary. 
