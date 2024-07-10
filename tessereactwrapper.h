#ifndef TESSEREACTWRAPPER_H
#define TESSEREACTWRAPPER_H
#include "TessereactWrapper_global.h"
#include <string>

class TesseractWrapperImpl;

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
                return "This Lang is not support yet!";
                break;
            case Error::PIC_PATH_NO_FOUND:
                return "Picture Path not target!";
                break;
            }
        }
    };

    TessereactWrapper();
    TessereactWrapper(const TessereactWrapper&) = delete;
    const   TessereactWrapper& operator=(const TessereactWrapper&) = delete;
    bool                    isFine(){return e.e == TessreactError::Error::NO_ERROR;}
    TessreactError::Error   error();
    void                    setLanguage(const char* language);
    void                    setTessPrifix(const char* prefix);
    void                    setViewImage(const char* image_path);
    std::string             getTextFromImage();
    ~TessereactWrapper();
private:
    void                    clearError();
    void                    transferError();
    TessreactError          e;
    TesseractWrapperImpl*   _impl;
};

#endif // TESSEREACTWRAPPER_H
