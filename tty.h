#pragma once
#ifndef TTY_H
#define TTY_H

#define NOMINMAX //Otherwise, the windows API will detect macros min and max 
//that conflict with std::max and std::min in vector

#include <windows.h>
#include <vector>
#include <string>

struct TTY {

    TTY();
    virtual ~TTY();

    bool IsOK() const;

    void Connect(LPCWSTR port, int baudrate);
    void Disconnect();

    virtual void Write(const std::vector<unsigned char>& data); //Send data to com-port
    virtual void Read(std::vector<unsigned char>& data); //Read received data

    HANDLE m_Handle;

};

struct TTYException {
};

#endif