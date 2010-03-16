#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <stdexcept>

#include "AVString.h"

namespace av {

class ImageError : public std::runtime_error
{
public:
    ImageError( std::string errorText_) : std::runtime_error( errorText_ )
    {
    }
};

class Image
{
    struct Size
    {
    public:
        Size(const int width_, const int height_) : width(width_), height(height_) {};
        std::string getSize() const  { return av::itos(width) + "x" + av::itos(height) ;};
    private:
        int width;
        int height;
    };

public:
    Image();
    Image(const std::string& wwwRoot_, const std::string& urlPath_, const std::string& fileName_);
    Image(const Image& image_);

    std::string getFullUrl() const throw(ImageError);
    std::string getThumbUrl()  const throw(ImageError);

private:
    std::string _wwwRoot;
    std::string _urlPath;
    std::string _fileName;
    Size _thumbSize;

    std::string _getFullPath() const throw(ImageError);
    std::string _getThumbPath() const throw(ImageError);
    void _generateThumb() const throw(ImageError);
    std::string _getCurrentDirectory() const throw(ImageError);
    bool _hasThumb() const throw(ImageError);
    bool _hasShell() const throw(ImageError);
};

}
#endif // IMAGE_H
