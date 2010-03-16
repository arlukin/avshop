#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED

#include <string>
using std::string;

#include "Image.h"

#include "general/DBTable.h"
#include "Contact.h"
#include "ProductType.h"
#include "Money.h"

class Product : public DBTable
{
public:

    Product();
    Product(const Product * product_);
    Product
    (
        const string& name_,
        const string& description_,
        const Contact& manufacturer_,
        const Contact& supplier_,
        const string& externPartNo_,
        const string& internPartNo_,
        const int& minOrder_,
        const int& deliveryTime_,
        const ProductType& productType_,
        const Money& supplierPrice_,
        const Money& salesPrice_,
        int productId_ = NULL
    );
    //~Product();

    void setName(const string& name_);
    string name() const;

    void setDescription(const string& description_);
    string description() const;       

    Contact& manufacturer();
    Contact manufacturer() const;

    Contact& supplier();
    Contact supplier() const;

    void setExternPartNo_(const string& externPartNo_);
    string externPartNo() const;

    void setInternPartNo(const string& internPartNo_);
    string internPartNo() const;

    void setMinOrder(const int& minOrder_);
    int minOrder() const;

    void setDeliveryTime(const int& deliveryTime_);
    int deliveryTime() const;

    ProductType& productType();
    ProductType productType() const;

    Money& supplierPrice();
    Money supplierPrice() const;

    Money& salesPrice();
    Money salesPrice() const;

    string imageName(const std::string& wwwRoot_, const std::string& urlPath_) const;
    string imageThumbName(const std::string& wwwRoot_, const std::string& urlPath_) const;

    int productId() const;

    void clear();

    int save(session& session_);
    void destroy(session& session_);

protected:

private:
    void insert(session& session_);
    void update(session& session_);

    std::string _sanitizeFileName(const std::string& str_) const;
    av::Image _createImage(const std::string& wwwRoot_, const std::string& urlPath_) const;

    std::string _name;
    std::string _description;

    Contact _manufacturer;
    Contact _supplier;

    std::string _externPartNo;
    std::string _internPartNo;
    int _minOrder;
    int _deliveryTime;

    ProductType _productType;

    Money _supplierPrice;
    Money _salesPrice;

    int _productId;
};


#endif // PRODUCT_H_INCLUDED


