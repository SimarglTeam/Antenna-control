#include "tty.h"
#include <iostream>
#include <assert.h>

static int TIMEOUT = 1000;

TTY::TTY() {
    m_Handle = INVALID_HANDLE_VALUE;
}

TTY::~TTY() {
    Disconnect();
}

bool TTY::IsOK() const {
    return m_Handle != INVALID_HANDLE_VALUE;
}

void TTY::Connect(LPCWSTR port, int baudrate) {

    m_Handle =
        CreateFile( //Создание файла для работы с COM-портом
            port, //Указатель на строку с именем открываемого или создаваемого файла
            GENERIC_READ | GENERIC_WRITE, //Тип доступа к файлу: и для записи и для чтения
            0, //Параметр совместного доступа к файлу (Всегда 0, т.к. наш порт таким сделать нельзя)
            NULL, //Атрибут защиты файла, но для использования нужен Windows NT, потому NULL
            OPEN_EXISTING, //Управление режимами автосоздания, автоусечения файла и тп. Всегда равен OPEN_EXISTING
            FILE_ATTRIBUTE_NORMAL, //Данный атрибут используется для асинхронной работы или при фоновой обработке ввода/вывода
            NULL); //При работе с портами всегда NULL. А так задает описатель-шаблона

    if (m_Handle == INVALID_HANDLE_VALUE) {
        throw TTYException();
    }

    SetCommMask(m_Handle, EV_RXCHAR);
    SetupComm(m_Handle, 1500, 1500);

    COMMTIMEOUTS CommTimeOuts;
    CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
    CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
    CommTimeOuts.ReadTotalTimeoutConstant = TIMEOUT;
    CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
    CommTimeOuts.WriteTotalTimeoutConstant = TIMEOUT;

    if (!SetCommTimeouts(m_Handle, &CommTimeOuts)) {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
        throw TTYException();
    }

    DCB ComDCM;

    memset(&ComDCM, 0, sizeof(ComDCM));
    ComDCM.DCBlength = sizeof(DCB);
    GetCommState(m_Handle, &ComDCM);
    ComDCM.BaudRate = DWORD(baudrate);
    ComDCM.ByteSize = 8;
    ComDCM.Parity = NOPARITY;
    ComDCM.StopBits = ONESTOPBIT;
    ComDCM.fAbortOnError = TRUE;
    ComDCM.fDtrControl = DTR_CONTROL_DISABLE;
    ComDCM.fRtsControl = RTS_CONTROL_DISABLE;
    ComDCM.fBinary = TRUE;
    ComDCM.fParity = FALSE;
    ComDCM.fInX = FALSE;
    ComDCM.fOutX = FALSE;
    ComDCM.XonChar = 0;
    ComDCM.XoffChar = (unsigned char)0xFF;
    ComDCM.fErrorChar = FALSE;
    ComDCM.fNull = FALSE;
    ComDCM.fOutxCtsFlow = FALSE;
    ComDCM.fOutxDsrFlow = FALSE;
    ComDCM.XonLim = 128;
    ComDCM.XoffLim = 128;

    if (!SetCommState(m_Handle, &ComDCM)) {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
        throw TTYException();
    }
    std::cout << "Connect successfull" << std::endl;
}

void TTY::Disconnect() {

    if (m_Handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
    }
    std::cout << "Disconnect successfull" << std::endl;
}

void TTY::Write(const std::vector<unsigned char>& data) {

    if (m_Handle == INVALID_HANDLE_VALUE) {
        throw TTYException();
    }

    DWORD feedback = 0;
    if (!WriteFile(m_Handle, &data[0], (DWORD)data.size(), &feedback, 0) || feedback != (DWORD)data.size()) {
        CloseHandle(m_Handle);
        m_Handle = INVALID_HANDLE_VALUE;
        throw TTYException();
    }
}

void TTY::Read(std::vector<unsigned char>& data) {

    if (m_Handle == INVALID_HANDLE_VALUE) {
        throw TTYException();
    }

    DWORD begin = GetTickCount64();
    DWORD feedback = 0;

    unsigned char* buf = &data[0];
    DWORD len = 16;

    int attempts = 3;
    while (len && (attempts || (GetTickCount64() - begin) < (DWORD)TIMEOUT / 3)) {

        if (attempts) attempts--;

        if (!ReadFile(m_Handle, buf, len, &feedback, NULL)) {
            CloseHandle(m_Handle);
            m_Handle = INVALID_HANDLE_VALUE;
            throw TTYException();
        }

        assert(feedback <= len);
        len -= feedback;
        buf += feedback;

    }

    if (len) {
       CloseHandle(m_Handle);
       m_Handle = INVALID_HANDLE_VALUE;
       throw TTYException();
    }

}
