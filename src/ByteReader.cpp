#include "ByteReader.hpp"

std::string getBytesFromLogin(int connection)
{
    char buffer[64];
    for (int i = 0; i < 63; ++i)
    {
        buffer[i] = 65;
    }
    std::size_t read = 0;
    while (true)
    {
        ssize_t actual = ::read(connection, buffer + read, 4096 - read);
        if (actual == 0)
        {
            break;
        }
        if (actual == -1 && (errno == EAGAIN || errno == EINTR))
        {
            continue;
        }
        if (actual == -1)
        {
            throw std::runtime_error("Read Error");
        }
        read += actual;
        if (read == 4096)
        {
            break;
        }
        if ((read > 0) && buffer[read - 1] == '\0')
        {
            break;
        }
    }
    return buffer;
}

void forwardBytes(int from, int to)
{
    int len = 0;
    std::size_t totalRead = 0;

    while (true)
    {
        if (len > 0 && totalRead == len)
        {
            break;
        }
        std::size_t loopRead = 0;
        const int bsize = 1024;
        unsigned char buffer[bsize];
        while (true)
        {
            ssize_t actual = ::read(from, buffer + loopRead, bsize - loopRead);
            if (actual == 0)
            {
                break;
            }
            if (actual == -1 && (errno == EAGAIN || errno == EINTR))
            {
                continue;
            }
            if (actual == -1)
            {
                throw std::runtime_error("Read Error");
            }
            if (len == 0 && actual >= 8)
            {                
                len = getQueryLength(buffer);
                std::cout << "LLL: " << len << std::endl;
            }
            
            loopRead += actual;
            totalRead += actual;
            if (loopRead == bsize || totalRead == len)
            {
                break;
            }
        }
        ::write(to, buffer, loopRead);
    }
}

int getQueryLength(unsigned char *buffer)
{
    long len = 0;
    len += buffer[4];
    len += buffer[5] << 8;
    len += buffer[6] << 16;
    len += buffer[7] << 24;
    return len;
}

std::vector<char> getBytesFromQuery(int connection)
{
    char buffer[1024];
    std::size_t read = 0;
    std::size_t shouldRead = 0;
    while (true)
    {
        ssize_t actual = ::read(connection, buffer + read, 4096 - read);
        if (actual == 0)
        {
            break;
        }
        if (actual == -1 && (errno == EAGAIN || errno == EINTR))
        {
            continue;
        }
        if (actual == -1)
        {
            std::cerr << "actual -1"
                      << "ERR:" << errno << std::endl;
            throw std::runtime_error("Read Error");
        }
        read += actual;
        if (read == 4096)
        {
            break;
        }
        if ((read >= 8) && (0 == shouldRead))
        {
            for (int i = 4; i < 8; ++i)
            {
                shouldRead += buffer[i];
            }
            if (read == shouldRead)
            {
                break;
            }
            continue;
        }
        if (read == shouldRead)
        {
            break;
        }
    }
    auto result = std::vector<char>();
    for (int i = 0; i < read; ++i)
    {
        result.push_back(buffer[i]);
    }

    return result;
}
