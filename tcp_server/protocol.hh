#ifndef PROTOCOL_HH
#define PROTOCOL_HH

/* protocol specification */

#include <stdint.h>

const uint32_t FILE_BUFF_SIZE = 1024;

enum TYPES {
	CONFIRM = 1, // подтверждение завершения команды, либо от клиента либо от сервера
	GREET, // приветствие от клиента, data - uint8_t id терминала
	GET_BULLETIN, // запрос бюллетеня от клиента, data - null
	SEND_BULLETIN, // отправка бюллетеня от сервера, data - uint32_t размер файла
	SEND_RESULT, // отправка от клиента результат голосования, data - uint8_t - номер кандидата, либо 0
	SEND_CANCELED, // отправка отмены голосования от клиенты
};

// base request structure
struct request {
	uint8_t type;
	char data[4];
}__attribute__((packed));
struct request_greeting
{
	uint8_t type = GREET;
	uint8_t terminal_id;
	char _data[3];
}__attribute__((packed));
struct request_bulletin {
	uint8_t type = GET_BULLETIN;
	char _data[4];
}__attribute__((packed));

struct send_bulletin {
	uint8_t type = SEND_BULLETIN;
	uint32_t file_size;
}__attribute__((packed));

struct send_result {
	uint8_t type = SEND_RESULT;
	uint8_t candidate_id = 0;
	char _data[3];
}__attribute__((packed));

struct send_cancel {
	uint8_t type = SEND_CANCELED;
	char _data[4];
}__attribute__((packed));

struct request_confirm {
	uint8_t type = CONFIRM;
	char _data[4];
}__attribute__((packed));
#endif /* PROTOCOL_HH */