# OTS: Open Terminal Studio

<img width="160" height="160" alt="ots_logo" src="https://github.com/user-attachments/assets/0758fe11-e898-407b-9535-c3cb16d5d7d2" align="right" />

Back in my day, we didn't have any fancy "desktop applications" with their "gooeys" and full-featured environments: we had the command line and you had to figure out the rest. OTS gives you a taste of those better days by allowing you to record your desktop and play back your recordings, all within your terminal!

OTS takes captures of your desktop and compresses it to an array of pixels, which it then renders using ASCII and ANSI, packing two pixels into each character. In this way, OTS can render anything on your screen!

<img width="2534" height="1363" alt="record-shipwrecked-screenshot" src="https://github.com/user-attachments/assets/fd8cbf72-1f01-4c2c-b45c-056ff1dfd1cb" />
<img width="1722" height="857" alt="playback-shipwrecked-screenshot" src="https://github.com/user-attachments/assets/16d945e4-654e-4b3b-b0d4-fc004991a2dc" />

## Features:
- Desktop mirroring at a 120x55 pixel resolution (capture is automatically downsized)
- Recording clips of mirrored desktop and saving to a small file compressed with zlib
- Loading from compressed file and playing back video

## Setup instructions (WINDOWS ONLY):
- If you don't have it already, download the appropriate release of the [Microsoft Visual C++ Redistributable](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170) -- libraries from this are needed for the program to work
- Download the .zip from releases
- Extract the .zip
- Run the .exe

## Controls:
- R - Start recording
- S - End recording and save to specified filepath (will enter pause mode)
- P - Pause/Unpause
- Q - Quit
