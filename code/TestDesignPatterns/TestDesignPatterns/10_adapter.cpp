#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;
typedef std::string String;

#define SafeDelete(ptr) if (ptr){ delete ptr; ptr = nullptr; }

// interface MediaPlayer
class MediaPlayer {
public:
	virtual void play(const String & audioType, const String & fileName) = 0;
};

// interface AdvancedMediaPlayer
class AdvancedMediaPlayer {
public:
	virtual void playVlc(const String & fileName) = 0;
	virtual void playMp4(const String & fileName) = 0;
};

// Create concrete classes implementing the AdvancedMediaPlayer interface.

// Create concrete class VlcPlayer

class VlcPlayer: public AdvancedMediaPlayer {
public:
	void playVlc(const String & fileName) {
		cout << "Playing vlc file. Name: " << fileName.c_str() << endl;
	}

	void playMp4(const String & fileName) {
		//do nothing
	}
};

// Create concrete class Mp4Player
class Mp4Player : public AdvancedMediaPlayer {
public:
	void playVlc(const String & fileName) {
		//do nothing
	}

	void playMp4(const String & fileName) {
		cout << "Playing mp4 file. Name: " << fileName.c_str() << endl;
	}
};


// Create adapter class implementing the MediaPlayer interface.
class MediaAdapter : public MediaPlayer {
private:
	AdvancedMediaPlayer* advancedMusicPlayer;

public:
	MediaAdapter(const String & audioType) : advancedMusicPlayer(nullptr) {
		if (audioType == "vlc") {
			advancedMusicPlayer = new VlcPlayer();

		}
		else if (audioType == "mp4") {
			advancedMusicPlayer = new Mp4Player();
		}
	}

	virtual ~MediaAdapter()
	{
		SafeDelete(advancedMusicPlayer);
	}

	void play(const String & audioType, const String & fileName) {

		if (audioType == "vlc") {
			advancedMusicPlayer->playVlc(fileName);
		}
		else if (audioType == "mp4") {
			advancedMusicPlayer->playMp4(fileName);
		}
	}
};

// Create concrete class implementing the MediaPlayer interface.
class AudioPlayer : public MediaPlayer {
private:
	MediaAdapter* mediaAdapter;


public:
	AudioPlayer() :mediaAdapter(nullptr){}

	virtual ~AudioPlayer(){	SafeDelete(mediaAdapter);}

	void play(const String & audioType, const String & fileName) {

		//inbuilt support to play mp3 music files
		if (audioType == "mp3") {
			cout << "Playing mp3 file. Name: " << fileName.c_str() << endl;
		}

		//mediaAdapter is providing support to play other file formats
		else if (audioType == "vlc" || audioType == "mp4") {
			SafeDelete(mediaAdapter);
			mediaAdapter = new MediaAdapter(audioType);
			mediaAdapter->play(audioType, fileName);
		}

		else {
			cout << "Invalid media. " << audioType.c_str() << " format not supported" << endl;
		}
	}
};

// Use the AudioPlayer to play different types of audio formats.
void main10(int argc, char ** argv) {
	AudioPlayer* audioPlayer = new AudioPlayer();

	audioPlayer->play("mp3", "beyond the horizon.mp3");
	audioPlayer->play("mp4", "alone.mp4");
	audioPlayer->play("vlc", "far far away.vlc");
	audioPlayer->play("avi", "mind me.avi");

	delete audioPlayer;
}

/*
Playing mp3 file. Name: beyond the horizon.mp3
Playing mp4 file. Name: alone.mp4
Playing vlc file. Name: far far away.vlc
Invalid media. avi format not supported
*/