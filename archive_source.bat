rmdir /s /q release\source

mkdir release
mkdir release\source
del /q mihajong\_*.hsp
copy mihajong\*.hsp release\source
copy mihajong\*.as release\source
mkdir release\source\icons
copy mihajong\icons\*.ico release\source\icons
del /q source.zip
cd release
"C:\Program Files\7-zip\7z.exe" a -mx=9 ..\source.zip source
cd ..
