#include "stdafx.h"
#include "SerialCom.h"


SerialCom::SerialCom()
{
	serial = NULL;
}


SerialCom::~SerialCom()
{
	ClosePort();
}

bool SerialCom::OpenPort(std::string port)
{
	if (serial != NULL)
		return false;

	serial = new boost::asio::serial_port(ios);
	serial->open(port, ec);
	serial->set_option(boost::asio::serial_port::baud_rate(115200));
	serial->set_option(boost::asio::serial_port::flow_control());
	serial->set_option(boost::asio::serial_port::parity());
	serial->set_option(boost::asio::serial_port::stop_bits());
	serial->set_option(boost::asio::serial_port::character_size(8));
	if (ec)
	{
		TRACE("�򿪴���ʧ��%s\n", ec.message().c_str());
		return false;
	}

	TRACE("�򿪴��ڳɹ�%s\n", ec.message().c_str());
	return true;
}

bool SerialCom::OpenPort(int port) {
	return false;
}

void SerialCom::ClosePort() {
	if (serial != NULL) {
		serial->close();
		delete serial;
		serial = NULL;
	}
}

bool SerialCom::Send(unsigned char* data, int data_len) {
	if (data == NULL || data_len <= 0)
		return false;

	size_t written = boost::asio::write(*serial, boost::asio::buffer(data, data_len), ec);
	if (ec)
	{
		TRACE("д����ʧ�� %s\n", ec.message().c_str());
		return false;
	}

	if (written != data_len)
		return false;

	return true;
}

bool SerialCom::Recv(unsigned char* data, int need_read, int* actual_read) {
	if (data == NULL || need_read <= 0)
		return false;

	//boost::asio::read_until();
	
	*actual_read = serial->read_some(boost::asio::buffer(data, need_read), ec);

	if (ec) {
		TRACE("������ʧ�� %s\n", ec.message().c_str());
		return false;
	}

	if (*actual_read != need_read) {
		TRACE("������ʧ�� %s\n", ec.message().c_str());
		return false;
	}

	TRACE("�����ڳɹ�\n");
	return true;
}