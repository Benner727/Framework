#include "Sprite.h"

Sprite::Sprite(const std::string& filename)
	: mGraphics(Graphics::Instance())
{
	mTexture = AssetManager::Instance().GetTexture(filename);
	SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mFlip = SDL_FLIP_NONE;
	mColor = { 255, 255, 255 };

	mFlash = false;
	mFlashColor = { 0, 0, 0 };
	mFlashFrames = 0;
}

Sprite::Sprite(const std::string& filename, int x, int y, int w, int h)
	: mGraphics(Graphics::Instance())
{
	mTexture = AssetManager::Instance().GetTexture(filename);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;

	mFlip = SDL_FLIP_NONE;
	mColor = { 255, 255, 255 };

	mFlash = false;
	mFlashColor = { 0, 0, 0 };
	mFlashFrames = 0;
}

Sprite::Sprite(const char& c, const std::string& fontpath, int size, SDL_Color color)
	: mGraphics(Graphics::Instance())
{
	mTexture = AssetManager::Instance().GetText(std::string(1, c), fontpath, size, { 255, 255, 255 });
	SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mFlip = SDL_FLIP_NONE;
	mColor = color;

	mFlash = false;
	mFlashColor = { 0, 0, 0 };
	mFlashFrames = 0;
}

Sprite::~Sprite()
{
}

const Vector2& Sprite::ScaledDimensions()
{
	Vector2 scaledDimensions = Scale();
	scaledDimensions.x *= mWidth;
	scaledDimensions.y *= mHeight;

	return scaledDimensions;
}

void Sprite::Flip(SDL_RendererFlip flip)
{
	mFlip = flip;
}

void Sprite::Color(SDL_Color color)
{
	mColor = color;
}

void Sprite::FlashColor(SDL_Color color)
{
	mFlashColor = color;
}

void Sprite::Flash()
{
	mFlash = true;
}

void Sprite::Render()
{
	Vector2 pos = Pos(world);
	Vector2 scale = Scale(world);

	mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);

	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	if (mFlash && mFlashFrames >= 0)
	{
		SDL_SetTextureColorMod(mTexture.get(), mFlashColor.r, mFlashColor.g, mFlashColor.b);
		mFlashFrames++;
	}
	else
	{
		SDL_SetTextureColorMod(mTexture.get(), mColor.r, mColor.g, mColor.b);
		if (mFlashFrames < 0) mFlashFrames++;
	}
	
	mGraphics.DrawTexture(mTexture, (mClipped) ? &mClipRect : nullptr, &mRenderRect, Rotation(world), mFlip);
	
	if (mFlash && mFlashFrames >= FLASH_FRAMES)
	{
		mFlash = false;
		mFlashFrames = -FLASH_FRAMES * 2.5f;
	}

	SDL_SetTextureColorMod(mTexture.get(), 255, 255, 255);
}