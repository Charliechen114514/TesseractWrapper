#ifndef TESSEREACTWRAPPER_H
#define TESSEREACTWRAPPER_H
#include "TessereactWrapper_global.h"
#include <string>

class TesseractWrapperImpl;

extern "C" {
    using CREATE_PTR = void*(*)();
    using SET_PTR = void*(*)(void*, const char*);
    using GET_PTR = const char*(*)(void*);
    using ERASE_PTR = void(*)(void*);
    __declspec(dllexport) void*         TesseractWrapper_create();
    __declspec(dllexport) void          TesseractWrapper_setLanguage(void* TesseractHandle, const char* language);
    __declspec(dllexport) void          TesseractWrapper_setTessPrifix(void* TesseractHandle, const char* prefix);
    __declspec(dllexport) void          TesseractWrapper_setViewImage(void* TesseractHandle, const char* image_path);
    __declspec(dllexport) const char*   TesseractWrapper_getTextFromImage(void* TesseractHandle);
    __declspec(dllexport) void          TesseractWrapper_Erase(void* handle);
    __declspec(dllexport) const char*   TesseractWrapper_ErrorString(void* handle);
}

extern "C"
{
    class TESSEREACTWRAPPER_EXPORT TessereactWrapper
    {
    public:
        struct TessreactError
        {
            enum class Error{
                NO_ERROR,
                NO_LANG_SUPPORT,
                PIC_PATH_NO_FOUND
            }e;
            const char* errorString(){
                switch(e){
                case Error::NO_ERROR:
                    return "";
                case Error::NO_LANG_SUPPORT:
                    return "请检查自己的tessetact数据集位置！请放到DLL以来目录下的share/目录下";
                    break;
                case Error::PIC_PATH_NO_FOUND:
                    return "目标图像无法识别，因为没有找到路径";
                    break;
                }
            }
        };

        TessereactWrapper();
        TessereactWrapper(const TessereactWrapper&) = delete;
        const   TessereactWrapper& operator=(const TessereactWrapper&) = delete;
        bool                    isFine(){return e.e == TessreactError::Error::NO_ERROR;}
        TessreactError::Error   error();
        const char*             errorString();
        void                    setLanguage(const char* language);
        void                    setTessPrifix(const char* prefix);
        void                    setViewImage(const char* image_path);
        const char*             getHeapRawString();
        std::string             getTextFromImage();
        ~TessereactWrapper();
    private:
        void                    clearError();
        void                    transferError();
        TessreactError          e;
        TesseractWrapperImpl*   _impl;
    };
}

#endif // TESSEREACTWRAPPER_H
