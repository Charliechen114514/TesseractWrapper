#include "tessereactwrapper.h"

void* TesseractWrapper_create()
{
    return new TessereactWrapper;
}

void TesseractWrapper_setLanguage(void* TesseractHandle, const char* language)
{
    TessereactWrapper* wrapper = static_cast<TessereactWrapper*>(TesseractHandle);
    wrapper->setLanguage(language);
}

void TesseractWrapper_setTessPrifix(void* TesseractHandle, const char* prefix)
{
    TessereactWrapper* wrapper = static_cast<TessereactWrapper*>(TesseractHandle);
    wrapper->setTessPrifix(prefix);
}

void TesseractWrapper_setViewImage(void* TesseractHandle, const char* image_path)
{
    TessereactWrapper* wrapper = static_cast<TessereactWrapper*>(TesseractHandle);
    wrapper->setViewImage(image_path);
}

const char* TesseractWrapper_getTextFromImage(void* TesseractHandle)
{
    TessereactWrapper* wrapper = static_cast<TessereactWrapper*>(TesseractHandle);
    return wrapper->getHeapRawString();
}

const char* TesseractWrapper_ErrorString(void* TesseractHandle)
{
    TessereactWrapper* wrapper = static_cast<TessereactWrapper*>(TesseractHandle);
    return wrapper->errorString();
}

void TesseractWrapper_Erase(void* handle)
{
    TessereactWrapper* wrapper = static_cast<TessereactWrapper*>(handle);
    delete wrapper;
}
