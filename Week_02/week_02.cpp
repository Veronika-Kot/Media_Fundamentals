///*
//==================================================================================================================================================================
//|Copyright 2018 Oscar Lara	- scarlara@hotmail.com																												   |
//|																																								   |
//|See individual libraries separate legal notices																												   |
//|																																								   |
//|Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),				   |
//|to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,				   |
//|and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :					   |
//|																																								   |
//|The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.									   |
//|																																								   |
//|THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,			   |
//|FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,	   |
//|WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.		   |
//==================================================================================================================================================================
//*/
//


#include "common\src\utils\console.h"


#include <Windows.h>
#pragma comment(lib, "Winmm.lib")

#include <stdio.h>
#include <iostream>
#include <conio.h>



Console console;


//WAV file format
//http://soundfile.sapp.org/doc/WaveFormat/



struct  WAV_HEADER
{
	unsigned char chunkid[4];
	unsigned char chunksize[4];
	unsigned char format[4];
	unsigned char subchunck1id[4];
	unsigned char subchunk1size[4];
	unsigned char audioformat[2];
	unsigned char numchannels[2];
	unsigned char samplerate[4];
	unsigned char byterate[4];
	unsigned char blockalign[2];
	unsigned char bitpersample[2];
	unsigned char subchunk2id[4];
	unsigned char subchink2size[4];
};



bool esc_pressed() {
	if (kbhit())
	{		
		char ch = getch();
		if (ch == 27) return true;
	}

	return false;
}



int main(){	
	
	bool should_exit = false;
	WAV_HEADER wavHeader;

	const char* filePath = "../common/assets/drumloop.wav";

	FILE* wavFile = fopen(filePath, "r");
	if (wavFile == nullptr)
	{
		fprintf(stderr, "Unable to open wave file: %s\n", filePath);
		return 1;
	}

	PlaySound(TEXT(filePath), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC );

	size_t bytesRead = fread(&wavHeader, 1, sizeof(WAV_HEADER), wavFile);
	console.log("Bytes: %d", bytesRead);
	console.lock_start_row();

	while(!should_exit)
	{
		//console.log("Nothing to do yet..!");
		if (bytesRead > 0){
			console.log("Chunked ID containes letters RIFF: %c%c%c%c", wavHeader.chunkid[0], wavHeader.chunkid[1], wavHeader.chunkid[2], wavHeader.chunkid[3]);
			console.log("Size the rest of the chunk: %d", little_endian_to_int(wavHeader.chunksize, 4)); 
			console.log("Format containes letters WAVE: %c%c%c%c", wavHeader.format[0], wavHeader.format[1], wavHeader.format[2], wavHeader.format[3]);
			console.log("Subchunck1id containes letters fmt: %c%c%c", wavHeader.subchunck1id[0], wavHeader.subchunck1id[1], wavHeader.subchunck1id[2]);
			console.log("Subchunk1size containes size of the rest of the subchink: %d", little_endian_to_int(wavHeader.subchunk1size, 4));
			console.log("Audioformat contains a number (if other than 1 indicate some form of compression.): %i", little_endian_to_int(wavHeader.audioformat, 2));
			console.log("Numchannels contains a number (Mono = 1, Stereo = 2, etc) : %i", little_endian_to_int(wavHeader.numchannels, 2));
			console.log("Samplerate contains: %d", little_endian_to_int(wavHeader.samplerate, 2));
		    console.log("Byterate contains: %d", little_endian_to_int(wavHeader.byterate, 2));
		}
		console.refresh();

		//Exit loop?
		should_exit = esc_pressed();


	}

	

	return 0;
}