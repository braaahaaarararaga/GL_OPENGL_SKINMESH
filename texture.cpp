#include "main.h"
#include "texture.h"


unsigned int LoadTexture(const char * FileName)
{
	unsigned int texture;
	unsigned char header[18];
	unsigned char* image;
	FILE* file;
	unsigned int width, height;
	file = fopen(FileName, "rb");

	fread(header, 1, sizeof(header), file);  
	width = header[13] * 256 + header[12];   // �o�C�g�I�[�_�[�A �G���f�B�A��
	height = header[15] * 256 + header[14];

	image = new unsigned char[width * height * 4];

	// TGA file format
	// ___________________
	// | header(18byte)  | (width, height data)
	// -------------------
	// | body(color data)|
	// -------------------

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			image[(y * width + x) * 4 + 2] = fgetc(file);  // fgetc 1byte get

			image[(y * width + x) * 4 + 1] = fgetc(file);
			image[(y * width + x) * 4 + 0] = fgetc(file);
			image[(y * width + x) * 4 + 3] = fgetc(file);
		}
	}
	fclose(file);
	// TGA data            |B|G|R|A|B|G|R|A|    
	// opengl texture data |R|G|B|A|R|G|B|A|

	glGenTextures(1, &texture); // �e�N�X�`������
	glBindTexture(GL_TEXTURE_2D, texture); // �e�N�X�`���ݒ�
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image); // �e�N�X�`���ɐF�ݒ�
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] image;
	return texture;
}
