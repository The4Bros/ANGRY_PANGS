#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(Application* app) : Module(app)
{
	music = NULL;
}

bool ModuleAudio::Init()
{
	//SDL_Init(0);

	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags);

	if (initted != flags && flags != flags){ return false; }

	if (Mix_OpenAudio(44100, AUDIO_U8 /*MIX_DEFAULT_FORMAT*/, 2, 2048) == -1){ return false; } // Initialize SDL_mixer

	return true;
}
update_status ModuleAudio::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleAudio::Update(){ return UPDATE_CONTINUE; }
update_status ModuleAudio::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModuleAudio::CleanUp()
{
	if (music != NULL){ Mix_FreeMusic(music); }

	for (DoubleNode<Mix_Chunk*>* item = fx.getStart(); item != NULL; item = item->next){ Mix_FreeChunk(item->data); }

	fx.clear();
	Mix_CloseAudio();

	while (Mix_Init(0)){ Mix_Quit(); } //each call to Mix_Init may set different flags
		
	return true;
}


bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	if (music != NULL)
	{
		if (fade_time > 0.0f){ Mix_FadeOutMusic((int)(fade_time * 1000.0f)); }
		else{ Mix_HaltMusic(); }

		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL){ return false; }
	else
	{
		if (fade_time > 0.0f)
		{
			if ((Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)){ return false; }
		}
		else if (Mix_PlayMusic(music, -1) < 0){ return false; }
	}

	return true;
}

// Load WAV
unsigned int ModuleAudio::LoadFx(const char* path)
{
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk != NULL)
	{
		fx.push(chunk);
		return fx.Count();
	}

	return 0;
}

// Play WAV
bool ModuleAudio::PlayFx(unsigned int id, int repeat)
{
	Mix_Chunk* chunk = NULL;

	if (fx.at(id - 1, chunk))
	{
		Mix_PlayChannel(-1, chunk, repeat);
		return true;
	}

	return false;
}