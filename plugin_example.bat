Set FREI0R_PATH=x64\Release
"ffmpeg\bin\ffmpeg.exe" -y -t 2 -i TestDepthMap\resources\video\sherlocksbs.mp4 -filter_complex "[0:v]format=pix_fmts=bgra" -pix_fmt yuv420p -c:v libx264 out_test.mp4
"ffmpeg\bin\ffmpeg.exe" -y -i TestDepthMap\resources\video\sherlocksbs.mp4 -filter_complex "[0:v]format=pix_fmts=bgra,frei0r=filter_name=FilterDepthMap:filter_params=1|1" -pix_fmt yuv420p -c:v libx264 out.mp4
pause
