#ifndef __BOO_H
#define __BOO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// for file utility
#include <unistd.h>
#include <sys/file.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

#define BOO_READ_BINARY_MODE "rb"
#define BOO_WRITE_BINARY_MODE "wb"

#define BOO_ERROR_FILE_READ_ERROR 1
#define BOO_ERROR_NULL_MEMORY 2
#define BOO_ERROR_FUNCTIONAL_ERROR 128

#define BOO_ENCRYPTION_KEY 0xff

#define FILE_SIZE_ESTIMATOR(SIZE) (SIZE * sizeof(char))

#define BOO_PADDER 0x04
// algorithm for boo
//
// open a file  -- X
// read content -- X
// modify content -- X
//
// close file

/// the encryptor starter
int boo_starter(int argc, char **argv);

// prototype for opening and reading a file content
void *boo_open_and_read_file(const char *path, 
		int64_t *real_file_size,
		int64_t *read_file_size);

/// the main encryptor for boo
bool 
boo_operation_encrypt(char *target_buffer, 
		size_t target_buffer_size,
		char key);

/// finalizer for boo writer
bool boo_operation_write_close(char *encrypted_data, 
		size_t encrypted_buffer_size,
		char *target_file_path);

int main(int argc, char **argv)
{
	if (argc < 2) {
		return 1;
	}

	return boo_starter(argc, argv);
}

int boo_starter(int argc, char **argv)
{
	const char *target_file = *(argv + 1);
	if (target_file == NULL)
		return BOO_ERROR_NULL_MEMORY; 

	int64_t real_file_size = 0;
	int64_t read_file_size = 0;
	void *target_data = boo_open_and_read_file(target_file, 
			&real_file_size, &read_file_size);
	if (target_data == NULL) {
		return BOO_ERROR_NULL_MEMORY;
	}

	if (real_file_size != read_file_size)
		goto __boo_starter_cleanup;

	boo_operation_encrypt(target_data, read_file_size, BOO_ENCRYPTION_KEY);
	if (boo_operation_write_close(target_data, 
				read_file_size, (char*)target_file) != true) {
		goto __boo_starter_cleanup;
	}
	if (target_data != NULL)
		free(target_data);
	return 0;
__boo_starter_cleanup:
	if (target_data != NULL)
		free(target_data);
	return BOO_ERROR_FUNCTIONAL_ERROR;
}

void *boo_open_and_read_file(const char *path, 
		int64_t *real_file_size,
		int64_t *read_file_size)
{
	if (path == NULL)
		return NULL;

	FILE *target_file = NULL;
	char *target_buffer = NULL;
	target_file = fopen(path, BOO_READ_BINARY_MODE);
	// if file does not exist
	// then return empty object
	if (target_file == NULL) {
		return NULL;
	}
	struct stat sb;
	if (lstat(path, &sb) != 0) {
		goto boo_clear_up_operation;
	}

	int64_t target_file_size = sb.st_size;
	*real_file_size = target_file_size;

	target_buffer = (char*)
		malloc(FILE_SIZE_ESTIMATOR(target_file_size));

	if (target_buffer == NULL)
		goto boo_clear_up_operation;

	memset(target_buffer, 0, target_file_size);
	fseek(target_file, 0, SEEK_SET);
	size_t red = fread(target_buffer, 
			sizeof(char), target_file_size, target_file);
	*read_file_size = red;
	if (red == 0) {
		goto boo_clear_up_operation;
	}

	/// we haven't wrote this safeguard during our session
	/// and it is problematic since it will be leacking memory
	/// MUST CLOSE WHAT YOU OPENED.
	if (target_file != NULL) {
		fclose(target_file);
	}

	return target_buffer;

boo_clear_up_operation:
	if (target_buffer != NULL)
		free(target_buffer);
	if (target_file != NULL)
		fclose(target_file);
	return NULL;
}

/// the main encryptor for boo
bool 
boo_operation_encrypt(char *target_buffer,  size_t target_buffer_size, char key)
{
	if (target_buffer == NULL)
		return false;
	if (target_buffer_size <= 0)
		return false;
	int64_t index = 0;
__boo_encryption_starter:
	if (index >= target_buffer_size)
		goto __boo_encryption_terminator;
	// *(target_buffer + index) = *((target_buffer + index) + BOO_PADDER) ^ key;
	char data = *(target_buffer + index);
	data = (data ^ key) - BOO_PADDER;
	*(target_buffer + index) = data;
	index += 1;
	goto __boo_encryption_starter;
__boo_encryption_terminator:
	return true;
}

bool boo_operation_write_close(char *encrypted_data, 
		size_t encrypted_buffer_size,
		char *target_file_path)
{
	if (encrypted_data == NULL)
		return false;
	if (encrypted_buffer_size <= 0)
		return false;
	if (target_file_path == NULL)
		return false;

	FILE *final_file = NULL;
	final_file = fopen(target_file_path, BOO_WRITE_BINARY_MODE);
	if (final_file == NULL)
		return false;
	fseek(final_file, 0, SEEK_SET);
	fwrite(encrypted_data, sizeof(char), 
			encrypted_buffer_size, final_file);
	fclose(final_file);
	return true;
}

#endif
