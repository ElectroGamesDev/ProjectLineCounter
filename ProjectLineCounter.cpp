#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <conio.h>

int CountLines(std::filesystem::path path)
{
    std::ifstream file(path);

    if (!file.is_open()) return false;

    std::string line;
    int lineCount = 0;

    while (std::getline(file, line))
        lineCount++;

    file.close();
    return lineCount;
}

int main()
{
    std::cout << "Drag and drop a folder to count the total number of lines your project has..." << std::endl;

    std::vector< std::string > files;

    for (int ch = _getch(); ch != '\r'; ch = _getch()) {

        std::string file_name;

        if (ch == '\"')
        {
            while ((ch = _getch()) != '\"')
                file_name += ch;
        }
        else
        {
            file_name += ch;
            while (_kbhit())
                file_name += _getch();
        }

        files.push_back(file_name);
        break;
    }

    int lines = 0;

    for (auto& file : files)
    {
        if (std::filesystem::is_directory(file))
        {
            for (const auto& fileFound : std::filesystem::recursive_directory_iterator(file))
                lines += CountLines(fileFound);
        }
        else
            lines += CountLines(file);
    }

    std::cout << "\nYour project has " << lines << " lines." << std::endl;

    std::cout << "\nPress [Enter] To Close" << std::endl;
    std::cin.ignore();
    return 0;
}