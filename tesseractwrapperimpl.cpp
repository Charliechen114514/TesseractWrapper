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

void TesseractWrapperImpl::real_initAPI()
{
    if(!std::getenv("TESSDATA_PREFIX"))
    {
        DEBUG("Now set the envs");
        DEBUG(tess_prefix);
        _putenv_s("TESSDATA_PREFIX", tess_prefix);
        DEBUG(std::getenv("TESSDATA_PREFIX"));
        isTmpSetEnv = true;
    }

    if(apiCall->Init(nullptr, language)){
        e = _Inner_Error::_NO_LAN_SUPPORT;
        return;
    }
    isOpen = true;
}

std::string TesseractWrapperImpl::doGetText()
{
    if(!__pvt_check_fileExsits(image_path)){
        e = _Inner_Error::_PIC_PATH_INVALID;
        return "";
    }

    if(!isOpen){
        real_initAPI();
    }

    Pix*    pic = pixRead(image_path);
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
