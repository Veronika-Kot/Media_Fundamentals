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
#include <fmod.hpp>
#include <fmod_errors.h>

Console console;

FMOD_RESULT mresult;
FMOD::System *msystem = NULL;
FMOD::Channel	*mchannel = 0;
FMOD::Sound		*msound;
bool mispaused;
bool mshould_exit = false;
bool is_paused;

void handle_keyboard() {
	if (kbhit())
	{		
		char ch = getch();
		if (ch == 27) {
			mshould_exit = true;
		}
		else if (ch == 49) {//1
		}
		else if (ch == 50) {//2
		}
		else if (ch == 51) {//3
		}
		else if (ch == 52) {//4
		}
		else if (ch == 80 || ch == 112) {//p|P pressing P
			mchannel->getPaused(&is_paused);
			mchannel->setPaused(!is_paused);
		}
	}

	
}


int main(){	
	
	

	//TODO: Create the main system object.
	mresult = FMOD::System_Create(&msystem);

	if (mresult != FMOD_OK)
	{
		fprintf(stderr, "FMOD error! (%d)", mresult);
		exit(-1);
	}

	//TODO:Initializes the system object, and the sound device. This has to be called at the start of the user's program
	
	mresult = msystem->init(512, FMOD_INIT_NORMAL, 0);
	if (mresult != FMOD_OK)
	{
		fprintf(stderr, "FMOD error! (%d)", mresult);
		exit(-1);
	}
	//TODO create a sound

	const char* filename = "../common/assets/bump_of_chicken_helloworld.mp3";
	mresult = msystem->createSound(filename, FMOD_DEFAULT, 0, &msound);
	if (mresult != FMOD_OK)
	{
		fprintf(stderr, "FMOD error! (%d)", mresult);
		exit(-1);
	}
	//TODO: play sound

	mresult = msystem->playSound(msound, 0, false, &mchannel);
	if (mresult != FMOD_OK)
	{
		fprintf(stderr, "FMOD error! (%d)", mresult);
		exit(-1);
	}
	

	bool is_channel_playing = false;
	
	

	while(!mshould_exit)
	{
		//get is channel playing
		mresult = mchannel->isPlaying(&is_channel_playing);
		if (mresult != FMOD_OK)
		{
			fprintf(stderr, "FMOD error! (%d)", mresult);
			exit(-1);
		} 

		//is paused

		mresult = mchannel->getPaused(&is_paused);
		if (mresult != FMOD_OK)
		{
			fprintf(stderr, "FMOD error! (%d)", mresult);
			exit(-1);
		}

		//TODO: Important to update system
		


		console.log("==============================================================");
		console.log("Media Fundamentals... Week 02, Play Sound With FMOD");
		console.log("==============================================================");
		console.log("");
		console.log("filename/path: %s", filename);
		console.log("Is Playing: %s", (is_channel_playing) ? "true" : "false");
		console.log("Is Paused: %s", (is_paused) ? "true" : "false");
		
		console.refresh();

		
		handle_keyboard();


	}

	
	//Shutdown
	
	mresult = msound->release();
	if (mresult != FMOD_OK)
	{
		fprintf(stderr, "FMOD error! (%d) %s\n", mresult, FMOD_ErrorString(mresult));
		exit(-1);
	}
	mresult = msystem->close();
	if (mresult != FMOD_OK)
	{
		fprintf(stderr, "FMOD error! (%d) %s\n", mresult, FMOD_ErrorString(mresult));
		exit(-1);
	}
	mresult = msystem->release();
	if (mresult != FMOD_OK)
	{
		fprintf(stderr, "FMOD error! (%d) %s\n", mresult, FMOD_ErrorString(mresult));
		exit(-1);
	}


	return 0;
}