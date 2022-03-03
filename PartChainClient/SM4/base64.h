#pragma once
#define BASE64_NeedCRLF	1
#define BASE64_NotCRLF	0


/***************************************************************
 *
 * Input
 *     bin_data : binary data
 *     bin_size : binary data length
 *     Mode     : operation mode
 *          BASE64_NeedCRLF ---- Need a CRLF every 64 base64-character
 *          BASE64_NotCRLF  ---- Need not CRLF between 64 base64-character
 *
 * Output
 *     char data
 *     char data length
 *
 * Return
 *     0: success; -1: error
 ***************************************************************/
int Base64_Encode_New(const unsigned char *bin_data,const int& bin_size,
	  			     char * base64_data,int& base64_size,const int& Mode = BASE64_NotCRLF);

/***************************************************************
*
* Input
*     base64_data : char data
*     base64_size : char data length
*
* Output
*     binary data
*     binary data length
*
* Return
*     0: success; -1: base64 data format error
***************************************************************/
int Base64_Decode_New(const char *base64_data, const long long& base64_size,
    unsigned char *bin_data, long long& bin_size);
