#include "AffinePlane.h"
#include "../camera/Camera.h"
#include "../input/Input.h"
#include <iostream>
#include <cmath>


AffinePlane::AffinePlane(std::string id, int samp_size, int x, int y, int w, int h, float scl) {
	
	textureID = id;

    scale = scl;

    sample_size = samp_size;

	xPos = x;
	
	yPos = y;

    width = w;

    height = h;

    og_texture_width = TextureManager::getInstance()->getWidth(textureID);
    og_texture_height = TextureManager::getInstance()->getHeight(textureID);

    amplitude = 20.0;
    freq = 0.05;
    speed = 0.2;
    time = 0.0;

    SDL_Texture* og_texture = TextureManager::getInstance()->getTexture(textureID);

    if (SDL_LockTexture(og_texture, NULL, &pixels, &pitch) != 0) {

        std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;

        return;
    }

    SDL_UnlockTexture(og_texture);

    new_texture = SDL_CreateTexture(Engine::getInstance()->getRenderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, Engine::getInstance()->getWidth(), Engine::getInstance()->getHeight());

    //original_pixels = new Uint32[optimized->w * optimized->h];
	//SDL_memcpy(original_pixels, optimized->pixels, optimized->w * optimized->h * sizeof(Uint32));
}

AffinePlane::AffinePlane() {
	
	
}

AffinePlane::~AffinePlane() {
	
	SDL_DestroyTexture(new_texture);

    std::cout << "New Affine Texture Destroyed!" << std::endl;
}

void AffinePlane::draw() {

	//TextureManager::getInstance()->draw(textureID, xPos, yPos, SDL_FLIP_NONE, scale);

	SDL_Rect dstRect = {xPos, yPos, 384, height};

    SDL_RenderCopy(Engine::getInstance()->getRenderer(), new_texture, NULL, &dstRect);
}

void AffinePlane::applySineWave(Uint32* og_pixels, Uint32* txt_pixels, int width, int height, double time) {

    SDL_memset4(txt_pixels, 0, width * height);

    for (int y = 0; y < height; y++) {

        for (int x = 0; x < width; x++) {

            int newX = x;

            int newY = y + static_cast<int>(amplitude * sin(freq * x + time));

            if (newY >= 0 && newY < height) {

                txt_pixels[newY * width + newX] = og_pixels[y * width + x];
            }
        }
    }
}

void AffinePlane::applyModeSeven(Uint32* og_pixels, Uint32* txt_pixels) {

    SDL_memset4(txt_pixels, 0, Engine::getInstance()->getWidth() * Engine::getInstance()->getHeight());

    float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
    float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

    float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
    float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

    float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
    float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

    float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
    float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;


    for (int y = 0; y < Engine::getInstance()->getHeight(); y++) {

        float fSampleDepth = (float)y / ((float)Engine::getInstance()->getHeight() / 2.0f);

        float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
        float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;

        float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
        float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;


        for (int x = 0; x < Engine::getInstance()->getWidth(); x++) {

            float fSampleWidth = (float)x / (float)Engine::getInstance()->getWidth();

            float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
            float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;

            fSampleX = fmod(fSampleX, 1.0f);
            fSampleY = fmod(fSampleY, 1.0f);

            //make sure values are original texture's width and height
            int sampleX = (int)(fSampleX * og_texture_width);
            int sampleY = (int)(fSampleY * og_texture_height);

            txt_pixels[y * 384 + x] = og_pixels[sampleY * sample_size + sampleX];
        }
    }
}

void AffinePlane::update(float dT) {

    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_UP)) {

    //     fWorldX += cosf(fWorldA) * 0.001f;
    //     fWorldY += sinf(fWorldA) * 0.001f;
    // }

    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_DOWN)) {

    //     fWorldX -= cosf(fWorldA) * 0.001f;
    //     fWorldY -= sinf(fWorldA) * 0.001f;
    // }

    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_LEFT)) {

    //     fWorldA -= 0.01f;
    // }

    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_RIGHT)) {

    //     fWorldA += 0.01f;
    // }

    // //ascend
    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_W)) {

    //     fFar += 0.01f;
    // }

    // //descend
    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_S)) {

    //     fFar -= 0.01f;
    // }

    // //FOV
    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_K)) {

    //     fFoVHalf += 0.01f;
    // }

    // if (Input::getInstance()->getKeyDown(SDL_SCANCODE_L)) {

    //     fFoVHalf -= 0.01f;
    // }

    //fWorldA += 0.0015f;
    //fWorldX += cosf(fWorldA) * 0.005f;
    //fWorldY += sinf(fWorldA) * 0.005f;

    //strafe left or right
    //fWorldY += 0.005f;

    //rotate "yaw" left or right
    fWorldX += 0.002f;

    void* new_pixels;
    int new_pitch;

    if (SDL_LockTexture(new_texture, NULL, &new_pixels, &new_pitch) != 0) {

        std::cerr << "Failed to lock texture: " << SDL_GetError() << std::endl;

        return;
    }

    Uint32* converted_og_pixels = static_cast<Uint32*>(pixels);
    Uint32* converted_new_pixels = static_cast<Uint32*>(new_pixels);

    //applySineWave(converted_og_pixels, converted_new_pixels, 1024, 1024, time);
    applyModeSeven(converted_og_pixels, converted_new_pixels);
    time += speed;

    SDL_UnlockTexture(new_texture);
}

void AffinePlane::setAlpha(int alpha) {

	TextureManager::getInstance()->setAlpha(textureID, alpha);
}