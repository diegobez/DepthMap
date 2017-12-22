Set FREI0R_PATH=C://Users/Enrique/Documents/GitHub/DepthMap/x64/Release

"ffmpeg\bin\ffmpeg.exe" -y -t 5 -i resources\video\sherlock_4096.mp4 -filter_complex "[0:v]format=pix_fmts=bgra,frei0r=filter_name=FilterDepthMap:filter_params=1|1" -pix_fmt yuv420p -c:v libx264 out2.mp4

pause
,crop=4096:2048:0:0