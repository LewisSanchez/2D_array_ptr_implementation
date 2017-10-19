#include "Exception.h"

Exception::Exception()
	: m_msg(nullptr)
{

}

Exception::Exception(char * msg)
{
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}

Exception::Exception(const Exception & copy)
{
	this->m_msg = new char[strlen(copy.m_msg) + 1];
	strcpy(this->m_msg, copy.m_msg);
}

Exception::~Exception()
{
	if (m_msg != nullptr)
		delete[] m_msg;
}

Exception & Exception::operator= (const Exception & rhs)
{
	if (this != &rhs)
	{
		if (this->m_msg != nullptr)
			delete[] this->m_msg;

		this->m_msg = new char[strlen(rhs.m_msg) + 1];
		strcpy(this->m_msg, rhs.m_msg);
	}

	return *this;
}

const char * Exception::getMessage()
{
	return this->m_msg;
}

void Exception::setMessage(char * msg)
{
	if (this->m_msg != nullptr)
		delete[] this->m_msg;

	this->m_msg = new char[strlen(msg) + 1];
	strcpy(this->m_msg, msg);
}

ostream & operator<< (ostream & stream, const Exception & except)
{
	stream << except.m_msg << '\n';

	return stream;
}