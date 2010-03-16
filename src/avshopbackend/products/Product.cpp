#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include "Product.h"

Product::Product()
        : _minOrder(0), _deliveryTime(0), _productId(0)
{

}

Product::Product(const Product * product_)
    : _name(product_->_name), _description(product_->_description),
    _manufacturer(product_->_manufacturer), _supplier(product_->_supplier),
    _externPartNo(product_->_externPartNo), _internPartNo(product_->_internPartNo),
    _minOrder(product_->_minOrder), _deliveryTime(product_->_deliveryTime),
    _productType(product_->_productType),
    _supplierPrice(product_->_supplierPrice), _salesPrice(product_->_salesPrice),
    _productId(product_->_productId)
{
}

Product::Product
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
    int productId_
)
        : _name(name_), _description(description_),
        _manufacturer(manufacturer_), _supplier(supplier_),
        _externPartNo(externPartNo_), _internPartNo(internPartNo_),
        _minOrder(minOrder_), _deliveryTime(deliveryTime_),
        _productType(productType_),
        _supplierPrice(supplierPrice_), _salesPrice(salesPrice_),
        _productId(productId_)
{
   
}

void Product::setName(const string& name_)
{
    _name = name_;    
}

string Product::name() const
{
    return _name;
}

int ProductType::productTypeId() const
{
	return _productTypeId;
}

void Product::setDescription(const string& description_)
{
    _description = description_;
}

string Product::description() const
{
    return _description;
}

Contact& Product::manufacturer()
{
    return _manufacturer;
}

Contact Product::manufacturer() const
{
    return _manufacturer;
}

Contact& Product::supplier()
{
    return _supplier;
}

Contact Product::supplier() const
{
    return _supplier;
}

void Product::setExternPartNo_(const string& externPartNo_)
{
    _externPartNo = externPartNo_;
}

string Product::externPartNo() const
{
    return _externPartNo;
}

void Product::setInternPartNo(const string& internPartNo_)
{
    _description = internPartNo_;
}

string Product::internPartNo() const
{
    return _internPartNo;
}

void Product::setMinOrder(const int& minOrder_)
{
    _minOrder = minOrder_;
}

int Product::minOrder() const
{
    return _minOrder;
}

void Product::setDeliveryTime(const int& deliveryTime_)
{
    _description = deliveryTime_;
}

int Product::deliveryTime() const
{
    return _deliveryTime;
}

ProductType& Product::productType()
{
    return _productType;
}

ProductType Product::productType() const
{
    return _productType;
}

Money& Product::supplierPrice()
{
    return _supplierPrice;
}

Money Product::supplierPrice() const
{
    return _supplierPrice;
}

Money& Product::salesPrice()
{
    return _salesPrice;
}

Money Product::salesPrice() const
{
    return _salesPrice;
}

string Product::imageName(const std::string& wwwRoot_, const std::string& urlPath_) const
{
    return _createImage(wwwRoot_, urlPath_).getFullUrl();
}

string Product::imageThumbName(const std::string& wwwRoot_, const std::string& urlPath_) const
{
    return _createImage(wwwRoot_, urlPath_).getThumbUrl();
}

int Product::productId() const
{
    return _productId;
}

void Product::clear()
{
    _name = "";
    _description = "";

    _manufacturer.clear();
    _supplier.clear();

	_externPartNo = "";
    _internPartNo = "";
    _minOrder = 0;
    _deliveryTime = 0;

    _productType.clear();

    _supplierPrice = Money();
    _salesPrice= Money();

    _productId = 0;
}

int Product::save(session& session_)
{
    if (productId())
    {
        update(session_);
    }
    else
    {
        insert(session_);
    }

    return productId();
}

void Product::insert(session& session_)
{
    session_ <<
    "INSERT INTO Product "
    "	(name, description, manufacturerId, supplierId, externPartNo, "
    "	internPartNo, minOrder, deliveryTime, productTypeId, "
    "	supplierAmount, supplierCurrency, salesAmount, salesCurrency) "
    "VALUES "
    "	(:name, :description, :manufacturerId, :supplierId, :externPartNo, "
    "	:internPartNo, :minOrder, :deliveryTime, :productTypeId, "
    "	:supplierAmount, :supplierCurrency, :salesAmount, :salesCurrency) ",
    use(name(), "name"),
    use(description(), "description"),
    use(manufacturer().save(session_), "manufacturerId"),
    use(supplier().save(session_), "supplierId"),
    use(externPartNo(), "externPartNo"),
    use(internPartNo(), "internPartNo"),
    use(minOrder(), "minOrder"),
    use(deliveryTime(), "deliveryTime"),
    use(productType().save(session_), "productTypeId"),
    use(supplierPrice().amount(), "supplierAmount"),
    use(supplierPrice().currency(), "supplierCurrency"),
    use(salesPrice().amount(), "salesAmount"),
    use(salesPrice().currency(), "salesCurrency");

    session_ << "SELECT last_insert_id()", into(_productId);
};

void Product::update(session& session_)
{
    session_ <<
    "UPDATE Product "
    "SET "
    "	name = :name, "
    "	description = :description, "
    "	manufacturerId = :manufacturerId, "
	"	supplierId = :supplierId, "
	"	externPartNo = :externPartNo, "
    "	internPartNo = :internPartNo, "
    "	minOrder = :minOrder, "
    "	deliveryTime = :deliveryTime, "
    "	productTypeId = :productTypeId, "
    "	supplierAmount = :supplierAmount, "
    "	supplierCurrency = :supplierCurrency, "
    "	salesAmount = :salesAmount, "
    "	salesCurrency = :salesCurrency"
    "WHERE "
    "   productId = :productId",
    use(name(), "name"),
    use(description(), "description"),
    use(manufacturer().save(session_), "manufacturerId"),
    use(supplier().save(session_), "supplierId"),
    use(externPartNo(), "externPartNo"),
    use(internPartNo(), "internPartNo"),
    use(minOrder(), "minOrder"),
    use(deliveryTime(), "deliveryTime"),
    use(productType().save(session_), "productTypeId"),
    use(supplierPrice().amount(), "supplierAmount"),
    use(supplierPrice().currency(), "supplierCurrency"),
    use(salesPrice().amount(), "salesAmount"),
    use(salesPrice().currency(), "salesCurrency");
    use(productId(), "productId");
};

void Product::destroy(session& session_)
{
    if (productId())
    {
        session_ << "DELETE FROM Product WHERE productId = :productId",
        use(productId(), "productId");
    }
    clear();
}

std::string Product::_sanitizeFileName(const std::string& str_) const
{
    std::string str = boost::to_lower_copy(str_);
    boost::replace_all(str, " ", "_");
    boost::replace_all(str, "(", "_");
    boost::replace_all(str, ")", "_");
    boost::replace_all(str, "-", "_");
    boost::replace_all(str, "\"", "_");
    boost::replace_all(str, ",", "_");
    boost::replace_all(str, "/", "_");

    return str;
}

av::Image Product::_createImage(const std::string& wwwRoot_, const std::string& urlPath_) const
{
    std::string path = _sanitizeFileName(manufacturer().companyName()) + "/";
    std::string fileName = _sanitizeFileName(name()) + ".jpg";
    return av::Image(wwwRoot_, urlPath_ + path, fileName);
}
