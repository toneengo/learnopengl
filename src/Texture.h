#ifndef TEXTURE_H
#define TEXTURE_H
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
    // the program ID
    unsigned int ID[15];
    unsigned int index;
    
    Texture()
    {
        index = 0;
    }
    // use/activate the shader
    void addTex(const char * texturePath, bool alpha)
    {
        GLint iformat;
        GLint iformat2;
        if (alpha)
        {
            iformat = GL_RGBA;
            iformat2 = GL_RGBA8;
        } else
        {
            iformat = GL_RGB;
            iformat2 = GL_RGB8;
        }
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
        glCreateTextures(GL_TEXTURE_2D, 1, &ID[index]);
        glTextureParameteri(ID[index], GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTextureParameteri(ID[index], GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(ID[index], GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(ID[index], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (data)
        {      
            glTextureStorage2D(ID[index], 1, iformat2, width, height);
            glTextureSubImage2D(ID[index], 0, 0, 0, width, height, iformat, GL_UNSIGNED_BYTE, data);
        } else
        {
            std::cout << "You failed cunt" << std::endl;
        }
        stbi_image_free(data);
        index++;
    }

    void actTex(unsigned int texid)
    {
        glBindTextureUnit(texid, ID[texid]);
    }
};
  
#endif
