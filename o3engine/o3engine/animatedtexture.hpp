#ifndef ANIMATEDTEXTURE_H_INCLUDED
#define ANIMATEDTEXTURE_H_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"

// STL
#include <map>
#include <vector>

namespace o3engine
{
	//! Class for handling and playing animated textures
	class AnimatedTexture : public Texture
	{
	protected:
		int play_mode;                      //!< Selected play mode
		map<Real, const Image *> playlist;          //!< The playlist
		map<Real, const Image *>::iterator current; //!< Current played
		vector<Image *> v_generated_imgs;           //!< Generated images
		Real total_time;                    //!< The total time
		Real current_time;                  //!< The current time of play

	public:

		enum E_ANIMATED_TEXTURES_PLAYMODE
		{
			PLAY_ONEWAY,        //!< Play until the end reaches and stop
			PLAY_REPEATED,      //!< Play until the end and repeat from start
			PLAY_FORWARDBACK	//!< Play until the end and then the opposite way until the start
		};

		//! Default constructor
		AnimatedTexture(const string & name);

		//! Destructor
		virtual ~AnimatedTexture();

		//! Add a frame
		/**
		@note
			When adding a new frame, AnimatedTexture is not copying image data
			so pointer of Image must be valid until the death of AnimatedTexture
		@param p_image Pointer to an Image object holding the picture of this frame
		@param played_time The time from which this image will be displayed
		*/
		void addFrame(const Image * p_image, Real played_time)
		{   playlist[played_time] = p_image; if (played_time > total_time) total_time = played_time;  playNext(0); }

		//! Play next
		void playNext(Real timepassed);

		//! Reset timer to start from the begining again
		inline void rewind()
		{   current_time = 0; current = playlist.end();    }

		//! Get playmode
		int getPlayMode()const { return play_mode; }

		//! Set playmode
		int setPlayMode(int newmode) { return play_mode = newmode; }

		//! Create intermediate images
		void createIntermediateImages(Real max_interval);
	};
}

#endif // ANIMATEDTEXTURE_H_INCLUDED
