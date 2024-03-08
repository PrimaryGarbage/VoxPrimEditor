#ifndef PRIM_EXCEPTION_HPP
#define PRIM_EXCEPTION_HPP

#include <string>

#define EXCEPTION(what) prim::Exception(what, __FILE__, __LINE__)
#define EXCEPTION_TYPED(what, type) prim::Exception(what, type, __FILE__, __LINE__)
#define CATCH_IGNORE(code) try{code;}catch(...){}

enum class ExceptionType { OperationalException, NotFound };
inline const char* ExceptionType_str[] = { "OperationalException", "NotFound" };

#define OPERATIONAL ExceptionType::OperationalException
#define NOT_FOUND ExceptionType::NotFound

namespace prim
{

    class Exception
    {
    private:
        ExceptionType exceptionType = ExceptionType::OperationalException;
        std::string whatString;
    public:
        Exception(): whatString("[EXCEPTION]") {}
        Exception(std::string what, std::string file, int line): whatString(std::string("[EXCEPTION] : ") 
        + ExceptionType_str[(u_int32_t)exceptionType] + "] -> File: '" + file + "', Line: '" + std::to_string(line) + "', What: '" + what + "'.") {}
        Exception(std::string what, ExceptionType type, std::string file, int line): exceptionType(type), whatString(std::string("[EXCEPTION] : ") 
            + ExceptionType_str[(u_int32_t)exceptionType] + "] -> File: '" + file + "', Line: '" + std::to_string(line) + "', What: '" + what + "'."){}

        std::string what() const { return whatString; }
        ExceptionType type() const { return exceptionType; };
    };

}

#endif // PRIM_EXCEPTION_HPP