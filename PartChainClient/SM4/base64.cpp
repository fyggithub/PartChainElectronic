
#include "base64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <QDebug>

static char base64_table[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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
/*int Base64_Encode_New(const unsigned char *bin_data,const quint64& bin_size,
                      char * base64_data,quint64& base64_size,const int& Mode)
{
    quint64 blk_size = bin_size / 3;
    long remain_size = (int)bin_size%3 ;
    quint64 i, j, k;
    const unsigned char * p = bin_data;
    unsigned char left[3];
    quint64 i64;
    j = 0;
    i64=0;

    for(i=0;i<blk_size;i++)
    {
        k = (p[0] & 0xFC) >> 2;
        base64_data[j++] = base64_table[k];

        k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
        base64_data[j++] = base64_table[k];

        k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
        base64_data[j++] = base64_table[k];

        k = p[2] & 0x3F;
        base64_data[j++] = base64_table[k];

        i64++;i64++;i64++;i64++;

        if(Mode==BASE64_NeedCRLF)
            if((i64%64)==0)
            {
                base64_data[j++]=(char)0x0d;
                base64_data[j++]=(char)0x0a;
                i64=0;
            }

        p += 3;
    }

    switch(remain_size)
    {
        case 0:
            break;

        case 1:
            left[0] = p[0];
            left[1] = 0;
            p = left;

            k = (p[0] & 0xFC) >> 2;
            base64_data[j++] = base64_table[k];
            k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
            base64_data[j++] = base64_table[k];

            base64_data[j++] = '=';
            base64_data[j++] = '=';
            break;

        case 2:
            left[0] = p[0];
            left[1] = p[1];
            left[2] = 0;
            p = left;

            k = (p[0] & 0xFC) >> 2;
            base64_data[j++] = base64_table[k];
            k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
            base64_data[j++] = base64_table[k];
            k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
            base64_data[j++] = base64_table[k];
            base64_data[j++] = '=';
            break;

        default:
            break;
    }

    base64_data[j] = 0;
    base64_size=j;

    return 0;
}*/
int Base64_Encode_New(const unsigned char *bin_data,const int& bin_size,
					  char * base64_data,int& base64_size,const int& Mode)
{
	long blk_size = bin_size / 3;
	long remain_size = bin_size % 3 ;
	long i, j, k;
    const unsigned char * p = bin_data;
	unsigned char left[3];
	int i64;
	j = 0;
	i64=0;

    for(i=0;i<blk_size;i++)
	{
        k = (p[0] & 0xFC) >> 2;
        base64_data[j++] = base64_table[k];

        k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
        base64_data[j++] = base64_table[k];

        k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
        base64_data[j++] = base64_table[k];

        k = p[2] & 0x3F;
        base64_data[j++] = base64_table[k];

		i64++;i64++;i64++;i64++;

		if(Mode==BASE64_NeedCRLF)
			if((i64%64)==0)
			{
				base64_data[j++]=(char)0x0d;
				base64_data[j++]=(char)0x0a;
				i64=0;
			}

		p += 3;
	}

    switch(remain_size)
	{
	    case 0:
			break;

		case 1:
			left[0] = p[0];
			left[1] = 0;
			p = left;

            k = (p[0] & 0xFC) >> 2;
            base64_data[j++] = base64_table[k];
            k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
            base64_data[j++] = base64_table[k];

			base64_data[j++] = '=';
			base64_data[j++] = '=';
			break;

		case 2:
			left[0] = p[0];
			left[1] = p[1];
			left[2] = 0;
			p = left;

            k = (p[0] & 0xFC) >> 2;
            base64_data[j++] = base64_table[k];
            k = ((p[0] & 0x03) << 4) | (p[1] >> 4);
            base64_data[j++] = base64_table[k];
            k = ((p[1] & 0x0F) << 2) | (p[2] >> 6);
            base64_data[j++] = base64_table[k];
			base64_data[j++] = '=';
			break;

		default:
			break;
	}

	base64_data[j] = 0;
	base64_size=j;

	return 0;
}


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
int Base64_Decode_New(const char *base64_data,const long long &base64_size,
                     unsigned char *bin_data,  long long &bin_size)
//int Base64_Decode_New(const QString& strBase64,const long long &base64_size,
//                     unsigned char *bin_data,  long long &bin_size)
{   
    qDebug()<<"Base64_Decode_New";

    long long i=0,j=0,k=0,m=0,n=0,l=0;
    unsigned char four_bin[4] = {0};
    char four_char[4] = {0};
    char c;

    j = base64_size;
 	i = 0;
	l = 0;
    
    for(;;)
	{
        if((i + 4) > j)
		{
			break;
		}
         
		k = 0;
		while(k < 4)
		{
            if(i == j)
			{
			    break;
			}

			c = base64_data[i++];
            if((c == '+') || (c == '/') || (c == '=') ||
                             ((c >= '0') && (c <= '9')) ||
			                 ((c >= 'A') && (c <= 'Z')) ||
			                 ((c >= 'a') && (c <= 'z')))
			{
   	           four_char[k++] = c;
			}
		}

        if(k != 4)
		{
		    return -1;
		}

		n = 0;
		for(k=0;k<4;k++)
		{
			if(four_char[k] != '=')
			{
			    for(m=0;m<64;m++)
				{
				    if(base64_table[m] == four_char[k])
					{
					    four_bin[k] = (unsigned char)m;
						break;
					}
				}
			}
			else
			{
				n++;
			}
		}

		switch(n)
		{
		    case 0:
                bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
		        bin_data[l++] = (four_bin[1] << 4) | (four_bin[2] >> 2);
		        bin_data[l++] = (four_bin[2] << 6) | four_bin[3]; 
				break;

			case 1:
                bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
		        bin_data[l++] = (four_bin[1] << 4) | (four_bin[2] >> 2);
				break;

			case 2:
                bin_data[l++] = (four_bin[0] << 2) | (four_bin[1] >> 4);
				break;

			default:
				break;
		}
		
		if(n != 0)
		{
			break;
		}
	}

	bin_size = l;

	return 0;
}
