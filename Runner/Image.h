#ifndef IMAGE_H__
#define IMAGE_H__

namespace Runner
{
	class Image
	{
	public:
		Image() {}
		~Image() {}

		bool Load(char* pathToFile);
		void GetImageBuffer(unsigned char** outData);
		int Width() const;
		int Height() const;
		bool HasAlpha() const;
	private:
		bool loadPngImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, unsigned char** outData);
	private:
		int m_width;
		int m_height;
		bool m_hasAlpha;
		unsigned char** m_buffer;
	};
}

#endif /*IMAGE_H__*/