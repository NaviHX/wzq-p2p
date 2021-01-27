#include "game.h"
#include <iostream>
#include <cstdio>
#include <string>

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        std::cout << "var needed\n\"--help\" for help\n";
    }
    else
    {
        std::string ip = "";
        for (int i = 1; i < argc; i++)
        {
            std::string arg(argv[i]);
            if (arg[0] == '-')
            {
                if (arg == "--help")
                {
                    std::cout << "Usage              : wzq-p2p [options] ip" << std::endl
                              << "-c, --connect <ip> : connect a game" << std::endl
                              << "-h, --host         : host a game" << std::endl
                              << "    --help         : help information" << std::endl;
                }
                else if (arg == "-c" || arg == "--connect")
                {
                    if (i + 1 >= argc)
                    {
                        std::cout << "IP Needed\n";
                        return 0;
                    }
                    else
                        ip = std::string(argv[++i]);
                    connectGame(ip.c_str());
                }
                else if (arg == "-h" || arg == "--host")
                {
                    hostGame();
                }
            }
        }
    }
    return 0;
}
