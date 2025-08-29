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

## Background

### Why it was made
I wanted to get more experience with C++, and I've always been drawn to the useless elegance of apps that run entirely in the terminal for no good reason. I decided to do a recording software because I hadn't seen any terminal apps like it (and because I wanted to render something big and colorful with ANSI).

## How it was made
First, I used the Windows system library to capture the pixels from the user's desktop. Next, I compressed those pixels via averaging so they fit within the console. I then used the Unicode Lower Half Block character (▄) with ANSI color codes to render the pixels to the console. I was able to get two pixels into each character by coloring the text (Lower Half Block) the color of the bottom pixel and the background of the character the color of the top pixel. To record, I captured the arrays of pixels and saved them to a file compressed with zlib, then, for playback, I unzipped it using the same method and iterated through the array.

## Struggles
C++, in general. Also, I realized I needed a way to compress the video files after they were recorded (instead of just dumping all the characters in a text file), so I decided to import a library to help, but in order to do so cleanly, I had to convert my entire project over to CMake. This meant that I needed to create an entirely new CMake Visual Studio project and transfer all of the code to there before wrestling with Git to make it stay on the same repository (which is why there is a separate branch with the final code on it). 
