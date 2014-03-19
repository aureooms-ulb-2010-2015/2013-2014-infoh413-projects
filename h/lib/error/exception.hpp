#ifndef _LIB_ERROR_EXCEPTION_HPP
#define _LIB_ERROR_EXCEPTION_HPP

namespace lib{
namespace error{

	class exception : public std::exception {
	private:
		std::string msg;
	public:
		exception(const std::string& msg):msg(msg){}
		virtual ~exception() noexcept {}
		const char* what() const noexcept {return msg.c_str();}
	};

}
}


#endif // _LIB_ERROR_EXCEPTION_HPP