


#ifndef pbge_exceptions_h_
#define pbge_exceptions_h_

#include <string>

namespace pbge {
    class Exception {
    public:
        Exception(std::string _message="") {message = _message;}
        virtual const std::string getMessage() {return message;}
    protected:
        std::string message;
    };

    class BuilderValidationException : public Exception {
    public:
        BuilderValidationException(const std::string & _message) : Exception(_message){}
    };

    class BuilderException : public Exception {
    public:
        BuilderException(const std::string & _message) : Exception(_message) {}
    };


}


#endif
