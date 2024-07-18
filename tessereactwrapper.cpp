#include "tessereactwrapper.h"
#include "tesseractwrapperimpl.h"


TessereactWrapper::TessereactWrapper()
{
    _impl = new TesseractWrapperImpl;
}

void TessereactWrapper::setLanguage(const char* language)
{
    _impl->setLanguage(language);
}

void TessereactWrapper::setTessPrifix(const char* prefix)
{
    _impl->setTESS_PREFIX(prefix);
}

void TessereactWrapper::setViewImage(const char* image_path)
{
    _impl->setImagePath(image_path);
}

TessereactWrapper::TessreactError::Error TessereactWrapper::error()
{
    clearError();
    return e.e;
}

const char* TessereactWrapper::errorString(){
    transferError();
    return e.errorString();
}


void TessereactWrapper::clearError()
{
    e.e = TessreactError::Error::NO_ERROR;
    _impl->e = TesseractWrapperImpl::_Inner_Error::_NO_ERROR_;
}

void TessereactWrapper::transferError()
{
    switch(_impl->e)
    {
    case TesseractWrapperImpl::_Inner_Error::_NO_ERROR_:
        e.e = TessreactError::Error::NO_ERROR;break;
    case TesseractWrapperImpl::_Inner_Error::_NO_LAN_SUPPORT:
        e.e = TessreactError::Error::NO_LANG_SUPPORT;break;
    case TesseractWrapperImpl::_Inner_Error::_PIC_PATH_INVALID:
        e.e = TessreactError::Error::PIC_PATH_NO_FOUND;
        break;
    }
}

const char* TessereactWrapper::getHeapRawString()
{
    transferError();
    if(!isFine()){
        return "";
    }
    return _impl->doGetHeapRawString();
}

std::string TessereactWrapper::getTextFromImage()
{
    transferError();
    if(!isFine()){
        return "";
    }
    return _impl->doGetText();
}

TessereactWrapper::~TessereactWrapper()
{
    delete _impl;
}
