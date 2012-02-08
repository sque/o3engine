#include "./animatedtexture.hpp"


namespace o3engine
{
	AnimatedTexture::AnimatedTexture(const string & name)
		:Texture(name)
	{
		current = playlist.end();
		total_time = 0;
		current_time = 0;
		play_mode = PLAY_REPEATED;
	}

	AnimatedTexture::~AnimatedTexture()
	{
		vector<Image *>::iterator it;

		while ((it = v_generated_imgs.begin()) != v_generated_imgs.end())
		{
			delete (*it);
			v_generated_imgs.erase(it);
		}
	}

	//! Play next
	void AnimatedTexture::playNext(Real timepassed)
	{   map<Real, const Image *>::iterator it;

		// Increase current time
		current_time += timepassed;

		// Check if we reached the end
		if (current_time > total_time)
		{
			switch(play_mode)
			{
			case PLAY_ONEWAY:
				return; // Bye!
			case PLAY_REPEATED:
				current_time -= total_time;
				break;
			case PLAY_FORWARDBACK:  //! we will see it
				break;
			}
		}

		// Select new image
		for(it = playlist.begin();it != playlist.end();it++)
		{
			// Find 1st frame above desired time
			if (it->first > current_time)
			{   it--;   // Go back now

				// Check if it is already loaded
				if (current != it)
				{
					setImage(*it->second);
					current = it;
				}
				break;
			}
		}
	}

	//! Create intermediate images
	void AnimatedTexture::createIntermediateImages(Real max_interval)
	{   map<Real, const Image *>::iterator it, next;
		Real frames_interval;
		int new_frames, i;
		Image * p_image;

		for(it = playlist.begin();it != playlist.end();it++)
		{   next = ++it; it --;
			// We create new frames between existing ones, we don't expand
			if (next != playlist.end())
			{   frames_interval = next->first - it->first;
				new_frames = (int)floor((Real)frames_interval / max_interval);
				for(i = 1;i < new_frames;i++)
				{
					// Create a new image
					p_image = new Image(*it->second);
					// Mix it
					p_image->blend(*next->second, (max_interval*i)/frames_interval);
					// Store it for later deletion
					v_generated_imgs.push_back(p_image);
					// Save  frame
					playlist[it->first + (max_interval * i)] = p_image;
				}
			}
		}
	}
}
