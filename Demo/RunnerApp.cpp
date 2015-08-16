#include "RunnerApp.h"
#include "Quad.h"
#include "Program.h"
#include "RunnerShaders.h"
//#include "common.h"
#include <iostream>

// required fo libpng usage
#include <libpng/png.h>
#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#define png_voidp_NULL NULL

using namespace Runner;

RunnerApp::RunnerApp() :
	m_quad(NULL)
{

}

RunnerApp::~RunnerApp()
{

}

void RunnerApp::Create(const int& uiWidth, const int& uiHeight)
{
	AppNativeWindow::Create(uiWidth, uiHeight);

	m_quad = new Runner::Quad();
	m_program = new Runner::Program();
	m_program->Init(runnerVertShader, runnerFragShader);
}

void RunnerApp::Destroy()
{
	AppNativeWindow::Destroy();

	SAFE_DELETE_PTR(m_quad);
	SAFE_DELETE_PTR(m_program);
}

void RunnerApp::t_OnInit()
{
	m_programID = m_program->GetProgramID();
}

void RunnerApp::t_OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 0.0);

	glUseProgram(m_programID);

	// load texture
	GLuint samplerLoc;
	samplerLoc = glGetUniformLocation(m_programID, "tex");
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(samplerLoc, 0);
	m_loadImage("..\\..\\..\\resources\\quack.png");
	//m_loadImage("D:\\projects\\Runner\\resources\\apple.png");
	// load vertices
	unsigned int offset = 0;
	m_BindVBO(m_quad->vboID);
	unsigned int vertexLoc = -1;
	vertexLoc  = glGetAttribLocation(m_programID, "a_vertex");
	glEnableVertexAttribArray(vertexLoc);
	glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, false, m_quad->stride, (void*) offset);
	offset += 3 * sizeof(float);

	// load texture coordinates
	unsigned int texCoordsLoc = -1;
	texCoordsLoc  = glGetAttribLocation(m_programID, "a_texture");
	if (texCoordsLoc != -1)
	{
		glEnableVertexAttribArray(texCoordsLoc );
		glVertexAttribPointer(texCoordsLoc, 2, GL_FLOAT, false, m_quad->stride, (void*) offset);
	}
	offset += 2 * sizeof(float);

	unsigned short indicies[4] = {0, 1, 2, 3};
	glDrawElements(GL_TRIANGLE_STRIP, m_quad->vertCount, GL_UNSIGNED_SHORT, indicies);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(vertexLoc);
	//glDeleteTextures(1, &m_quad->textureID);

	glUseProgram(0);
}

void RunnerApp::m_loadImage(const char* imagePath)
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (m_quad->textureID == -1)
	{
		glGenTextures(1, &m_quad->textureID);
		glBindTexture(GL_TEXTURE_2D, m_quad->textureID);

		int width = -1, height  = -1;
		bool hasAlpha = false;

		GLubyte* buffer = NULL;
		bool isImageLoaded = loadPngImage(imagePath, width, height, hasAlpha, &buffer);
		if (isImageLoaded)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
				height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, buffer);
		}
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_quad->textureID);
	}
}

void RunnerApp::m_BindVBO(int& vboID)
{
	if (vboID == -1)
	{
		unsigned int _vboID = 0;
		glGenBuffers(1, &_vboID);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, (3 + 2) * m_quad->vertCount * sizeof(float), m_quad->vert, GL_STATIC_DRAW);
		vboID = (int)_vboID;
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
	}
}

bool RunnerApp::loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) 
{
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    FILE *fp;
 
    if ((fp = fopen(name, "rb")) == NULL)
        return false;
 
    /* Create and initialize the png_struct with the desired error handler
     * functions.  If you want to use the default stderr and longjump method,
     * you can supply NULL for the last three parameters.  We also supply the
     * the compiler header file version, so that we know if the application
     * was compiled with a compatible version of the library.  REQUIRED
     */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
            NULL, NULL, NULL);
 
    if (png_ptr == NULL) {
        fclose(fp);
        return false;
    }
 
    // Allocate/initialize the memory for image information.  REQUIRED.
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        fclose(fp);
        png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
        return false;
    }
 
    /* Set error handling if you are using the setjmp/longjmp method
     * (this is the normal method of doing things with libpng).
     * REQUIRED unless you  set up your own error handlers in
     * the png_create_read_struct() earlier.
     */
    if (setjmp(png_jmpbuf(png_ptr))) {
        /* Free all of the memory associated with the png_ptr and info_ptr */
        png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
        fclose(fp);
        /* If we get here, we had a problem reading the file */
        return false;
    }
 
    /* Set up the output control if you are using standard C streams */
    png_init_io(png_ptr, fp);
 
    /* If we have already read some of the signature */
    png_set_sig_bytes(png_ptr, sig_read);
 
    /*
     * If you have enough memory to read in the entire image at once, and
     * you need to specify only transforms that can be controlled
     * with one of the PNG_TRANSFORM_* bits (this presently excludes
     * dithering, filling, setting background, and doing gamma
     * adjustment), then you can read the entire image (including pixels)
     * into the info structure with this call
     *
     * PNG_TRANSFORM_STRIP_16 |
     * PNG_TRANSFORM_PACKING  forces 8 bit
     * PNG_TRANSFORM_EXPAND forces to
     *  expand a palette into RGB
     */
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);
 
    outWidth = png_get_image_width(png_ptr,info_ptr); // ширина изображение
    outHeight = png_get_image_height(png_ptr,info_ptr); // высота изображения
 
   // проверка на наличие альфа-канала
    switch (png_get_color_type(png_ptr,info_ptr)) {
        case PNG_COLOR_TYPE_RGBA:
            outHasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
            outHasAlpha = false;
            break;
        default:
            std::cout << "Color type " << png_get_color_type(png_ptr,info_ptr) << " not supported" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
            fclose(fp);
            return false;
    }
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    *outData = (unsigned char*) malloc(row_bytes * outHeight);
 
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
 
    for (int i = 0; i < outHeight; i++) {
        // note that png is ordered top to bottom, but OpenGL expect it bottom to top
        // so the order or swapped
        memcpy(*outData+(row_bytes * (outHeight-1-i)), row_pointers[i], row_bytes);
    }
 
    /* Clean up after the read, and free any memory allocated */
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
 
    /* Close the file */
    fclose(fp);
 
    return true;
}
