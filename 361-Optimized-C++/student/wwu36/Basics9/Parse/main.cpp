//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// Add functions and includes as needed

#include "Chunk.h"
#include <iostream>
#include <cstring>
#include <string>

int ParseArguments(int argc, char* argv[], ChunkType& chunkType, std::string& chunkName)
{
    chunkType = VERTS_TYPE;
    chunkName = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-T") == 0) {
            if (i + 1 < argc) {
                std::string typeString = argv[i + 1];
                if (typeString == "VERTS_TYPE")
                    chunkType = VERTS_TYPE;
                else if (typeString == "NORMS_TYPE")
                    chunkType = NORMS_TYPE;
                else if (typeString == "ANIM_TYPE")
                    chunkType = ANIM_TYPE;
                else if (typeString == "TEXTURE_TYPE")
                    chunkType = TEXTURE_TYPE;
                else if (typeString == "UV_TYPE")
                    chunkType = UV_TYPE;
                else
                    return -1;
                i++;
            }
            else
                return -1;
        }
        else if ((strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-N") == 0) && i + 1 < argc) {
            std::string nameString = argv[i + 1];
            if (nameString.length() > 19)
                return -1;
            chunkName = nameString;
            i++;
        }
        else 
            return -1;
    }
    return 0; 
}

int main(int argc, char* argv[])
{
    ChunkType chunkType;
    std::string chunkName;

    int parseResult = ParseArguments(argc, argv, chunkType, chunkName);

    if (parseResult == 0) {
        std::cout << "Chunk type: " << chunkType << std::endl;
        std::cout << "Chunk name: " << chunkName << std::endl;
        return 0;
    }
    else {
        std::cerr << "Parsing error" << std::endl;
        return -1;
    }
}

// ---  End of File ---------------
