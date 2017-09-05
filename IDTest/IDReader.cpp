#include "stdafx.h"
#include "IDReader.h"


IDReader::IDReader()
{
	
}


IDReader::~IDReader()
{
}

bool IDReader::Init(std::string port)
{
	
	return com.OpenPort(port);
}

unsigned char IDReader::calc_lrc(unsigned char* data, int data_len)
{
	unsigned char lrc = 0;

	for (int i = 0; i < data_len; i++)
	{
		lrc ^= data[i];
	}

	return lrc;
}


bool IDReader::ReadIDNo(char* idno, int* len)
{
	char send_buf[8] = { 0x00 };

	char begin = 0x02;

	
	char data_len_buf[2] = { 0x00, 0x03 };

	char data[3] = { 0xCA, 0x01, 0x01 };
	

	char lrc = 0x00;
	char end = 0x03;

	
	int pos = 0;
	memcpy(send_buf + pos, &begin, 1);
	pos += 1;

	memcpy(send_buf + pos, data_len_buf, 2);
	pos += 2;

	memcpy(send_buf + pos, data, sizeof(data));
	pos += sizeof(data);

	lrc = calc_lrc((unsigned char*)data, sizeof(data));
	memcpy(send_buf + pos, &lrc, 1);
	pos += 1;

	memcpy(send_buf + pos, &end, 1);

	if ( !com.Send((unsigned char*)send_buf, sizeof(send_buf)) )
		return false;

	char recv_buf[1024] = { 0x00 };
	int actual_len = 0;

	// 先接收前5个字节
	if (!com.Recv((unsigned char*)recv_buf, pkglen, &actual_len)) {
		return false;
	}
	

	short data_len = 0;
	memcpy(&data_len, recv_buf + 1, 2);
	data_len = htons(data_len);

	short status = 0;
	memcpy(&status, recv_buf + 3, 2);
	status = htons(status);
	if (status != 0x9000) {

	}
	
	// 2代表lrc + end
	if (!com.Recv((unsigned char*)recv_buf + pkglen, (int)data_len, &actual_len)) {
		return false;
	}

	*len = 36;
	memcpy(idno, recv_buf + 5, *len);

	return true;
}