#pragma once
#ifndef TTY_H
#define TTY_H

#define NOMINMAX 

#include <windows.h>
#include <vector>
#include <string>

struct TTY {

    TTY();
    virtual ~TTY();

    bool IsOK() const;

    void Connect(LPCWSTR port, int baudrate);
    void Disconnect();

    virtual void Write(const std::vector<unsigned char>& data); 
    virtual void Read(std::vector<unsigned char>& data); 

    HANDLE m_Handle;
};

struct TTYException {
};

#endif