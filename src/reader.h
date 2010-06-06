//////////////////////////////////////////////////////////////////////////////////
/// This file is part of EasyRPG Player.
/// 
/// EasyRPG Player is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// 
/// EasyRPG Player is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
/// 
/// You should have received a copy of the GNU General Public License
/// along with EasyRPG Player.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////////////

#ifndef _READER_H_
#define _READER_H_

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <iostream>
#include <string.h>
#include <stdio.h>

////////////////////////////////////////////////////////////
/// Reader namespace
////////////////////////////////////////////////////////////
namespace Reader {
    struct Chunk {
        unsigned long ID;
        unsigned long length;
    };
    unsigned long CInteger(FILE* stream);
    short Short(FILE* stream);
    long Uint32(FILE* stream);
    bool Flag(FILE* stream);
    unsigned char BitFlag(FILE* stream);
    std::string String(FILE* stream, int lenght);
    std::vector<short> ArrayShort(FILE* stream, int lenght);
    std::vector<unsigned char> ArrayUint8(FILE* stream, int lenght);
    std::vector<unsigned long> ArrayUint32(FILE* stream, int lenght);
    std::vector<bool> ArrayFlag(FILE* stream, int lenght);
};

#endif
