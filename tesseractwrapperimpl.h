#ifndef TESSERACTWRAPPERIMPL_H
#define TESSERACTWRAPPERIMPL_H
#include <tesseract/baseapi.h>
#include <memory>
static constexpr const char* DEF_PATH = "./tessdata";
#ifdef  DEBUG_LIB
#define DEBUG(str) printf("%s", str)
#else
#define DEBUG(str) ;
#endif

class TesseractWrapperImpl
{
public:
    friend class TesseractWrapper;
    TesseractWrapperImpl() noexcept;
    TesseractWrapperImpl(const TesseractWrapperImpl&) = delete;
    const TesseractWrapperImpl& operator=(const TesseractWrapperImpl&) = delete;
    ~TesseractWrapperImpl();

    void                setLanguage(const char* language){this->language = language;};
    void                setImagePath(const char* imagePath){this->image_path = imagePath;}
    void                setTESS_PREFIX(const char* prefix){tess_prefix = prefix;}
    std::string         doGetText();

    enum class _Inner_Error{
        _NO_ERROR_,
        _NO_LAN_SUPPORT,
        _PIC_PATH_INVALID
    } e {_Inner_Error::_NO_ERROR_};

private:
    bool                isTmpSetEnv = false;
    bool                isOpen      = false;
    bool                shellContinue(){return e == _Inner_Error::_NO_ERROR_;}
    void                clearImagePath(){image_path = nullptr;}
    void                clearLanguage(){language = nullptr;}
    void                real_initAPI();
    void                endAPICall();
    const char*         language;
    const char*         image_path;
    const char*         tess_prefix {DEF_PATH} ;
    std::unique_ptr<tesseract::TessBaseAPI>     apiCall;
};

#endif // TESSERACTWRAPPERIMPL_H
