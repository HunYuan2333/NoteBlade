#ifndef XML_H
#define XML_H

#include <string>
#include <vector>
#include <iostream>
#include <tinyxml2.h>
#include "error.h"

namespace NoteBlade {
    template <typename T>
    class NullableXMLValue {
        private:
            bool                _null;
            tinyxml2::XMLError  _error;
            T                   _value;
        public:
            NullableXMLValue(tinyxml2::XMLError error) : _null(true),  _error(error) {};
            NullableXMLValue(T value)                  : _null(false), _error(tinyxml2::XML_SUCCESS), _value(value) {};

            T                   default_unwarp(T i)  const { return _null ? i : _value; };
            bool                null()               const { return _null; };
            std::string         error_message()      const { return tinyxml2::XMLDocument::ErrorIDToName(_error); };
            tinyxml2::XMLError  error()              const { return _error; };

            T unwarp()  const {
                return !null()
                    ? _value
                    : throw std::runtime_error(
                        ERR_NUMBER_FORMAT_MESSAGE(ERR_XML_READ_VALUE) + "::" +
                        ERR_STRING_FORMAT_MESSAGE(error_message(), error()) + ": " +
                        "Failed to read value from XML."
                    );
            };
    };

    typedef NullableXMLValue<unsigned int> NullableXMLUInt;
    typedef NullableXMLValue<std::string>  NullableXMLString;
    typedef NullableXMLValue<bool>         NullableXMLBool;

    class NullableXMLElement {
        private:
            tinyxml2::XMLElement* _element;
            bool                  _null;
        public:
            NullableXMLElement()                              : _element(NULL),    _null(true) {};
            NullableXMLElement(tinyxml2::XMLElement* element) : _element(element), _null(false) {};

            bool                             null()                         const { return _element == NULL; };
            std::vector<NullableXMLElement>  select(std::string name)       const;
            NullableXMLElement               first(std::string name)        const;
            NullableXMLUInt                  as_uint()                      const;
            NullableXMLBool                  as_bool()                      const;
            NullableXMLString                as_string()                    const;
            NullableXMLUInt                  attr_uint(std::string name)    const;
            NullableXMLBool                  attr_bool(std::string name)    const;
            NullableXMLString                attr_string(std::string name)  const;
    };

    class XML {
        private:
            tinyxml2::XMLDocument* _xml;
        public:
            XML(std::string path);
            void display()  const;
            auto document() const { return _xml; };
            auto root()     const { return NullableXMLElement(_xml->RootElement()); };
    };
}

#endif
