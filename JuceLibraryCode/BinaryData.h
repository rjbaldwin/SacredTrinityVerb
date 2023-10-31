/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   guiBack1_jpg;
    const int            guiBack1_jpgSize = 160421;

    extern const char*   tempBack2_jpg;
    const int            tempBack2_jpgSize = 161837;

    extern const char*   tempBack3_jpg;
    const int            tempBack3_jpgSize = 160374;

    extern const char*   balcony_3m_wav;
    const int            balcony_3m_wavSize = 1434994;

    extern const char*   balcony_6m_wav;
    const int            balcony_6m_wavSize = 1472590;

    extern const char*   main_hall_2m_wav;
    const int            main_hall_2m_wavSize = 1718146;

    extern const char*   main_hall_4m_wav;
    const int            main_hall_4m_wavSize = 1806550;

    extern const char*   main_hall_5m_wav;
    const int            main_hall_5m_wavSize = 2085796;

    extern const char*   main_hall_9m_wav;
    const int            main_hall_9m_wavSize = 1361692;

    extern const char*   small_room_2m_wav;
    const int            small_room_2m_wavSize = 1304854;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
