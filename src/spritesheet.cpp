#include "spritesheet.h"

Spritesheet::Spritesheet(
        TextureCache* textureCache,
        TextureId textureId,
        std::vector<int> frameDurations, 
        bool loop
) {
    this->textureId = textureId;
    frameDurationsMs = frameDurations;
    shouldLoop = loop;

    numFrames = frameDurationsMs.size();
    // Get size of full sheet
    int sheet_width, sheet_height;
    std::tie(sheet_width, sheet_height) = 
        textureCache->getDimensions(this->textureId);

    frameW = sheet_width / numFrames;
    frameH = sheet_height;

    for (int frame_duration : frameDurations) 
    {
        totalRuntimeMs += frame_duration;
    }
}

void Spritesheet::start() 
{
    if (isPlaying) 
    {
        throw new std::runtime_error(
            "Animation already playing"
        );
    } 
    else if (hasPlayed && !shouldLoop) 
    {
        throw new std::runtime_error(
            "Animation has already played and does not loop--call reset()"
        );
    } 
    else 
    {
        isPlaying = true;
    }
}

void Spritesheet::stop()
{
    if (!isPlaying) 
    {
        throw new std::runtime_error(
            "Animation isn't playing, therefore cannot be stopped"
        );
    }
    isPlaying = false;
}

void Spritesheet::reset() 
{
    currFrameIndex = 0;
    timeOnCurrFrameMs = 0;
    hasPlayed = false;
    isPlaying = false;
}

bool Spritesheet::getIsPlaying() 
{
    return isPlaying;
}

bool Spritesheet::getHasPlayed() 
{
    return hasPlayed;
}

void Spritesheet::update(long milliseconds) 
{
    while (isPlaying && milliseconds > 0) 
    {
        long ms_left_this_frame = 
            frameDurationsMs[currFrameIndex] - timeOnCurrFrameMs;
        
        // Enough time has passed to move to the next frame
        if (milliseconds >= ms_left_this_frame) 
        {
            incrementFrame();
            milliseconds -= ms_left_this_frame;
        } 
        else 
        {  
            // Stay on current frame, but increment `timeOnCurrFrameMs`
            timeOnCurrFrameMs += milliseconds;
            milliseconds = 0;
        }
    }
}

void Spritesheet::incrementFrame() 
{
    if (!isPlaying) 
    {
        throw new std::runtime_error(
            "Animation is not playing"
        );
    }

    currFrameIndex++;
    timeOnCurrFrameMs = 0;

    // Reached end of animation
    if (currFrameIndex == numFrames) 
    {
        hasPlayed = true;

        if (shouldLoop) 
        {
            currFrameIndex = 0;
        } 
        else 
        {
            stop();
        }
    }
}

SDL_Rect Spritesheet::getCurrentFrameSrc() 
{
    if (!isPlaying) 
    {
        throw new std::runtime_error(
            "Animation is not playing"
        );
    }
    return SDL_Rect {
        frameW * currFrameIndex, 
        0, 
        frameW * (currFrameIndex + 1), 
        frameH
    };
}

TextureId Spritesheet::getTextureID() 
{
    return textureId;
}

int Spritesheet::getFrameW() 
{
    return frameW;
}

int Spritesheet::getFrameH() 
{
    return frameH;
}

// return number of frames left in animation (not total number of frameCounts!!)
int Spritesheet::getFramesLeft() 
{
    if (!isPlaying) 
    {
        throw new std::runtime_error(
            "Animation is not playing"
        );
    }

    return numFrames - currFrameIndex;
}