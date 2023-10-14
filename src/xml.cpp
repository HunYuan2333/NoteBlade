#include <tinyxml2.h>
#include "xml.h"
#include "error.h"

NoteBlade::XML::XML(std::string path)
{
    _xml = new tinyxml2::XMLDocument();
    auto err = _xml->LoadFile(path.c_str());
    if (err != tinyxml2::XML_SUCCESS) {
        throw std::runtime_error(
            ERR_NUMBER_FORMAT_MESSAGE(ERR_XML_FILE_NOT_FOUND) + "::" +
            ERR_STRING_FORMAT_MESSAGE(tinyxml2::XMLDocument::ErrorIDToName(err), err) + ": " +
            "Failed to load XML file: '" + path + "'. Please check if the file exists."
        );
    }
}

void NoteBlade::XML::display() const
{
    std::cout << "XML @"  << this << std::endl;
}

NoteBlade::NullableXMLElement NoteBlade::NullableXMLElement::first(std::string name) const
{
    auto child = _element->FirstChildElement(name.c_str());
    if (child == NULL) return NullableXMLElement();
    return NullableXMLElement(child);
}

std::vector<NoteBlade::NullableXMLElement> NoteBlade::NullableXMLElement::select(std::string name) const
{
    std::vector<NullableXMLElement> children;
    for (auto child = _element->FirstChildElement(name.c_str()); child != NULL; child = child->NextSiblingElement(name.c_str())) {
        children.push_back(NullableXMLElement(child));
    }
    return children;
}

NoteBlade::NullableXMLUInt NoteBlade::NullableXMLElement::as_uint() const
{
    if (null()) return NullableXMLUInt(tinyxml2::XML_ERROR_MISMATCHED_ELEMENT);
    unsigned int value;
    auto err = _element->QueryUnsignedText(&value);
    if (err != tinyxml2::XML_SUCCESS) return NullableXMLUInt(err);
    return NullableXMLUInt(value);
}

NoteBlade::NullableXMLBool NoteBlade::NullableXMLElement::as_bool() const
{
    if (null()) return NullableXMLBool(tinyxml2::XML_ERROR_MISMATCHED_ELEMENT);
    bool value;
    auto err = _element->QueryBoolText(&value);
    if (err != tinyxml2::XML_SUCCESS) return NullableXMLBool(err);
    return NullableXMLBool(value);
}

NoteBlade::NullableXMLString NoteBlade::NullableXMLElement::as_string() const
{
    if (null()) return NullableXMLString(tinyxml2::XML_ERROR_MISMATCHED_ELEMENT);
    auto value = _element->GetText();
    if (value == NULL) return NullableXMLString(tinyxml2::XML_ERROR_MISMATCHED_ELEMENT);
    return NullableXMLString(value);
}

NoteBlade::NullableXMLUInt NoteBlade::NullableXMLElement::attr_uint(std::string name) const
{
    auto value = _element->UnsignedAttribute(name.c_str());
    if (value == NULL) return NullableXMLUInt(tinyxml2::XML_ERROR_PARSING_ATTRIBUTE);
    return NullableXMLUInt(value);
}

NoteBlade::NullableXMLBool NoteBlade::NullableXMLElement::attr_bool(std::string name) const
{
    auto value = _element->BoolAttribute(name.c_str());
    if (value == NULL) return NullableXMLBool(tinyxml2::XML_ERROR_PARSING_ATTRIBUTE);
    return NullableXMLBool(value);
}

NoteBlade::NullableXMLString NoteBlade::NullableXMLElement::attr_string(std::string name) const
{
    auto value = _element->Attribute(name.c_str());
    if (value == NULL) return NullableXMLString(tinyxml2::XML_ERROR_PARSING_ATTRIBUTE);
    return NullableXMLString(value);
}
