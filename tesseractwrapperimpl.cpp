#include "tesseractwrapperimpl.h"
#include <stdlib.h>
#include <leptonica/allheaders.h>
#include <filesystem>

static bool __pvt_check_fileExsits(const char* filePath){
    return std::filesystem::exists(filePath);
}


TesseractWrapperImpl::TesseractWrapperImpl() noexcept :
    apiCall(new tesseract::TessBaseAPI)
{}

bool TesseractWrapperImpl::real_initAPI()
{
    if(!std::getenv("TESSDATA_PREFIX"))
    {
        DEBUG("Now set the envs");
        DEBUG(tess_prefix);
        _putenv_s("TESSDATA_PREFIX", tess_prefix.c_str());
        DEBUG(std::getenv("TESSDATA_PREFIX"));
        isTmpSetEnv = true;
    }

    if(apiCall->Init(nullptr, language.c_str())){
        e = _Inner_Error::_NO_LAN_SUPPORT;
        return false;
    }
    isOpen = true;
    return true;
}

const char* TesseractWrapperImpl::doGetHeapRawString()
{
    if(!__pvt_check_fileExsits(image_path.c_str())){
        e = _Inner_Error::_PIC_PATH_INVALID;
        return "";
    }

    if(!isOpen){
        if(!real_initAPI())
        {
            e = _Inner_Error::_NO_LAN_SUPPORT;
            return "";
        }
    }

    Pix*    pic = pixRead(image_path.c_str());
    apiCall->SetImage(pic);
    char* res =  apiCall->GetUTF8Text();
    pixDestroy(&pic);
    return res;
}

std::string TesseractWrapperImpl::doGetText()
{
    if(!__pvt_check_fileExsits(image_path.c_str())){
        e = _Inner_Error::_PIC_PATH_INVALID;
        return "";
    }

    if(!isOpen){
        if(!real_initAPI())
        {
            e = _Inner_Error::_NO_LAN_SUPPORT;
            return "";
        }
    }

    Pix*    pic = pixRead(image_path.c_str());
    apiCall->SetImage(pic);
    char* _heap_string = apiCall->GetUTF8Text();
    std::string heap_string{ _heap_string };
    pixDestroy(&pic);
    delete[]    _heap_string;
    return      heap_string;
}

void TesseractWrapperImpl::endAPICall()
{
    apiCall->End();
}

TesseractWrapperImpl::~TesseractWrapperImpl()
{
    if(isTmpSetEnv){
        _putenv_s("TESSDATA_PREFIX", "");
    }
}
