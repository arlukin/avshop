#include <cstdlib>
#include <iostream>

#include "boost/filesystem.hpp"

#include "Image.h"

namespace av {


Image::Image()
    : _wwwRoot(""), _urlPath(""), _fileName(""), _thumbSize(204,204)
{
}

Image::Image(const std::string& wwwRoot_, const std::string& urlPath_, const std::string& fileName_)
    : _wwwRoot(wwwRoot_), _urlPath(urlPath_), _fileName(fileName_), _thumbSize(204,204)
{
    _generateThumb();
}

Image::Image(const Image& image_)
    : _thumbSize(image_._thumbSize)
{
    _wwwRoot = image_._wwwRoot;
     _urlPath = image_._urlPath;
     _fileName = image_._fileName;
}

std::string Image::getFullUrl() const throw(ImageError)
{
    return std::string(std::string(_urlPath + _fileName));
}

std::string Image::getThumbUrl()  const throw(ImageError)
{
    boost::filesystem::path name(std::string(std::string(_urlPath + "thumb/" + _fileName)));
    name.replace_extension(".jpg");
    return name.string();
}

std::string Image::_getFullPath() const throw(ImageError)
{
    return _getCurrentDirectory() + _wwwRoot + getFullUrl();
}

std::string Image::_getThumbPath() const throw(ImageError)
{
    return std::string(_getCurrentDirectory() +_wwwRoot + getThumbUrl());
}

void Image::_generateThumb() const throw(ImageError)
{
    if (!_hasThumb() && _hasShell())
    {        
        if (!boost::filesystem::exists(_getFullPath()))
            throw ImageError("Original file doesn't exist: " + _getFullPath());

        // Create thumb path if not existing.
        if (!boost::filesystem::exists(_getThumbPath()))
        {
            boost::filesystem::create_directories(_getThumbPath());

            if (!boost::filesystem::exists(_getThumbPath()))
                throw ImageError("Thumb path cant be created: " + _getThumbPath());
        }

        std::string command("convert");
        command += " -resize " + _thumbSize.getSize();
        command += " -gravity Center -extent 204x204^";
        command += " " + _getFullPath();
        command += " " + _getThumbPath();
        system(command.c_str());

        std::cout << "executed: " << command.c_str() << std::endl;
    }
}

std::string Image::_getCurrentDirectory() const throw(ImageError)
{
    static std::string dir = "" ;
    if (dir.empty())
    {
        dir = boost::filesystem::current_path().string() + "/";
    }

    return dir;
}

bool Image::_hasThumb() const throw(ImageError)
{
    return (boost::filesystem::exists(_getThumbPath()));
}

bool Image::_hasShell() const throw(ImageError)
{
    if (!system(NULL))
        throw ImageError("No shell available.");
    
    return true;
}

}
