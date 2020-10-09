#ifndef _SPRITESHEET_H
#define _SPRITESHEET_H

#include <vector>
#include "texture_cache.h"


class Spritesheet
{
public:
    /*
    Create animation using provided spritesheet image.
     */
    Spritesheet(
            TextureCache* textureCache,
            TextureId textureId,
            std::vector<int> frameDurations, 
            bool loop
    );

    /*
    Starts the animation, setting `isPlaying` = True. Must be called before using the
    other methods!  TODO: MUCH BETTER DOCUMENTATION
     */
    void start();

    // Stops animation
    void stop();

    void reset();

    // whether animation has finished or not
    bool getIsPlaying();

    // whether animation has played
    bool getHasPlayed();

    /*
    Progresses the animation by the specified number of milliseconds.
     */
    void update(long milliseconds);

    /*
    Returns Rect containing coordinates of the current frame, on the spritesheet
    */
    SDL_Rect getCurrentFrameSrc();

    TextureId getTextureID();
    int getFrameW();
    int getFrameH();
    // return number of frames left in animation (not total number of frameCounts!!)
    int getFramesLeft();

private:
    // Texture being used as the spritesheet
    TextureId textureId;
    // Number of frames in the animation
    int numFrames;
    // Dimensions of each frame (px)
    int frameW, frameH;
    // Duration (ms) to show each frame.
    std::vector<int> frameDurationsMs;
    // Whether the animation loops to the start after completing
    bool shouldLoop;
    // Whether this animation is in the process of playing
    bool isPlaying;
    // Whether this animation has completed at least once
    bool hasPlayed;
    // Index of current frame being played
    int currFrameIndex;
    // Time spent on the current frame (ms)
    int timeOnCurrFrameMs;
    // Total runtime of one loop of the animation (ms)
    int totalRuntimeMs;

    void incrementFrame();
};

#endif