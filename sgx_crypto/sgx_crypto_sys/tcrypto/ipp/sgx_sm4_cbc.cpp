/*
 * Copyright (C) 2011-2021 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "sgx_tcrypto.h"
#include "ippcp.h"
#include "ipp_wrapper.h"
#include "stdlib.h"
#include "string.h"

/* SM4-CBC
 * Parameters:
 *   Return:
 *     sgx_status_t - SGX_SUCCESS or failure as defined in sgx_error.h
 *   Inputs:
 *     sgx_sm4_128bit_key_t *p_key - Pointer to the key used in encryption/decryption operation
 *     uint8_t *p_src - Pointer to the input stream to be encrypted/decrypted
 *     uint32_t src_len - Length of the input stream to be encrypted/decrypted
 *     uint8_t *p_iv - Pointer to initialization vector to use
 *     uint32_t iv_len - Length of initialization vector
 *   Output:
 *     uint8_t *p_dst - Pointer to the cipher text. Size of buffer should be >= src_len.
 */
sgx_status_t sgx_sm4_cbc_encrypt(const sgx_sm4_cbc_128bit_key_t *p_key, const uint8_t *p_src,
                                const uint32_t src_len, uint8_t *p_dst, const uint8_t *p_iv,
                                const uint32_t iv_len)
{
    IppStatus error_code = ippStsNoErr;
    IppsSMS4Spec* ptr_ctx = NULL;
    int ctx_size = 0;

    if ((p_key == NULL) || (p_src == NULL) || (p_iv == NULL) || (iv_len != SGX_SM4CBC_IV_SIZE) || (p_dst == NULL))
    {
        return SGX_ERROR_INVALID_PARAMETER;
    }

    // SM4-CBC encryption
    error_code = ippsSMS4GetSize(&ctx_size);
    if (error_code != ippStsNoErr)
    {
        return SGX_ERROR_UNEXPECTED;
    }
    ptr_ctx = (IppsSMS4Spec*)malloc(ctx_size);
    if (ptr_ctx == NULL)
    {
        return SGX_ERROR_OUT_OF_MEMORY;
    }

    // Init
    error_code = ippsSMS4Init((const Ipp8u*)p_key, SGX_SM4CBC_KEY_SIZE, ptr_ctx, ctx_size);
    if (error_code != ippStsNoErr)
    {
        // Clear temp State before free.
        memset_s(ptr_ctx, ctx_size, 0, ctx_size);
        free(ptr_ctx);
        switch (error_code)
        {
        case ippStsMemAllocErr: return SGX_ERROR_OUT_OF_MEMORY;
        case ippStsNullPtrErr:
        case ippStsLengthErr: return SGX_ERROR_INVALID_PARAMETER;
        default: return SGX_ERROR_UNEXPECTED;
        }
    }
    error_code = ippsSMS4EncryptCBC(p_src, p_dst, src_len, ptr_ctx, p_iv);
    if (error_code != ippStsNoErr)
    {
        // Clear temp State before free.
        memset_s(ptr_ctx, ctx_size, 0, ctx_size);
        free(ptr_ctx);
        switch (error_code)
        {
        case ippStsNullPtrErr:
        case ippStsLengthErr: return SGX_ERROR_INVALID_PARAMETER;
        default: return SGX_ERROR_UNEXPECTED;
        }
    }
    // Clear temp State before free.
    memset_s(ptr_ctx, ctx_size, 0, ctx_size);
    free(ptr_ctx);
    return SGX_SUCCESS;
}

sgx_status_t sgx_sm4_cbc_decrypt(const sgx_sm4_cbc_128bit_key_t *p_key, const uint8_t *p_src,
                                const uint32_t src_len, uint8_t *p_dst, const uint8_t *p_iv,
                                const uint32_t iv_len)
{
    IppStatus error_code = ippStsNoErr;
    IppsSMS4Spec* ptr_ctx = NULL;
    int ctx_size = 0;

    if ((p_key == NULL) || (p_src == NULL) || (p_iv == NULL) || (iv_len != SGX_SM4CBC_IV_SIZE) || (p_dst == NULL))
    {
        return SGX_ERROR_INVALID_PARAMETER;
    }

    // SM4-CBC decryption
    error_code = ippsSMS4GetSize(&ctx_size);
    if (error_code != ippStsNoErr)
    {
        return SGX_ERROR_UNEXPECTED;
    }
    ptr_ctx = (IppsSMS4Spec*)malloc(ctx_size);
    if (ptr_ctx == NULL)
    {
        return SGX_ERROR_OUT_OF_MEMORY;
    }

    // Init
    error_code = ippsSMS4Init((const Ipp8u*)p_key, SGX_SM4CBC_KEY_SIZE, ptr_ctx, ctx_size);
    if (error_code != ippStsNoErr)
    {
        // Clear temp State before free.
        memset_s(ptr_ctx, ctx_size, 0, ctx_size);
        free(ptr_ctx);
        switch (error_code)
        {
        case ippStsMemAllocErr: return SGX_ERROR_OUT_OF_MEMORY;
        case ippStsNullPtrErr:
        case ippStsLengthErr: return SGX_ERROR_INVALID_PARAMETER;
        default: return SGX_ERROR_UNEXPECTED;
        }
    }
    error_code = ippsSMS4DecryptCBC(p_src, p_dst, src_len, ptr_ctx, p_iv);
    if (error_code != ippStsNoErr)
    {
        // Clear temp State before free.
        memset_s(ptr_ctx, ctx_size, 0, ctx_size);
        free(ptr_ctx);
        switch (error_code)
        {
        case ippStsNullPtrErr:
        case ippStsLengthErr: return SGX_ERROR_INVALID_PARAMETER;
        default: return SGX_ERROR_UNEXPECTED;
        }
    }
    // Clear temp State before free.
    memset_s(ptr_ctx, ctx_size, 0, ctx_size);
    free(ptr_ctx);
    return SGX_SUCCESS;
}
