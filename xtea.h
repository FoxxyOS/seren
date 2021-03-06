/*
 * Copyright (C) 2013, 2014 Giorgio Vazzana
 *
 * This file is part of Seren.
 *
 * Seren is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Seren is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef XTEA_H
#define XTEA_H

#include <stddef.h>
#include <stdint.h>

struct xtea_ctx {
	/* 128-bit key */
	uint32_t key[4];

#ifndef SMALL
	/* subkeys */
	uint32_t subkey[64];
#endif
};

void xtea_init(struct xtea_ctx *ctx, const uint8_t key[16]);

/* For all the following functions len must be multiple of 8.
 * Encryption and decryption will be performed "in place",
 * that is, overwriting the data in buf.
 */

/* electronic codebook */
void xtea_encrypt_buffer_ecb(const struct xtea_ctx *ctx, uint8_t *buf, size_t len);
void xtea_decrypt_buffer_ecb(const struct xtea_ctx *ctx, uint8_t *buf, size_t len);

/* cipher-block chaining */
void xtea_encrypt_buffer_cbc(const struct xtea_ctx *ctx, uint8_t *buf, size_t len, const uint32_t iv[2]);
void xtea_decrypt_buffer_cbc(const struct xtea_ctx *ctx, uint8_t *buf, size_t len, const uint32_t iv[2]);

/* counter */
void xtea_encrypt_buffer_ctr(const struct xtea_ctx *ctx, uint8_t *buf, size_t len, const uint32_t iv[2]);
#define xtea_decrypt_buffer_ctr xtea_encrypt_buffer_ctr

#endif
