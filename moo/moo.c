#ifndef __MOO_H
#define __MOO_H

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

#define MOO_READ_BINARY_MODE "rb"
#define MOO_WRITE_BINARY_MODE "wb"

#define MOO_ERROR_FILE_READ_ERROR 1
#define MOO_ERROR_NULL_MEMORY 2
#define MOO_ERROR_FUNCTIONAL_ERROR 128

#define MOO_ENCRYPTION_KEY 0xff

#define FILE_SIZE_ESTIMATOR(SIZE) (SIZE * sizeof(char))

#define MOO_PADDER 0x04
// algorithm for moo
//
// open a file  -- X
// read content -- X
// modify content -- X
//
// close file

/// the encryptor starter
int moo_starter(int argc, char **argv);

// prototype for opening and reading a file content
void *moo_open_and_read_file(const char *path, 
		int64_t *real_file_size,
		int64_t *read_file_size);

/// the main encryptor for moo
bool 
moo_operation_encrypt(char *target_buffer, 
		size_t target_buffer_size,
		char key);

/// finalizer for moo writer
bool moo_operation_write_close(char *encrypted_data, 
		size_t encrypted_buffer_size,
		char *target_file_path);

int main(int argc, char **argv)
{
	if (argc < 2) {
		return 1;
	}

	return moo_starter(argc, argv);
}

int moo_starter(int argc, char **argv)
{
	const char *target_file = *(argv + 1);
	if (target_file == NULL)
		return MOO_ERROR_NULL_MEMORY; 

	int64_t real_file_size = 0;
	int64_t read_file_size = 0;
	void *target_data = moo_open_and_read_file(target_file, 
			&real_file_size, &read_file_size);
	if (target_data == NULL) {
		return MOO_ERROR_NULL_MEMORY;
	}

	if (real_file_size != read_file_size)
		goto __moo_starter_cleanup;

	moo_operation_encrypt(target_data, read_file_size, MOO_ENCRYPTION_KEY);
	if (moo_operation_write_close(target_data, 
				read_file_size, (char*)target_file) != true) {
		goto __moo_starter_cleanup;
	}
	if (target_data != NULL)
		free(target_data);
	return 0;
__moo_starter_cleanup:
	if (target_data != NULL)
		free(target_data);
	return MOO_ERROR_FUNCTIONAL_ERROR;
}

void *moo_open_and_read_file(const char *path, 
		int64_t *real_file_size,
		int64_t *read_file_size)
{
	if (path == NULL)
		return NULL;

	FILE *target_file = NULL;
	char *target_buffer = NULL;
	target_file = fopen(path, MOO_READ_BINARY_MODE);
	// if file does not exist
	// then return empty object
	if (target_file == NULL) {
		return NULL;
	}
	struct stat sb;
	if (lstat(path, &sb) != 0) {
		goto moo_clear_up_operation;
	}

	int64_t target_file_size = sb.st_size;
	*real_file_size = target_file_size;

	target_buffer = (char*)
		malloc(FILE_SIZE_ESTIMATOR(target_file_size));

	if (target_buffer == NULL)
		goto moo_clear_up_operation;

	memset(target_buffer, 0, target_file_size);
	fseek(target_file, 0, SEEK_SET);
	size_t red = fread(target_buffer, 
			sizeof(char), target_file_size, target_file);
	*read_file_size = red;
	if (red == 0) {
		goto moo_clear_up_operation;
	}

	/// we haven't wrote this safeguard during our session
	/// and it is problematic since it will be leacking memory
	/// MUST CLOSE WHAT YOU OPENED.
	if (target_file != NULL) {
		fclose(target_file);
	}

	return target_buffer;

moo_clear_up_operation:
	if (target_buffer != NULL)
		free(target_buffer);
	if (target_file != NULL)
		fclose(target_file);
	return NULL;
}

/// the main encryptor for moo
bool 
moo_operation_encrypt(char *target_buffer,  size_t target_buffer_size, char key)
{
	if (target_buffer == NULL)
		return false;
	if (target_buffer_size <= 0)
		return false;
	int64_t index = 0;
__moo_encryption_starter:
	if (index >= target_buffer_size)
		goto __moo_encryption_terminator;
	// *(target_buffer + index) = *((target_buffer + index) + MOO_PADDER) ^ key;
	char data = *(target_buffer + index);
	data = (data + MOO_PADDER) ^ key;
	*(target_buffer + index) = data;
	index += 1;
	goto __moo_encryption_starter;
__moo_encryption_terminator:
	return true;
}

bool moo_operation_write_close(char *encrypted_data, 
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
	final_file = fopen(target_file_path, MOO_WRITE_BINARY_MODE);
	if (final_file == NULL)
		return false;
	fseek(final_file, 0, SEEK_SET);
	fwrite(encrypted_data, sizeof(char), 
			encrypted_buffer_size, final_file);
	fclose(final_file);
	return true;
}

#endif
